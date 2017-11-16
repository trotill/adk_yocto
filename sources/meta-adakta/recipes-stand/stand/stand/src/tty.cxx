/**
 * tty.cxx
 *
 * Author: gorchakov.ilya
 * Email: ilya.gorchakov@adakta.ru
 */

/**
 * Class for working with UART chip, provides wrapper for standard API
 */

#include "tty.h"


TTYclass::TTYclass(string & tty, u32 speed, u8 stopbit)
{

	struct termio stbuf;
	glbERROR=NO_ERROR;
	TTYFname=tty;
	comfd=-1;


	//GPRINT(MEDIUM_LEVEL,"Probe init [%s]\n",tty.c_str());
	if (TTYopen()==ERROR)
	{
		glbERROR=ERROR;
		return;
	}

	if (ioctl (comfd, TCGETA, &stbuf) < 0) {
		//GPRINT(NORMAL_LEVEL,"Not get TTY params\n");
		glbERROR=ERROR;
		return;
	  }

	int c_cflag=CS8|CREAD;

	if (speed==1000000) c_cflag|=B1000000;
	if (speed==921600) c_cflag|=B921600;
	if (speed==576000) c_cflag|=B576000;
	if (speed==500000) c_cflag|=B500000;
	if (speed==460800) c_cflag|=B460800;
	if (speed==230400) c_cflag|=B230400;
	if (speed==115200) c_cflag|=B115200;
	if (speed==9600) c_cflag|=B9600;
	if (speed==4800) c_cflag|=B4800;
	if (stopbit>1)
		c_cflag|=CSTOPB;

	stbuf.c_lflag    = 0;
	stbuf.c_iflag    = BRKINT;
	stbuf.c_oflag    = 0;
	stbuf.c_cflag    = c_cflag;
	stbuf.c_cc[VMIN] = 2;
	stbuf.c_cc[VTIME] = 1;


	if (ioctl(comfd, TCSETA, &stbuf) < 0) {
		//GPRINT(NORMAL_LEVEL,"Not set TTY params\n");
		glbERROR=ERROR;
		return;
	  }

	//GPRINT(NORMAL_LEVEL,"Init conrol port [%s]\n",tty.c_str());
	glbERROR=NO_ERROR;
	return;
}

TTYclass::~TTYclass(void)
{
	if (glbERROR==NO_ERROR)
	{
		if (comfd!=-1)
			TTYclose();
	}
}

eErrorTp TTYclass::TTYopen(void)
{


	if (comfd!=-1) return ERROR;

	if ((comfd = open(TTYFname.c_str(), O_RDWR|O_EXCL|O_NONBLOCK|O_NOCTTY)) <0)
	{
		printf("Not open port [%s]\n",TTYFname.c_str());
		return ERROR;
	}

	printf("Open port[%s]\n",TTYFname.c_str());


	return NO_ERROR;

}

void TTYclass::TTYclose(void)
{
	printf("close port[%s]\n",TTYFname.c_str());
	close(comfd);
	comfd=-1;
}

eErrorTp TTYclass::TTYClear(void)
{
	char buff;
	if (comfd==-1) return ERROR;
	tcflush(comfd, TCIFLUSH);
	return NO_ERROR;
}

eErrorTp TTYclass::TTYreadChar(u8 & buff)
{
	u32 i,j;
	int res;

	if (comfd==-1)
	{
		return ERROR;
	}
    //printf("try read\n");
	res=read(comfd,&buff,1);
	if (res==-1) return ERROR;


	//printhex(buff,1,16);
	return NO_ERROR;
}

eErrorTp TTYclass::TTYreadBuf(u8 * buff,u32 len)
{
	u32 i,j;
	int res;

	if (comfd==-1)
	{
		return ERROR;
	}
    //printf("try read\n");
	res=read(comfd,buff,len);


	if (res==-1) return ERROR;
	printhex(buff,res,16);

	//printhex(buff,1,16);
	return NO_ERROR;
}


eErrorTp TTYclass::TTYwriteChar(char & buff)
{
	u32 i,j;
	int res;
	if (comfd==-1) return ERROR;
	res=write(comfd,&buff,1);
	if (res==-1) return ERROR;

	return NO_ERROR;
}

eErrorTp TTYclass::TTYwriteBuf(char * buff, u32 len)
{
	u32 i,j;
	u32 res;
	if (comfd==-1) return ERROR;

	//printf("%s",buff);
	res=write(comfd,buff,len);
	if (res!=len) return ERROR;


	return NO_ERROR;
}


