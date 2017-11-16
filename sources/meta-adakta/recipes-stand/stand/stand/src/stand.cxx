/**
 * srvDVR.cxx
 *
 * Author: gorchakov.ilya
 * Email: ilya.gorchakov@adakta.ru
 */

/**
 * Video server (DVR) supporting recording from 4 channels of cameras in full resolution for 2 storages simultaneously
 * with a link to telemetry information, which has a large pre-record, UART control and many useful features.
 */

//@
#include "stand.h"
#include <signal.h>
#include <pthread.h>
#include "gpio.h"
//#include "AMX6_0517.h"

pthread_mutex_t glbSigMutex;
string SERVER_CONFIG_FILE;

u16 GetProgVersion(void) {
    char s_month[5];
    int month, day, year;
    u16 version;
    static const char month_names[] = "JanFebMarAprMayJunJulAugSepOctNovDec";

    sscanf(__DATE__, "%s %d %d", s_month, &day, &year);

    month = (strstr(month_names, s_month)-month_names)/3;
    version=(year-2000)<<9|(month<<5)|(day);

    return version;
}


///help for info
void Help(void)
{
	u32 i;
	cout << PROGRAMM_NAME << " server V" << GetProgVersion() << " (" << __DATE__ << ")" << endl;
	cout << "This help " << endl;
	cout << "   opts --help" << endl;
	cout << "configuration file, default /stand.json" << endl;
	cout << "   opts --conf" <<endl;
	cout << "For example: " << PROGRAMM_NAME << " --conf=/stand.json" << endl;


	printf("------------------------------------------------------------\n");
}





void SigHandler(int snum)
{
	printf("%s:Catched signal %d\n",__FILE__,snum);
	printf("%s:SIGINT %d,SIGPIPE %d,SIGURG %d, SIGCHLD %d SIGTERM %d\n",__FILE__,SIGINT,SIGPIPE,SIGURG,SIGCHLD,SIGTERM);

	if (pthread_mutex_trylock(&glbSigMutex)!=0)
		printf("%s:SigHandler blocked\n",__FILE__);
	else
	{
		switch (snum) {
			case SIGPIPE: break;
			case SIGINT:
			case SIGTERM:
			case SIGKILL:

			break;
		}

		pthread_mutex_unlock(&glbSigMutex);
	}

}

///Signal config
void SigActionConfig(void)
{
	struct sigaction act;

	sigemptyset(&act.sa_mask);
	act.sa_handler=&SigHandler;
	act.sa_flags=0;

	sigset_t newset;
	sigemptyset(&newset);
	sigaddset(&newset, SIGPIPE);
	sigprocmask(SIG_BLOCK, &newset, 0);

	if (sigaction(SIGINT,&act,NULL)==-1){
		printf("%s:Signal SIGINT is blocked\n",__FILE__);
	}

	if (sigaction(SIGTERM,&act,NULL)==-1){
			printf("%s:Signal SIGTERM is blocked\n",__FILE__);
	}

	if (sigaction(SIGKILL,&act,NULL)==-1){
		printf("%s:Signal SIGKILL is blocked\n",__FILE__);
	}


	if (sigaction(SIGPIPE,&act,NULL)==-1){
		printf("%s:Signal SIGPIPE is blocked\n",__FILE__);
	}

	if (sigaction(SIGURG,&act,NULL)==-1){
		printf("%s:Signal SIGURG is blocked\n",__FILE__);
	}

}

eErrorTp ParseOpts(int argc, char *argv[])
{
	int c;
	u8 trig=0;

	static struct option long_options[] =
            {
              {"help",     no_argument,       0, 'h'},
              {"conf",  required_argument,       0, 'c'},
         //     {"debug",  required_argument,       0, 'd'},
              {0, 0, 0, 0}
            };
	 struct in_addr inp;
	 while (1)
	 {
		 int option_index = 0;

          c = getopt_long (argc, argv, "h:c",
                           long_options, &option_index);

          /* Detect the end of the options. */
          if (c == -1)
            break;

          switch (c)
            {
            case 0:

              /* If this option set a flag, do nothing else now. */
              if (long_options[option_index].flag != 0)
                break;
              cout << "option " << long_options[option_index].name;
              if (optarg)
                cout << "with arg " << optarg;
              cout << endl;
              break;

            case 'c':
            	if (optarg!=0)
            	{
            		if (SearchFile(optarg)!=ERROR)
            		{
            			SERVER_CONFIG_FILE=optarg;
            			trig=1;
            			 cout << "Found  conf " << SERVER_CONFIG_FILE << endl;
            		}
            		else
            			 cout << "Not found "<<optarg<<", use default conf " << SERVER_CONFIG_FILE << endl;
            	}
            	break;

            case 'h':

            case '?':
            	Help();
            	exit(0);
            	break;
              /* getopt_long already printed an error message. */
            default:
              printf("Incorrect options, exit\n");
              exit(0);
            }
	 }


   return NO_ERROR;
 }

