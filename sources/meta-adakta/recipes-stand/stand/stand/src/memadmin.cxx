/**
 * memadmin.cxx
 *
 * Author: gorchakov.ilya
 * Email: ilya.gorchakov@adakta.ru
 */

/**
 * The module provides an API for protecting the memory buffer from errors
 */

#include <memadmin.h>

eErrorTp CreateForFifoSendCast(BufHandler * buf,u32 size)
{

	return CreateBuf(buf,(size+sizeof(sInterThrMsgHeader))*2);
}

eErrorTp CreateBuf(BufHandler * buf,u32 size)
{
	InitBuf(buf);
	if (AllocBuf(buf,size)==ERROR) return ERROR;

	return NO_ERROR;
}

eErrorTp SafeMoveToStartPointerBuf(BufHandler * buf)
{
	buf->buf=buf->buf_base;
	buf->len=buf->base_len;

	return NO_ERROR;
}

eErrorTp SafeIncTotalLenBuf(BufHandler * buf, u32 inc)
{
	if (buf->free_size>=inc)
		{
			buf->base_len+=inc;
			buf->free_size-=inc;
			return NO_ERROR;
		}
	return ERROR;
}

eErrorTp SafeIncPointerBuf(BufHandler * buf, u32 inc)
{

	if (buf->free_size>=inc)
	{
		buf->buf+=inc;
		buf->len=0;
		return NO_ERROR;
	}

	return ERROR;
}

eErrorTp SafeMoveBuf(BufHandler * dstbuf, BufHandler * srcbuf, u32 srcmovesize)
{

	dstbuf->buf+=dstbuf->len;
	memcpy(dstbuf->buf,srcbuf->buf,srcmovesize);

	dstbuf->len=srcmovesize;
	dstbuf->base_len+=srcmovesize;
	srcbuf->len-=srcmovesize;
	srcbuf->buf+=srcmovesize;
	return NO_ERROR;
}


eErrorTp CopyFragmentBuf(BufHandler * dstbuf, BufHandler * srcbuf, u32 srcfragsize)
{

	if (srcbuf->len<srcfragsize)
	{
		CRIT_ERROR
		return ERROR;
	}

	if ((srcfragsize+dstbuf->buf)>(dstbuf->max_size+dstbuf->buf_base))
	{
		CRIT_ERROR
		return ERROR;
	}

	memcpy(&dstbuf->buf_base[dstbuf->base_len],srcbuf->buf,srcfragsize);
	dstbuf->len=srcfragsize;
	dstbuf->base_len+=srcfragsize;
	return NO_ERROR;
}

eErrorTp SafeCopyBufToBaseBuf(BufHandler * dstbuf)
{

	u8 * tmpbuf;

		if (dstbuf->len>dstbuf->max_size)
		{
			CRIT_ERROR;
			return ERROR;
		}

		tmpbuf=(u8*)calloc(dstbuf->len,1);//new u8[dstbuf->len];

		memcpy(tmpbuf,dstbuf->buf,dstbuf->len);
		memcpy(dstbuf->buf_base,tmpbuf,dstbuf->len);

		dstbuf->buf=dstbuf->buf_base;
		dstbuf->base_len=dstbuf->len;
		dstbuf->free_size=dstbuf->max_size-dstbuf->len;
		dstbuf->buf+=dstbuf->len;
		free(tmpbuf);//delete [] tmpbuf;

	return NO_ERROR;
}

u32 GetBufFreeSize(BufHandler * buf)
{
	if (buf->base_len>buf->max_size)
	{
		CRIT_ERROR;
		buf->base_len=buf->max_size;
		buf->buf=buf->buf_base;
		buf->len=0;
	}
	return buf->max_size-buf->base_len;
}


eErrorTp CopyToBuf(BufHandler * dstbuf, u8 * srcbuf, u32 srcsize)
{
	if (GetBufFreeSize(dstbuf)<srcsize)
	{
		CRIT_ERROR;
		return ERROR;
	}

	memcpy(dstbuf->buf,srcbuf,srcsize);

	dstbuf->base_len-=dstbuf->len;
	dstbuf->free_size+=dstbuf->len;

	dstbuf->len=srcsize;
	dstbuf->base_len+=srcsize;
	dstbuf->free_size-=srcsize;
	return NO_ERROR;
}

