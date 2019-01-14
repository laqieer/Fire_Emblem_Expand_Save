#include "SRAM_Flash_1M.h"

__attribute__((section(".libraryIdentifier")))
const char libraryIdentifier[] = "FLASH1M_Vnn";

// Write Single Data Byte (all device types, except Atmel)
// The target memory location doesn't have been previously erased for VBA-M or mGBA.
void WriteSramFast_Flash_Core(unsigned char *src, unsigned char *dst, unsigned int size)
{
	int i;
	
	if((unsigned int)dst < 0xE000000 || (unsigned int)dst + size > 0xE010000)
		return;
	GamePakWaitstateControl = GamePakWaitstateControl & 0xFFFC | 3;
	for(i = 0; i < size; i++)
	{		
		// write byte command
		FLASH_BASE_HI = 0xAA;
		FLASH_BASE_LO = 0x55;
		FLASH_BASE_HI = 0xA0;
		// write byte to address
		dst[i] = src[i];
		// wait until writing completes
		while(dst[i] != src[i]);
	}
}

// Bank Switching (devices bigger than 64K only)
void WriteSramFast_Flash_1M_Core(unsigned char *src, unsigned char *dst, unsigned int size)
{
	if(size)
	{
		if((unsigned int)dst & 0x10000)
		{
			// select bank command
			FLASH_BASE_HI = 0xAA;
			FLASH_BASE_LO = 0x55;
			FLASH_BASE_HI = 0xB0;
			// write bank number 1
			FLASH_BASE = 1;
			
			WriteSramFast_Flash_Core(src, (unsigned int)dst & ~0x10000, size);
		}
		else if(((unsigned int)dst + size - 1) & 0x10000)
		{
			// Bank 0
			WriteSramFast_Flash_1M_Core(src, dst, 0xE010000 - (unsigned int)dst);
			// Bank 1
			WriteSramFast_Flash_1M_Core(src + 0xE010000 - (unsigned int)dst, 0xE000000, (unsigned int)dst + size - 0xE010000);
		}
		else
		{
			// select bank command
			FLASH_BASE_HI = 0xAA;
			FLASH_BASE_LO = 0x55;
			FLASH_BASE_HI = 0xB0;
			// write bank number 0
			FLASH_BASE = 0;
			
			WriteSramFast_Flash_Core(src, dst, size);
		}
	}
}

void ReadSramFast_Flash_1M(unsigned char *src, unsigned char *dst, unsigned int size)
{
	if(size)
	{
		if((unsigned int)src & 0x10000)
		{
			// select bank command
			FLASH_BASE_HI = 0xAA;
			FLASH_BASE_LO = 0x55;
			FLASH_BASE_HI = 0xB0;
			// write bank number 1
			FLASH_BASE = 1;
			
			(*ReadSramFast)((unsigned int)src & ~0x10000, dst, size);
		}
		else if(((unsigned int)src + size - 1) & 0x10000)
		{
			// Bank 0
			ReadSramFast_Flash_1M(src, dst, 0xE010000 - (unsigned int)src);
			// Bank 1
			ReadSramFast_Flash_1M(0xE000000, dst + 0xE010000 - (unsigned int)src, (unsigned int)src + size - 0xE010000);
		}
		else
		{
			// select bank command
			FLASH_BASE_HI = 0xAA;
			FLASH_BASE_LO = 0x55;
			FLASH_BASE_HI = 0xB0;
			// write bank number 0
			FLASH_BASE = 0;
			
			(*ReadSramFast)(src, dst, size);
		}
	}
}

unsigned int VerifySramFast_Flash_1M(unsigned char *src,unsigned char *tgt,unsigned int size)
{
	unsigned int errorAdr;
	
	if(size)
	{
		if((unsigned int)tgt & 0x10000)
		{
			// select bank command
			FLASH_BASE_HI = 0xAA;
			FLASH_BASE_LO = 0x55;
			FLASH_BASE_HI = 0xB0;
			// write bank number 1
			FLASH_BASE = 1;
			
			errorAdr = (*VerifySramFast)(src, (unsigned int)tgt & ~0x10000, size);
			if(errorAdr)
				errorAdr |= 0x10000;
		}
		else if(((unsigned int)tgt + size - 1) & 0x10000)
		{
			// Bank 0
			errorAdr = VerifySramFast_Flash_1M(src, tgt, 0xE010000 - (unsigned int)tgt);
			// Bank 1
			if(errorAdr == 0)
			{
				errorAdr = VerifySramFast_Flash_1M(src + 0xE010000 - (unsigned int)tgt, 0xE000000, (unsigned int)tgt + size - 0xE010000);
				if(errorAdr)
					errorAdr |= 0x10000;
			}
		}
		else
		{
			// select bank command
			FLASH_BASE_HI = 0xAA;
			FLASH_BASE_LO = 0x55;
			FLASH_BASE_HI = 0xB0;
			// write bank number 0
			FLASH_BASE = 0;
			
			errorAdr = (*VerifySramFast)(src, tgt, size);
		}
	}
	else
		errorAdr = tgt;
	
	return errorAdr;
}

__attribute__((section(".callWriteFlash")))
void WriteSramFast_Flash_1M(unsigned char *src, unsigned char *dst, unsigned int size)
{
	WriteSramFast_Flash_1M_Core(src, dst, size);
}