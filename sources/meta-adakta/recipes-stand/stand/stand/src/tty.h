/**
 * tty.h
 *
 * Author: gorchakov.ilya
 * Email: ilya.gorchakov@adakta.ru
 */

/**
 * Header for tty.cxx
 */

#ifndef TTY_H_
#define TTY_H_

#include "stand.h"

///The class defines access to the COM port
class TTYclass {
	public:
		TTYclass(string & tty, u32 speed, u8 stopbit);
		~TTYclass(void);
		void TTYclose(void);
		eErrorTp TTYreadChar(u8 & buff);
		eErrorTp TTYreadBuf(u8 * buff,u32 len);
		eErrorTp TTYwriteChar(char & buff);
		eErrorTp TTYwriteBuf(char * buff, u32 len);
		eErrorTp TTYClear(void);
		int comfd;
		eErrorTp glbERROR;
	protected:
		string TTYFname;
		eErrorTp TTYopen(void);
};


#endif /* TTY_H_ */