eErrorTp DelNByteToBuf(BufHandler * dstbuf, u32 count)
{
	if ((dstbuf->buf_base==NULL)||(count>dstbuf->base_len)) return ERROR;

	dstbuf->free_size+=1;
	dstbuf->base_len-=1;
	dstbuf->len-=1;

	return NO_ERROR;
}

eErrorTp AddToBuf(BufHandler * dstbuf, u8 * srcbuf, u32 srcsize)
{
	if ((dstbuf->buf_base==NULL)||(srcbuf==NULL)) return ERROR;

	if (GetBufFreeSize(dstbuf)<srcsize)
	{
		CRIT_ERROR;
		return ERROR;
	}

	dstbuf->buf+=dstbuf->len;
	memcpy(dstbuf->buf,srcbuf,srcsize);

	dstbuf->len=srcsize;
	dstbuf->base_len+=srcsize;
	dstbuf->free_size-=srcsize;

	return NO_ERROR;
}

eErrorTp BufClone(BufHandler * bufSrc,BufHandler * bufDst)
{
	memcpy(bufDst,bufSrc,sizeof(BufHandler));

	return NO_ERROR;
}

eErrorTp AllocBuf(BufHandler * buf,u32 size)
{
	if (buf->buf_base!=NULL)
	{
		CRIT_ERROR;
		return ERROR;
	}

	buf->buf_base=(u8*)calloc(size,1);//new u8[size];
	if (buf->buf_base==NULL)
	{
		CRIT_ERROR;
		return ERROR;
	}

	memset(buf->buf_base,0,size);
	buf->len=0;
	buf->base_len=0;
	buf->max_size=size;
	buf->free_size=size;
	buf->buf=buf->buf_base;
	return NO_ERROR;
}

eErrorTp IncreaseBufSize(BufHandler * buf,u32 size)
{
	if (buf->buf_base==NULL)
	{
		CRIT_ERROR;
		return ERROR;
	}

	u32 buf_offs=(u32)buf->buf-(u32)buf->buf_base;
	u8 * ptr=NULL;

	ptr=(u8*)realloc((char*)buf->buf_base,buf->max_size+size);

	if (ptr==NULL)
	{
		CRIT_ERROR;
		return ERROR;
	}

	buf->buf_base=ptr;
	buf->free_size+=size;
	buf->max_size+=size;

	buf->buf=&buf->buf_base[buf_offs];

	return NO_ERROR;
}

eErrorTp InitBuf(BufHandler * buf)
{
	buf->base_len=0;
	buf->buf=NULL;
	buf->buf_base=NULL;
	buf->free_size=0;
	buf->len=0;
	buf->max_size=0;
	return NO_ERROR;
}

eErrorTp ClearBuf(BufHandler * buf)
{
	buf->base_len=0;
	buf->buf=buf->buf_base;
	buf->free_size=buf->max_size;
	buf->len=0;
	return NO_ERROR;
}

eErrorTp BufToBufHandler(BufHandler * dstbuf, u8 * sbuf,u32 sbuf_len, u32 maxsize)
{
	if (sbuf==NULL)
	{
		CRIT_ERROR;
		return ERROR;
	}
	dstbuf->free_size=maxsize-sbuf_len;
	dstbuf->buf_base=sbuf;
	dstbuf->len=sbuf_len;
	dstbuf->base_len=sbuf_len;
	dstbuf->max_size=maxsize;
	dstbuf->buf=dstbuf->buf_base;
	return NO_ERROR;
}

eErrorTp TestIsFreeBuf(BufHandler * buf)
{
	if (buf->buf_base!=NULL) return ERROR;
	return NO_ERROR;
}

eErrorTp TestIsBufAllocated(BufHandler * buf)
{
	if (buf->buf_base==NULL) return ERROR;
	return NO_ERROR;
}

eErrorTp FreeBuf(BufHandler * buf)
{
	if (buf->buf_base==NULL)
		return ERROR;

	free(buf->buf_base);
	buf->buf_base=NULL;
	buf->base_len=0;
	buf->len=0;
	buf->free_size=0;
	return NO_ERROR;
}
