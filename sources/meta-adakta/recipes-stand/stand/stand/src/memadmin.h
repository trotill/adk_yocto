/**
 * memadmin.h
 *
 * Author: gorchakov.ilya
 * Email: ilya.gorchakov@adakta.ru
 */

/**
 * Description of the class for working with fifo buffers and description
 * prototypes of memadmin functions
 */

#ifndef MEMADMIN_H_
#define MEMADMIN_H_

#include <types.h>


#define FIFO_PREBUF_LEN MAX_RCV_CLNT_BUF
#define QCOUNT_MAX_SIZE 1000000
#define INTER_MSG_LEN_TYPE u32

#pragma pack(push, 1)
///Header of Inter-Thread Interaction Package
typedef struct sInterThrMsgHeader
{
	u8 SrvType;//eSrvTypeTp
	u8 MsgType;//eMsgTypeTp
}sInterThrMsgHeader;
#pragma pack(pop)

///The class describes the FIFO cell
class fifo_element
{
	public:
	fifo_element()
	{
		bufsize=0;
		buf=NULL;
	}

	u8 * GetBuf(u32 & size)
	{
		size=bufsize;
		return buf;
	}

	eErrorTp SetBuf(u8 * srcbuf,u32 size)
	{
	  try
	  {
		if (buf==NULL)
			buf=new u8 [size];
		else
		{
			delete [] buf;
			buf=new u8 [size];
		}
	  }
	  catch(bad_alloc)
	  {
		  buf=NULL;
		  bufsize=0;
		  return ERROR;
	  }

	  if (buf==NULL)
	  {
		  bufsize=0;
		  return ERROR;
	  }

	  bufsize=size;
	  memcpy(buf,srcbuf,bufsize);
	  return NO_ERROR;
	}
	~fifo_element()
	{
		if (buf!=NULL)
		{
			delete [] buf;
		}
		bufsize=0;
	}
	private:
	u8 * buf;
	u32 bufsize;
};

///The class describes a fifo that allows data to be exchanged between threads with a minimum overhead
class fragfifo
{
	public:
	u32 qcount;
	u32 qcount_bsize;
	u32 qcount_max_bsize;

		fragfifo()
		{
			fifo=new list<fifo_element>;
			qcount=0;
			qcount_max_bsize=QCOUNT_MAX_SIZE;
			qcount_bsize=0;
			fifo->push_back(felement);
			mutex_init(FifoMutex);
		}
		~fragfifo()
		{
			mutex_unlock(FifoMutex);
			fifo->clear();
			delete fifo;
		}
		eErrorTp PushBuf(u8 * buf, u32 size)
		{
			fifo_element * pfe;
			list<fifo_element>::iterator it;
			if ((qcount_bsize+size)>qcount_max_bsize)
				return ERROR;
			mutex_lock(FifoMutex);
			fifo->push_back(felement);
			it=fifo->end();

			it--;
			pfe=&*it;
			pfe->SetBuf(buf,size);
			qcount++;
			qcount_bsize+=size;
			mutex_unlock(FifoMutex);

			return NO_ERROR;
		}
		u8 * GetLastBuf(u32 & size)
		{
			fifo_element * pfe;
			list<fifo_element>::iterator it;
			u8 * buf;
			if (qcount<=0)
				return NULL;

			mutex_lock(FifoMutex);
			fifo->pop_front();
			it=fifo->begin();
			pfe=&*it;
			qcount--;
			buf=pfe->GetBuf(size);
			qcount_bsize-=size;
			mutex_unlock(FifoMutex);

			if (qcount_bsize<0)
				return NULL;

			return buf;
		}
		void ClearAll(void)
		{
			u32 size;
			while(GetLastBuf(size)!=NULL);
		}
		u32 GetCountElements()
		{
			return qcount;
		}
		int GetTotalSizeLastElements(u8 countElements)
		{
			u32 size=0;
			u32 getsz=0;
			fifo_element * pfe;
			list<fifo_element>::iterator it;

			mutex_lock(FifoMutex);

			if (qcount<(u32)(countElements+1))
			{
				mutex_unlock(FifoMutex);
				return 0;
			}

			u8 n=0;
			it=fifo->begin();
			it++;
			while(it!=fifo->end())
			{
				n++;
				pfe=&*it;
				pfe->GetBuf(getsz);
				size+=getsz;
				if (n>=countElements) break;
				it++;
			}

			mutex_unlock(FifoMutex);
			return size;
		}
	private:
		list<fifo_element> * fifo;
		Mutex_t FifoMutex;
		fifo_element felement;

};

///The structure stores a list of fifo created for the exchange between threads of different classes
typedef struct sListFifo
{
	fragfifo * FFifo[srvtMAX];
	Mutex_t FFmutex;
	bool FifosReady;
}sListFifo;

typedef struct BufHandler
{
	u32 free_size;
	u32 base_len;
	u32 max_size;
	u32 len;
	u8 * buf;
	u8 * buf_base;
}BufHandler;

u32 GetBufFreeSize(BufHandler * buf);
eErrorTp AddToBuf(BufHandler * dstbuf, u8 * srcbuf, u32 srcsize);
eErrorTp InitBuf(BufHandler * buf);
eErrorTp ClearBuf(BufHandler * buf);
eErrorTp AllocBuf(BufHandler * buf,u32 size);
eErrorTp FreeBuf(BufHandler * buf);
eErrorTp SafeMoveBuf(BufHandler * dstbuf, BufHandler * srcbuf, u32 srcmovesize);
eErrorTp SafeIncPointerBuf(BufHandler * buf, u32 inc);
eErrorTp SafeIncTotalLenBuf(BufHandler * buf, u32 inc);
eErrorTp SafeCopyBufToBaseBuf(BufHandler * dstbuf);
eErrorTp CopyFragmentBuf(BufHandler * dstbuf, BufHandler * srcbuf, u32 srcfragsize);
eErrorTp CopyToBuf(BufHandler * dstbuf, u8 * srcbuf, u32 srcsize);
eErrorTp BufClone(BufHandler * bufSrc,BufHandler * bufDst);
eErrorTp SafeMoveToStartPointerBuf(BufHandler * buf);
eErrorTp DelNByteToBuf(BufHandler * dstbuf, u32 count);

eErrorTp BufToBufHandler(BufHandler * dstbuf, u8 * sbuf,u32 sbuf_len, u32 maxsize);
eErrorTp IncreaseBufSize(BufHandler * buf,u32 size);
eErrorTp CreateBuf(BufHandler * buf,u32 size);
eErrorTp CreateForFifoSendCast(BufHandler * buf,u32 size);
eErrorTp TestIsFreeBuf(BufHandler * buf);
eErrorTp TestIsBufAllocated(BufHandler * buf);

#endif /* MEMADMIN_H_ */
