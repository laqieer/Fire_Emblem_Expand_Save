// import FLASH1M_V103
// by laqieer
// 2019-1-15

#include "gba_memcpy.h"
#include "flash_internal.h"

#define FLASH_SECTOR_SIZE	4096

extern void (*ReadSramFast)(u8 *src,u8 *dst,u32 size);
extern u32 (*VerifySramFast)(u8 *src,u8 *tgt,u32 size);

#pragma long_calls
extern u16 IdentifyFlash();
void WriteFlash(u8 *src,u8 *dst,u32 size);
#pragma long_calls_off

void callWriteFlash(u8 *src,u8 *dst,u32 size);
u16 callIdentifyFlash();

void ReadFlash_Wrapper(u8 *src, u8 *dst, u32 size);
u32 VerifyFlash_Wrapper(u8 *src,u8 *tgt,u32 size);
