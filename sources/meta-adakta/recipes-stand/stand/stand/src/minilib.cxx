/*
 * minilib.cxx
 *
 *  Created on: 19 окт. 2017 г.
 *      Author: root
 */
#include "minilib.h"
#include <json/json.h>
sGlobalVar sGV;


eErrorTp SearchFile(const char * fname)
{

	FILE * fil=NULL;

	fil=fopen(fname,"rb");

	if (fil==NULL) return ERROR;

	fclose(fil);
	return NO_ERROR;
}


eErrorTp ReadConfig(char * ConfigName)
{

	u16 ngp=0;

	Json::Value root;

	std::ifstream config_doc(ConfigName, std::ifstream::binary);
	config_doc >> root;

	if (root["gpio"].isArray())
	{
		sGV.TestGpio=true;
		while(root["gpio"][ngp][0].isNull()==false)
		{
			strcpy(sGV.gpio[ngp].MCpin,root["gpio"][ngp][0].asCString());
			strcpy(sGV.gpio[ngp].SoCpin,root["gpio"][ngp][1].asCString());
			strcpy(sGV.gpio[ngp].SoCname,root["gpio"][ngp][2].asCString());
			strcpy(sGV.gpio[ngp].SoCpad,root["gpio"][ngp][3].asCString());
			//printf("Val %s\n",root["gpio"][ngp][0].asCString());
			ngp++;

		}
	}
	ngp=0;
	if (root["leds"].isArray())
		{

			while(root["leds"][ngp].isNull()==false)
			{
				strcpy(sGV.LED[ngp].MCpin,root["leds"][ngp].asCString());
			 //  printf("Val %s\n",root["leds"][ngp].asCString());
				ngp++;

			}
		}

	if (root["hdmi"].asBool())
	{
		sGV.TestHdmi=true;
		sGV.HdmiFrameBufferNum=root["hdmi_fb"].asUInt();
	}
	if (root["sata"].asBool())
	{
		sGV.TestSata=true;
		strcpy(sGV.SataDev,root["sata_dev"].asCString());
	}
	if (root["pcie"].asBool())
		sGV.TestPcie=true;

	if (root["ethernet"].asBool())
		sGV.TestEthernet=true;

	if (root["usb0"].asBool())
		sGV.TestUsb0=true;

	if (root["usb1"].asBool())
		sGV.TestUsb1=true;

	if (root["emmc"].asBool())
	{
		sGV.TestEmmc=true;
		strcpy(sGV.EmmcDev,root["emmc_dev"].asCString());
	}
	//printf("Val %s\n",root["gpio"][0][0].asCString());
	return NO_ERROR;
}



eErrorTp HDMI_Test(u32 fb)
{
	string str="fb-test -f "+to_string(fb);
	system(str.c_str());
	return NO_ERROR;
}

eErrorTp ShowMessage(eErrorTp err,stringstream  & result)
{

	result << endl << LINE_SEP << endl;
	if (err==NO_ERROR)
		result << "Success: device check success." << endl;
	else
		result << "Fault: device check fault!!!" << endl;

	result << "'";
	printf("Result \n[%s]\n",result.str().c_str());

	stringstream ss;
	u32 z=0;
	for (u32 n=0;n<result.str().size();n++)
	{
		if (result.str().c_str()[n]=='\n')
		{
			ss<<"\\n";
			continue;
		}
		ss<<result.str().c_str()[n];
	}

	string str=string_format("/bin/sh %s/show_message.sh %s",SCRIPT_PATH,ss.str().c_str());
	system(str.c_str());
	///BashResult("/opt/show_message.sh",ss.str().c_str());


	return NO_ERROR;
}

eErrorTp USB_test(stringstream  & result)
{
	eErrorTp err=NO_ERROR;

	result << endl << LINE_SEP << endl;
	if (BashResult(string_format("%s/test_usb.sh",SCRIPT_PATH).c_str(),"")=="0\n")
	{
		result << "Error: USB not detect device" << endl;
		err=ERROR;
	}
	else
	{
		result << "Checked: USB" << endl;
	}



	return err;
}

eErrorTp Eth_test(stringstream  & result)
{
	eErrorTp err=NO_ERROR;

	result << endl << LINE_SEP << endl;
	if (BashResult(string_format("%s/test_eth.sh",SCRIPT_PATH).c_str(),"")=="0\n")
		{
			result << "Error: Ethernet not worked" << endl;
			err=ERROR;
		}
		else
		{
			result << "Checked: Ethernet" << endl;
		}

	return err;
}

eErrorTp Sata_test(stringstream  & result)
{
	eErrorTp err=NO_ERROR;

	result << endl << LINE_SEP << endl;
	if (BashResult(string_format("%s/test_sata.sh",SCRIPT_PATH).c_str(),sGV.SataDev)=="0\n")
		{
			result << "Error: SATA not worked" << endl;
			err=ERROR;
		}
		else
		{
			result << "Checked: SATA" << endl;
		}

	return err;
}

eErrorTp Emmc_test(stringstream  & result)
{
	eErrorTp err=NO_ERROR;

	result << endl << LINE_SEP << endl;

	printf("Emmc dev %s\n",sGV.EmmcDev);

	if (BashResult(string_format("%s/test_emmc.sh",SCRIPT_PATH).c_str(),sGV.EmmcDev)=="0\n")
		{
			result << "Error: EMMC not worked" << endl;
			err=ERROR;
		}
		else
		{
			result << "Checked: EMMC" << endl;
		}

	return err;
}

eErrorTp Pcie_test(stringstream  & result)
{
	eErrorTp err=NO_ERROR;

	result << endl << LINE_SEP << endl;
	if (BashResult(string_format("%s/test_pcie.sh",SCRIPT_PATH).c_str(),"")=="0\n")
		{
			result << "Error: PCIE not worked" << endl;
			err=ERROR;
		}
		else
		{
			result << "Checked: PCIE" << endl;
		}

	return err;
}

string BashResult(char* cmd,char* args) {
	std::unique_ptr<char[]>buffer(new tmp_str_size());

    snprintf(buffer.get(),TMP_STR_SIZE,"/bin/sh %s %s",cmd,args);
    std::string result = "";

   // printf("Run: %s\n",buffer.get());
    FILE* pipe = popen(buffer.get(), "r");
    if (!pipe) throw printf("popen() failed!");
    try {
        while (!feof(pipe)) {
            if (fgets(buffer.get(), TMP_STR_SIZE, pipe) != NULL)
                result += buffer.get();
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}

std::string string_format(const std::string fmt, ...) {
    int size = 100;
    std::string str;
    va_list ap;
    while (1) {
        str.resize(size);
        va_start(ap, fmt);
        int n = vsnprintf((char *)str.c_str(), size, fmt.c_str(), ap);
        va_end(ap);
        if (n > -1 && n < size) {
            str.resize(n);
            return str;
        }
        if (n > -1)
            size = n + 1;
        else
            size *= 2;
    }
    return str;
}

void printhex(u8 * buf,u32 len,u16 loop)
{
 u32 i;
 u16 k=0;
u8 buf2[10];
 if (len<loop) loop=len;
 cout << "-S--------------------------------------------------" << endl;
 for (i=0;i<len;i++){
	 snprintf((char*)buf2,10,"[0x%02x]",buf[i]);
	cout << buf2;
	k++;
	if (k==loop) {
	  cout << endl;
	  k=0;
	}
 }
 if (k!=0) cout << endl;
 cout << "-F--------------------------------------------------" << endl;

}
