// Modify SRAM library functions to support 1M Flash save for VBA-M & mGBA
// VBA-M : Options -> Game Boy Advance -> Configure -> Save Type -> Flash -> 128K or Detect Now
// mGBA : Tools -> Game overrides -> Game Boy Advance -> Save Type -> Flash 1Mb -> load the game
// by laqieer
// 2019-1-14

#pragma once

extern volatile unsigned short GamePakWaitstateControl;
extern volatile unsigned char FLASH_BASE;
extern volatile unsigned char FLASH_BASE_HI;
extern volatile unsigned char FLASH_BASE_LO;

extern void (*ReadSramFast)(unsigned char *src,unsigned char *dst,unsigned int size);
extern unsigned int (*VerifySramFast)(unsigned char *src,unsigned char *tgt,unsigned int size);

#pragma long_calls
void WriteSramFast_Flash_1M_Core(unsigned char *src, unsigned char *dst, unsigned int size);
#pragma long_calls_off

void WriteSramFast_Flash_1M(unsigned char *src, unsigned char *dst, unsigned int size);
void ReadSramFast_Flash_1M(unsigned char *src, unsigned char *dst, unsigned int size);
unsigned int VerifySramFast_Flash_1M(unsigned char *src,unsigned char *tgt,unsigned int size);