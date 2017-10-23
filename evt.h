#ifndef __EVT_H__
#define __EVT_H__


struct evt
{
	double temps;
	int code;
	unsigned int pid;
	unsigned int fid;
	char* src;
	char* dst;
	char* pos;
}

#endif
