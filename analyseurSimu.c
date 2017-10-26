#include <stdio.h>
#include <stdlib.h>
#include "statGlobal.h"
#include "trace.h"
#include "evt.h"
#include "analyse.h"


int main(/*TODO arg*/)
{
	FILE* fdTrace = ouvertureTrace("trace2650.txt");

	struct evt* newEvt;

	struct statGlobal stat;

	while((newEvt=nextEvt(fdTrace))!=NULL)
	{
		analyseGlobal(newEvt,&stat);
	}

	return 0;
}
