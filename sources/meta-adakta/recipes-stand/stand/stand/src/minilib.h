/*
 * minilib.h
 *
 *  Created on: 19 окт. 2017 г.
 *      Author: root
 */

#ifndef MINILIB_H_
#define MINILIB_H_
#include "basic.h"
#include "tty.h"
#include "memadmin.h"

#define LINE_SEP "--------------------"

#define MAX_GPIO 100

#define MAX_LED 12

#define SCRIPT_PATH "/etc/stand/test"

typedef struct sGlobalVar
{
	__ModuleGpioMap gpio[MAX_GPIO];
	__Leds LED[MAX_LED];
	bool TestHdmi;
	u32 HdmiFrameBufferNum;
	bool TestSata;
	bool TestGpio;
	bool TestPcie;
	bool TestEthernet;
	bool TestUsb0;
	bool TestUsb1;
	bool TestEmmc;
	bool TestNand;
	char EmmcDev[20];
	char SataDev[20];
	u32 progress;
}sGlobalVar;

extern sGlobalVar sGV;


typedef struct sGlobalVarString{
	string tty_port;
}sGlobalVarString;

extern sGlobalVarString sGVstr;

string string_format(const std::string fmt, ...);
void printhex(u8 * buf,u32 len,u16 loop);
string BashResult(char* cmd,char* args);;
eErrorTp Eth_test(stringstream  & result);
eErrorTp USB_test(stringstream  & result);
eErrorTp Nand_test(stringstream  & result);
eErrorTp Pcie_test(stringstream  & result);
eErrorTp Sata_test(stringstream  & result);
eErrorTp Emmc_test(stringstream  & result);
eErrorTp ShowMessage(eErrorTp err,stringstream  & result);
eErrorTp HDMI_Test(u32 fb);
eErrorTp ReadConfig(char * ConfigName);
eErrorTp SearchFile(const char * fname);

#endif /* MINILIB_H_ */
