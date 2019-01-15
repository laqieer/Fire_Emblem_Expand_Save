// import 512K flash driver FLASH512_V131
// It doesn't support Atmel flash.
// by laqieer
// 2019-1-11

#include "gba_memcpy.h"

#include "AgbFlash512K.h"
#include "AgbSramFast.h"

#define FLASH_SIZE	0x10000
#define SECTOR_SIZE	4096

#pragma long_calls
u16 IdentifyFlash_512K();
void WriteFlash(u8 *src,u8 *dst,u32 size);
#pragma long_calls_off

void callWriteFlash(u8 *src,u8 *dst,u32 size);
u16 callIdentifyFlash();

void ReadFlash_Wrapper(u8 *src, u8 *dst, u32 size);
u32 VerifyFlash_Wrapper(u8 *src,u8 *tgt,u32 size);
