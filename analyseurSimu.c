#include <stdio.h>
#include <stdlib.h>
#include <statGlobal.h>
#include <trace.h>
#include <evt.h>


int main(/*TODO arg*/)
{
	FILE* fdTrace = ouvertureTrace("trace.out");

	struct evt* newEvt;
	while((newEvt=nextEvt(fdTrace))!=NULL)
	{
		
	}

	return 0;
}
