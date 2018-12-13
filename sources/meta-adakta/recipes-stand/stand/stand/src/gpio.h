/*
 * gpio.h
 *
 *  Created on: 19 окт. 2017 г.
 *      Author: root
 */



#ifndef GPIO_H_
#define GPIO_H_


#include "stand.h"


class gpio: public fragfifo{
	public:
	gpio(void)
	{

		//string port="/dev/ttymxc2";
		TTYC=new TTYclass(sGVstr.tty_port,115200,1);
		if (TTYC->glbERROR==ERROR)
		{
			TTYC->comfd=-1;
			printf("Error not open uart %s\n",sGVstr.tty_port.c_str());
		}
		else
		{
			printf("Success open uart %s!!!\n",sGVstr.tty_port.c_str());
		}


	}
	~gpio(void)
	{
		delete TTYC;
	}
	/*
	 * echo 9 > /sys/class/gpio/export
echo out > /sys/class/gpio/gpio9/direction
echo 0 > /sys/class/gpio/gpio9/value
	 *
	 */
	//a2 a5
	//0123
	eErrorTp SetPin(char * pincode,bool value)
	{
		ofstream  fil;
		u32 pin;
		sPinDev pd=pdSOC;
		string MCpin;
		string MCmd;


		//printf("Pincode %s\n",pincode);
		//mdelay(1);
		if (pincode[0]=='P')
			pd=pdMC;

		if (pd==pdSOC)
		{
			pin=ConvertSOC_Pincode(pincode);
			if (pin==0xffffffff)
				return ERROR;

			fil.open(string_format("/sys/class/gpio/export"),ios::out |ios::binary);
			fil << to_string(pin);
			fil.close();

			fil.open(string_format("/sys/class/gpio/gpio%d/direction",pin),ios::out |ios::binary);
			fil << "out";
			fil.close();

			fil.open(string_format("/sys/class/gpio/gpio%d/value",pin),ios::out |ios::binary);
			fil << to_string(value);
			fil.close();
			return NO_ERROR;
		}

		if (pd==pdMC)
		{
			MCpin=ConvertMC_Pincode(pincode);
			if (MCpin.size()==0)
				return ERROR;

			if (value==true)
				MCmd="set "+MCpin+" 1\n";
			else
				MCmd="set "+MCpin+" 0\n";

			TTYC->TTYClear();

			TTYC->TTYwriteBuf(MCmd.c_str(),MCmd.size());
			memset(rxbuf,0,sizeof(rxbuf));
			u8 n=0;
			u8 ch;
			u32 z=0;

			while(1){
				if (TTYC->TTYreadChar(ch)!=ERROR)
				{
					rxbuf[n]=ch;
					n++;
					rxbuf[n]=0;
					if (rxbuf[n-1]==10)
					{
						rxbuf[n-1]=0;
						break;
					}
				}
				mdelay(1);
				z++;
				if (z==200)
					return ERROR;
			}

			if (strcmp(rxbuf,"1\n")!=0)
			{
				return ERROR;
			}
		}

		return NO_ERROR;
	}

	u32 GetPort(char * port)
	{
		sPinDev pd=pdSOC;
		string MCport;
		string MCmd;
		u32 result;
		u16 n=0;
		u8 ch=0;

		if (port[0]=='P')
			pd=pdMC;

		memset(rxbuf,0,sizeof(rxbuf));
		if (pd==pdMC)
		{
			if (strlen(port)==2)
			{
				MCport=port[1];
			}
			else
				return 0;

			MCmd="get "+MCport+"\n";

			//printf("MCDM %s\n",MCmd.c_str());
			TTYC->TTYClear();
			TTYC->TTYwriteBuf(MCmd.c_str(),MCmd.size());
			mdelay(5);
			while(TTYC->TTYreadChar(ch)==NO_ERROR){
				rxbuf[n]=ch;

				n++;
				rxbuf[n]=0;
				mdelay(3);

			}

			if (strlen(rxbuf)!=0)
			{
				if (rxbuf[n-1]==10)
					{
						rxbuf[n-1]=0;
						result=atoi(rxbuf);
					}
			}
		}

		return result;
	}

