#include "gba_memcpy.h"

void *gba_memcpy(void *dest, void *src, unsigned int count)
{
	if(count && (count & 31 == 0) && ((u32)src & 3 == 0) && ((u32)dest & 3 == 0))
		CpuFastCopy(src, dest, count);
	else
		memcpy(dest, src, count);
}