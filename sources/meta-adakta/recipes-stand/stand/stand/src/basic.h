/**
 * basic.h
 *
 * Author: gorchakov.ilya
 * Email: ilya.gorchakov@adakta.ru
 */

/**
 * Basic declarations
 */

//Basic header

#ifndef BASIC_H_
#define BASIC_H_

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <memory.h>
#include <list>
#include <algorithm>
#include <string>
#include <bitset>
using namespace std;
#include <cstring>
#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <functional>

#include <stdio.h>
#include <sys/statvfs.h>
#include <getopt.h>
#include <unistd.h>
#include <sys/stat.h>
#include <termio.h>
#include <fstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <linux/ip.h>
#include <sys/ioctl.h>
#include <stdarg.h>
#include <sys/time.h>
#include <sys/times.h>
#include <linux/icmp.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include <ftw.h>
#include <math.h>
#include <time.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <memory>

#define mdelay(a) usleep(a*1000)
#define delay(a) sleep(a)
#define Mutex_t pthread_mutex_t
#define mutex_init(a) pthread_mutex_init(&a,NULL);
#define mutex_lock(a) pthread_mutex_lock(&a);
#define mutex_unlock(a) pthread_mutex_unlock(&a);
#define Thread_t pthread_t
#define FLOAT_SEPARATOR '.'

#ifndef DEFSTDTYPE
typedef unsigned int u32;
typedef unsigned long long int u64;
typedef unsigned int uint32_t;
typedef unsigned int uint_32;
typedef unsigned short u16;
typedef unsigned short uint16_t;
typedef unsigned short uint_16;
typedef unsigned char u8;

typedef const char c8;
typedef unsigned char uint8_t;
typedef unsigned char uint_8;
typedef unsigned char u_int8_t;
typedef unsigned short u_int16_t;
#endif

#define TMP_STR_SIZE 500
using tmp_str_size = char[TMP_STR_SIZE];


typedef struct __Leds{
	char MCpin[10];
};

typedef struct __ModuleGpioMap{
	char MCpin[10];
	char SoCpin[10];
	char SoCname[100];
	char SoCpad[5];
}__ModuleGpioMap;

#define MAX_RCV_CLNT_BUF 0xffff
#define MAX_RCV_CLNT_OVER_SIZE MAX_RCV_CLNT_BUF*4
#define MAX_RCV_CLNT_BUF32 (MAX_RCV_CLNT_BUF>>2)
typedef enum {NO_USE,NORMAL_LEVEL,MEDIUM_LEVEL,HARD_LEVEL,PARANOIDAL_LEVEL} eDebugTp;
typedef enum {entUDP,entTCP} eTransportTp;
typedef enum {sockNO_INIT,sock_CONNECT,sock_DISCONNECT} eSockStatTp;
typedef enum {RUN,QUIT} eQuitTp;
typedef enum {ERROR1=-1,NO_ERROR=0,ERROR=1} eErrorTp;
typedef enum {pdSOC,pdMC} sPinDev;
//Thread type ID
typedef enum {srvtUNDEF,srvtHelper,srvtInterplay,srvtAudio,srvtARCHI,srvtPARAMS,srvtControllerProto,srvtVideoProcess,srvtUNDEF1,srvtEmu,srvtMAX} eSrvTypeTp;

#pragma pack(push, 1)


#define PROGRAMM_NAME "stand"
#define MIN_BUSY_TCPUDP_QUEUE_SIZE 20000


#pragma pack(pop)
#endif /* BASIC_H_ */