//Установить режим для hdmi
//echo S:1920x1080p-60 > /sys/class/graphics/fb2/mode
int main(int argc, char *argv[])
{


	//*Далее тест для hdmi fb-test -f 2
	//*Добавить поддержку конфига борды
	//*Добавить тест sata и pcie
	//*Добавить индикацию ошибок на светодиоды
	//Допилить сборку, все...


	memset(&sGV,0,sizeof(sGV));

	//exit(1);

	SERVER_CONFIG_FILE="/stand.json";
	printf("Started stand v%d\n",GetProgVersion());
	ParseOpts(argc,argv);
	if (SearchFile(SERVER_CONFIG_FILE.c_str())==ERROR)
		exit(1);

	ReadConfig(SERVER_CONFIG_FILE.c_str());


	gpio g;
	u32 n=0;
	u8 err_level=0;
	stringstream msg;
	msg << "'";
	//g.SetPin("Pe12",1);
	//printf("Get 12 %d\n",g.GetPin("0100"));
	u32 res;
	eErrorTp err=NO_ERROR;

	system("killall -9 xmessage");

	g.ClearAllLed();
#if 0
	while(1)
		{



			//g.SetPin("0406",0);
			g.SetPin("0407",0);
			if (g.GetPin("Pe02",res)==ERROR)
				printf("error\n");
			else
			{
				if (res!=0)
				  printf("Err:Set 0 err %d Get %d\n",g.GetPin("Pe02",res),res);
			}
				//printf("success\n");
			//mdelay(200);
			//sleep(1);
			//printf("Set 0 err %d Get %d\n",g.GetPin("Pe02",res),res);
			//printf("Get 3 %d\n",g.GetPin("Pe03"));
			//sleep(1);
			g.SetPin("0407",1);
			if (g.GetPin("Pe02",res)==ERROR)
				printf("error\n");
			else
			{
			//sleep(1);
				if (res!=1)
					printf("Set 1 err %d Get %d\n",g.GetPin("Pe02",res),res);
			}
		}
#endif
	//exit(1);

	if ((sGV.TestHdmi)&&(HDMI_Test(sGV.HdmiFrameBufferNum)==ERROR)) err=ERROR;
		g.SetLED(sGV.progress++,1);
	if ((sGV.TestUsb0)&&(USB_test(msg)==ERROR)) err=ERROR;
		g.SetLED(sGV.progress++,1);
	if ((sGV.TestEthernet)&&(Eth_test(msg)==ERROR)) err=ERROR;
		g.SetLED(sGV.progress++,1);
	if ((sGV.TestSata)&&(Sata_test(msg)==ERROR)) err=ERROR;
		g.SetLED(sGV.progress++,1);
	if ((sGV.TestEmmc)&&(Emmc_test(msg)==ERROR)) err=ERROR;
		g.SetLED(sGV.progress++,1);
	if ((sGV.TestPcie)&&(Pcie_test(msg)==ERROR)) err=ERROR;
		g.SetLED(sGV.progress++,1);

	if (err==ERROR)
		err_level=1;


	if ((sGV.TestGpio)&&(g.RunGpioTest(sGV.gpio,msg)==ERROR))
		{

			if (err==ERROR)
				err_level=3;
			else
				err_level=2;

			err=ERROR;
		}

	g.SetLED(sGV.progress++,1);



	if (ShowMessage(err,msg)==ERROR) err=ERROR;

	printf("Test end\n");
	while(1)
	{
		if (err==ERROR)
		{
			g.ClearAllLed();
			mdelay(150);
			g.SetErrorToLed(err_level);
			mdelay(100);
		}
	}

	//exit(1);
#if 0
	while(1)
	{



		//g.SetPin("0406",0);
		g.SetPin("0407",0);
		printf("Get %d\n",g.GetPin("Pe02"));
		//printf("Get 3 %d\n",g.GetPin("Pe03"));
		sleep(1);

		//g.SetPin("0406",1);
		g.SetPin("0407",1);
		printf("Get %d\n",g.GetPin("Pe02"));
		//printf("Get 3 %d\n",g.GetPin("Pe03"));
		sleep(1);
		//g.SetPin("PB00",0);

		//g.RunGpioTest(MM_AMX6_0517);
		//exit(1);

		//g.SetPin("0422",1);


		//g.SetPin("Pb00",1);

		//g.SetPin("Pb05",0);

		//sleep(1);
		g.SetPin("0102",0);
		if (g.GetPin("Pe06")!=0)
			printf("Error\n");

		//printf("get [%d]\n",g.GetPin("Pe06"));

		g.SetPin("0102",1);
		if (g.GetPin("Pe06")!=1)
			printf("Error\n");

		n++;

		sleep(1);
		printf("Port A %08x\n",g.GetPort("Pa"));
		printf("Port B %08x\n",g.GetPort("Pb"));
		printf("Port C %08x\n",g.GetPort("Pc"));
		printf("Port D %08x\n",g.GetPort("Pd"));
		printf("Port E %08x\n",g.GetPort("Pe"));
		if ((n%1000)==0)
		{
			printf("Total %d\n",n);
		}
		//printf("get [%d]\n",g.GetPin("Pe06"));
#endif
#if 0
		//printf("get [%d]\n",g.GetPin("Pb05"));
#if 0
		printf("Set pin MC, Get IMX\n");
		g.SetPin("Pe06",0);
		printf("get [%d]\n",g.GetPin("0102"));

		mdelay(100);
		g.SetPin("Pe06",1);
		mdelay(100);
		printf("get [%d]\n",g.GetPin("0102"));

		printf("-----------------------------\n");
#endif
		printf("Set pin IMX, Get MC\n");
		mdelay(100);
		g.GetPin("Pe06");
		g.SetPin("0102",0);
		mdelay(100);
		printf("get [%d]\n",g.GetPin("Pe06"));
		mdelay(100);
		g.GetPin("Pe06");
		g.SetPin("0102",0);

		printf("get [%d]\n",g.GetPin("Pe06"));
		printf("-----------------------------\n");
#endif


}
