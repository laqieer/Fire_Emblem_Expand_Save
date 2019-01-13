// memcpy implementation on GBA BIOS functions
// by laqieer
// 2019-01-13

#include "Agb.h"
#include <string.h>

// improve performance by GBA BIOS function CPUFastSet.
// CPUFastSet is implemented as repeated LDMIA/STMIA [Rb]!,r2-r9 instructions, so it can transfer in the unit of (4 * 8 = 32) bytes.
void *gba_memcpy(void *dest, void *src, unsigned int count);