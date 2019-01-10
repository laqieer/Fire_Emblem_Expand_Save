// Modify SRAM library functions in game
// by laqieer
// 2019-1-9

#pragma once

#include "AgbFlash.h"
#include <stddef.h>

char flash_sector_buffer[4096];
void (**gFlashTimerIntrFunc)(void) = 0;
void *memcpy(void *str1, const void *str2, size_t n);

#pragma long_calls
void SetSramFastFunc_Flash_Core();
void ReadSramFast_Flash_Core(unsigned char *src, unsigned char *dst, unsigned int size);
void WriteSramFast_Flash_Core(unsigned char *src, unsigned char *dst, unsigned int size);
unsigned int VerifySramFast_Flash_Core(unsigned char *src,unsigned char *tgt,unsigned int size);
#pragma long_calls_off

void SetSramFastFunc_Flash();
void ReadSramFast_Flash(unsigned char *src, unsigned char *dst, unsigned int size);
void WriteSramFast_Flash(unsigned char *src, unsigned char *dst, unsigned int size);
unsigned int VerifySramFast_Flash(unsigned char *src,unsigned char *tgt,unsigned int size);