	eErrorTp GetPin(char * pincode,u32 & val)
	{

		//mdelay(2);
		sPinDev pd=pdSOC;
		if (pincode[0]=='P')
			pd=pdMC;

		string MCpin;
		string MCmd;

		u8 ch=0;
		u16 n=0;
		u8 rbuf[20];

		memset(rxbuf,0,sizeof(rxbuf));

		if (pd==pdMC)
		{
			MCpin=ConvertMC_Pincode(pincode);
			if (MCpin.size()==0)
			{

				printf("MCpin.size()==0\n");
				return ERROR;
			}
			MCmd="get "+MCpin+"\n";

			TTYC->TTYClear();
			TTYC->TTYwriteBuf(MCmd.c_str(),MCmd.size());
			//mdelay(5);
			n=0;


			u32 z=0;
			while(1){
				if (TTYC->TTYreadChar(ch)!=ERROR)
				{
					rxbuf[n]=ch;
					n++;

					rxbuf[n]=0;
					if (rxbuf[n-1]==10)
					{
						rxbuf[n-1]=0;
						break;
					}
				}

				mdelay(1);
				z++;
				if (z==200)
					return ERROR;
			}

			val=atoi(rxbuf);

			return NO_ERROR;

	   }
	   else
	   {
		   u32 SocPin;
		   stringstream value;
		   ofstream  wrFile;
		   ifstream  rdFile;

		   SocPin=ConvertSOC_Pincode(pincode);
		   if (SocPin==0xffffffff)
		   		return ERROR;

		   wrFile.open(string_format("/sys/class/gpio/export"),ios::out |ios::binary);
		   wrFile << to_string(SocPin);
		   wrFile.close();

		   wrFile.open(string_format("/sys/class/gpio/gpio%d/direction",SocPin),ios::out |ios::binary);
		   wrFile << "in";
		   wrFile.close();

		   rdFile.open(string_format("/sys/class/gpio/gpio%d/value",SocPin),ios::in |ios::binary);
		   value << rdFile.rdbuf();
		   rdFile.close();
		   val=atoi(value.str().c_str());
		   return NO_ERROR;
	   }

		return ERROR;
	}

	//
	///g.SetPin("0102",1);
	///if (g.GetPin("Pe06")!=1)
	//	printf("Error\n");

	eErrorTp LinearGpio_SoC_Out_MC_In(__ModuleGpioMap * MMap, u32& TotalGpio)
	{
		__ModuleGpioMap * pMMap;
		eErrorTp err=NO_ERROR;
		pMMap=MMap;
		TotalGpio=0;
		u32 res;
		printf("Started gpio test linear algo SoC out, MC in\n");
		while (pMMap->MCpin[0]!=0)
		{
			TotalGpio++;
			//printf("gpio %s(%s)|SoC %s<->MC %s\n",pMMap->SoCname,pMMap->SoCpad,pMMap->SoCpin,pMMap->MCpin);
			SetPin(pMMap->SoCpin,0);
			if ((GetPin(pMMap->MCpin,res)==ERROR)||(res!=0))
			{
				PushBuf((u8*)pMMap,sizeof(__ModuleGpioMap));
				err=ERROR;
				//printf("New error, total found %d\n",GetCountElements());
			}

			SetPin(pMMap->SoCpin,1);
			if ((GetPin(pMMap->MCpin,res)==ERROR)||(res!=1))
			{

				PushBuf((u8*)pMMap,sizeof(__ModuleGpioMap));
				err=ERROR;
				//printf("New error, total found %d\n",GetCountElements());
			}

			pMMap++;
			//printf("pMMap 0x%08x\n",pMMap);

		}

		return err;
	}

	eErrorTp ReleaseAllPins(__ModuleGpioMap * MMap)
	{
		__ModuleGpioMap * pMMap=MMap;
		u32 res;
		while (pMMap->MCpin[0]!=0)
		{
			GetPin(pMMap->MCpin,res);
			pMMap++;
		}
		printf("Set all MC pins to input (release pin)\n");
		return NO_ERROR;

	}

	eErrorTp LinearGpio_MC_Out_SoC_In(__ModuleGpioMap * MMap, u32& TotalGpio)
		{
			__ModuleGpioMap * pMMap;
			eErrorTp err=NO_ERROR;
			u32 res;
			pMMap=MMap;
			TotalGpio=0;
			printf("Started gpio test linear algo MC out, SoC in\n");
			while (pMMap->MCpin[0]!=0)
			{
				TotalGpio++;
				//printf("gpio %s(%s)|SoC %s<->MC %s\n",pMMap->SoCname,pMMap->SoCpad,pMMap->SoCpin,pMMap->MCpin);
				SetPin(pMMap->MCpin,0);
				if ((GetPin(pMMap->SoCpin,res)==ERROR)||(res!=0))
				{
					PushBuf((u8*)pMMap,sizeof(__ModuleGpioMap));
					err=ERROR;
					//printf("New error, total found %d\n",GetCountElements());
				}

				SetPin(pMMap->MCpin,1);
				if ((GetPin(pMMap->SoCpin,res)==ERROR)||(res!=1))
				{

					PushBuf((u8*)pMMap,sizeof(__ModuleGpioMap));
					err=ERROR;
					//printf("New error, total found %d\n",GetCountElements());
				}

				pMMap++;
				//printf("pMMap 0x%08x\n",pMMap);

			}

			return err;
		}

