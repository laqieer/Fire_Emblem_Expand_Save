// import 512K flash driver
// by laqieer
// 2019-1-11

#include "gba_memcpy.h"

#include "AgbFlash.h"
#include "AgbSramFast.h"

#define FLASH_SIZE	0x10000
#define SECTOR_SIZE	4096

u32 VerifyFlashSector_Core(u8 *src,u8 *tgt,u32 size);

#pragma long_calls
u16 IdentifyFlash();
void WriteFlash(u8 *src,u8 *dst,u32 size);
#pragma long_calls_off

void callWriteFlash(u8 *src,u8 *dst,u32 size);
u16 callIdentifyFlash();