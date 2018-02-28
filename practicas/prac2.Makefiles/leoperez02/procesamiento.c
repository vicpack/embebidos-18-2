#include <stdio.h>
#include "defs.h"
#include <math.h>

void genera_seno(float seno[])
{
	register int n;
	float f,fs;
	f = 1000;
	fs = 45000;
	for(n = 0 ; n < MUESTRAS ; n++)
	{
		seno[n] = sinf(2*M_PI*f*n/fs);
	}
}