	eErrorTp LinearGpio_ZeroSearch(__ModuleGpioMap * MMap, u32& TotalGpio)
			{
				__ModuleGpioMap * pMMap;
				__ModuleGpioMap * ptMMap;
				__ModuleGpioMap * ptfMMap;
				eErrorTp err=NO_ERROR;
				pMMap=MMap;
				TotalGpio=0;
				u32 res;
				printf("Started gpio test linear algo, zero search\n");
				while (pMMap->MCpin[0]!=0)
				{
					TotalGpio++;
					//printf("First stage %s (%s)\n",pMMap->SoCname,pMMap->SoCpad);
					ptfMMap=MMap;
					while (ptfMMap->MCpin[0]!=0)
					{
						SetPin(ptfMMap->SoCpin,1);
						ptfMMap++;
					}
					//ptMMap=MMap;
					SetPin(pMMap->SoCpin,0);

					ptMMap=MMap;
					while (ptMMap->MCpin[0]!=0)
					{
						if (ptMMap==pMMap)
						{
							ptMMap++;
							continue;
						}

						if ((GetPin(ptMMap->MCpin,res)==ERROR)||(res!=1))
						{
							PushBuf((u8*)ptMMap,sizeof(__ModuleGpioMap));
							err=ERROR;

						}
						ptMMap++;
					}

				//	printf("Second stage\n");
					ptfMMap=MMap;
					while (ptfMMap->MCpin[0]!=0)
					{
						SetPin(ptfMMap->SoCpin,0);
						ptfMMap++;
					}
					SetPin(pMMap->SoCpin,1);

					ptMMap=MMap;
					while (ptMMap->MCpin[0]!=0)
					{
						if (ptMMap==pMMap)
						{
							ptMMap++;
							continue;
						}

						if ((GetPin(ptMMap->MCpin,res)==ERROR)||(res!=0))
						{
							PushBuf((u8*)ptMMap,sizeof(__ModuleGpioMap));
							err=ERROR;

						}
					   ptMMap++;
					}

					pMMap++;


				}

				return err;
			}

	eErrorTp RunGpioTest(__ModuleGpioMap * MMap,stringstream & Msg)
	{
		__ModuleGpioMap * err;
		u32 errsz;
		u32 TotalGpio;
		ClearAll();

		if (LinearGpio_SoC_Out_MC_In(MMap,TotalGpio)==NO_ERROR)
		{
			SetLED(sGV.progress++,1);
			//sleep(1);
			if (LinearGpio_MC_Out_SoC_In(MMap,TotalGpio)==NO_ERROR)
			{
				SetLED(sGV.progress++,1);
				LinearGpio_ZeroSearch(MMap,TotalGpio);
				SetLED(sGV.progress++,1);
			}
			else
			{
				SetLED(sGV.progress++,1);
			}
		}

		ReleaseAllPins(MMap);
		Msg << endl << LINE_SEP << endl;
		u32 errcnt=GetCountElements();
		if (errcnt!=0)
		{
			while((err=(__ModuleGpioMap*)GetLastBuf(errsz))!=NULL)
			{
				printf("Error gpio %15s(%03s)|SoC %s<->MC %s\n",err->SoCname,err->SoCpad,err->SoCpin,err->MCpin);
				Msg << "Error gpio " << err->SoCname << " (" << err->SoCpad << ")|SoC " << err->SoCpin << "<->MC " << err->MCpin << endl;
			}
		}

		printf("Total GPIO %d, errors [%d]\n",TotalGpio,errcnt);
		Msg  << "Checked: GPIO" << endl;
		Msg << "    total GPIO " << TotalGpio << ", errors [" << errcnt << "]" << endl;
		if (errcnt==0)
			return NO_ERROR;
		else
			return ERROR;
	}

	eErrorTp SetLED(u8 led,u8 val)
	{
		val&=1;
		SetPin(sGV.LED[led].MCpin,val);
		return NO_ERROR;
	}

	eErrorTp ClearAllLed(void)
	{
		for (u32 n=0;n<MAX_LED;n++)
				{
					SetLED(n,0);
				}
		return NO_ERROR;

	}

	eErrorTp SetErrorToLed(u8 level0_3)
	{
		u32 max=level0_3*4;

		if (max>MAX_LED) max=MAX_LED;


		ClearAllLed();
		for (u32 n=0;n<max;n++)
		{
			mdelay(3);
			SetLED(n,1);
		}

		return NO_ERROR;
	}

	eErrorTp SetSuccToLed()
		{
			for (u32 n=0;n<MAX_LED;n++)
			{
				SetLED(n,1);
			}

			return NO_ERROR;
		}

	private:
	TTYclass * TTYC;
	char rxbuf[100]={0};
	u32 ConvertSOC_Pincode(string pincode)
	{
		 //0102 port 1 pin 2
		if (pincode.size()!=4)
			return 0xffffffff;

		char cport[3];
		memcpy(cport,pincode.c_str(),2);
		cport[2]=0;

		char cpin[3];
		memcpy(cpin,&pincode.c_str()[2],2);
		cpin[2]=0;
		u16 port=atoi(cport);
		u16 pin=atoi(cpin);
		return (32*(port-1))+pin;

	}
	string ConvertMC_Pincode(string pincode)
	{	//PA01 port A pin 1
		if (pincode.size()!=4)
			return "";
		char cport[2];
		cport[0]=pincode.c_str()[1];
		cport[1]=0;

		char cpin[3];
		if (pincode.c_str()[2]=='0')
		{
			cpin[0]=pincode.c_str()[3];
			cpin[1]=0;
		}
		else
		{
			memcpy(cpin,&pincode.c_str()[2],2);
			cpin[2]=0;
		}

		return string_format("%s%s",cport,cpin);

	}


};



#endif /* GPIO_H_ */
