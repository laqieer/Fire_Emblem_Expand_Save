// import FLASH1M_V102
// 不检查跨bank的情况，请自行保证传入参数的正确性，即不要跨bank读写和校验数据
// by laqieer
// 2019-1-14

#include "gba_memcpy.h"

#include "AgbFlash1M.h"
#include "AgbSramFast.h"

#define FLASH_SIZE	0x20000

#pragma long_calls
u16 IdentifyFlash_1M();
void WriteFlash(u8 *src,u8 *dst,u32 size);
#pragma long_calls_off

void callWriteFlash(u8 *src,u8 *dst,u32 size);
u16 callIdentifyFlash();

void ReadFlash_Wrapper(u8 *src, u8 *dst, u32 size);
u32 VerifyFlash_Wrapper(u8 *src,u8 *tgt,u32 size);
