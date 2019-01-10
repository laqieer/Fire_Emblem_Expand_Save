#include "SRAM_Flash.h"

void WriteSramFast_Flash_Core(unsigned char *src, unsigned char *dst, unsigned int size)
{
	int i;
	
	if((unsigned int)dst < 0xE000000 || (unsigned int)dst + size > 0xE010000 || size == 0)
		return;
	GamePakWaitstateControl = GamePakWaitstateControl & 0xFFFC | 3;
	for(i = 0; i < size; i++)
	{		
		FLASH_BASE_HI = 0xAA;
		FLASH_BASE_LO = 0x55;
		FLASH_BASE_HI = 0xA0;
		dst[i] = src[i];
		while(dst[i] != src[i]);
	}
}

__attribute__((section(".WriteSramFast_Flash")))
void WriteSramFast_Flash(unsigned char *src, unsigned char *dst, unsigned int size)
{
	WriteSramFast_Flash_Core(src, dst, size);
}