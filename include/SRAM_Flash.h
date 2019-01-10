// Modify SRAM library functions in game
// by laqieer
// 2019-1-9

#pragma once

extern volatile unsigned short GamePakWaitstateControl;
extern volatile unsigned char FLASH_BASE_HI;
extern volatile unsigned char FLASH_BASE_LO;

#pragma long_calls
void WriteSramFast_Flash_Core(unsigned char *src, unsigned char *dst, unsigned int size);
#pragma long_calls_off

void WriteSramFast_Flash(unsigned char *src, unsigned char *dst, unsigned int size);