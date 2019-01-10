#include "SRAM_Flash.h"

void SetSramFastFunc_Flash_Core()
{
	IdentifyFlash();
}

__attribute__((section(".SetSramFastFunc_Flash")))
void SetSramFastFunc_Flash()
{
	SetSramFastFunc_Flash_Core();
}

void ReadSramFast_Flash_Core(unsigned char *src, unsigned char *dst, unsigned int size)
{	
	if((unsigned int)src < 0xE000000 || (unsigned int)src + size > 0xE010000)
		return;
	ReadFlash(((unsigned int)src - 0xE000000) / 4096, ((unsigned int)src - 0xE000000) % 4096, dst, size);
}

__attribute__((section(".ReadSramFast_Flash")))
void ReadSramFast_Flash(unsigned char *src, unsigned char *dst, unsigned int size)
{
	ReadSramFast_Flash_Core(src, dst, size);
}

void WriteSramFast_Flash_Core(unsigned char *src, unsigned char *dst, unsigned int size)
{
	int i;
	size_t n;
	int first_sector;
	int last_sector;
	
	SetFlashTimerIntr(2, gFlashTimerIntrFunc);
	
	if((unsigned int)dst < 0xE000000 || (unsigned int)dst + size > 0xE010000)
		return;
	first_sector = ((unsigned int)dst - 0xE000000) / 4096;
	last_sector = ((unsigned int)dst + size - 0xE000000) / 4096;
	if(((unsigned int)dst + size - 0xE000000) % 4096)
		last_sector += 1;
	
	// first sector
	if((unsigned int)dst + size > 4096 * (first_sector + 1))
		n = 0xE000000 + 4096 * (first_sector + 1) - (unsigned int)dst;
	else
		n = size;
	ReadFlash(first_sector, 0, flash_sector_buffer,4096);
	memcpy(src, &flash_sector_buffer[(unsigned int)dst - 0xE000000 - 4096 * first_sector], n);
	ProgramFlashSector(first_sector, flash_sector_buffer);
	
	// other sectors
	if(last_sector > first_sector + 1)
		for(i = first_sector + 1; i <= last_sector - 1; i++)
			ProgramFlashSector(i, src + n + 4096 * (i - first_sector - 1));
	
	// last sector
	if(last_sector > first_sector)
	{
		ReadFlash(last_sector, 0, flash_sector_buffer, 4096);
		memcpy(src + n + 4096 * (last_sector - first_sector - 1), flash_sector_buffer, size - n - 4096 * (last_sector - first_sector - 1));
		ProgramFlashSector(last_sector, flash_sector_buffer);
	}
}

__attribute__((section(".WriteSramFast_Flash")))
void WriteSramFast_Flash(unsigned char *src, unsigned char *dst, unsigned int size)
{
	WriteSramFast_Flash_Core(src, dst, size);
}

unsigned int VerifySramFast_Flash_Core(unsigned char *src,unsigned char *tgt,unsigned int size)
{
	int i;
	size_t n;
	int first_sector;
	int last_sector;
	unsigned int errorAdr;
	
	if((unsigned int)tgt < 0xE000000 || (unsigned int)tgt + size > 0xE010000)
		return (unsigned int)tgt;
	first_sector = ((unsigned int)tgt - 0xE000000) / 4096;
	last_sector = ((unsigned int)tgt + size - 0xE000000) / 4096;
	if(((unsigned int)tgt + size - 0xE000000) % 4096)
		last_sector += 1;
	
	// first sector
	if((unsigned int)tgt + size > 4096 * (first_sector + 1))
		n = 0xE000000 + 4096 * (first_sector + 1) - (unsigned int)tgt;
	else
		n = size;
	ReadFlash(first_sector, 0, flash_sector_buffer,4096);
	memcpy(src, &flash_sector_buffer[(unsigned int)tgt - 0xE000000 - 4096 * first_sector], n);
	errorAdr = VerifyFlashSector(first_sector, flash_sector_buffer);
	if(errorAdr)
		return 0xE000000 + 4096 * first_sector;
	
	// other sectors
	if(last_sector > first_sector + 1)
		for(i = first_sector + 1; i <= last_sector - 1; i++)
		{
			errorAdr = VerifyFlashSector(i, src + n + 4096 * (i - first_sector - 1));
			if(errorAdr)
				return 0xE000000 + 4096 * i;
		}
	
	// last sector
	if(last_sector > first_sector)
	{
		ReadFlash(last_sector, 0, flash_sector_buffer, 4096);
		memcpy(src + n + 4096 * (last_sector - first_sector - 1), flash_sector_buffer, size - n - 4096 * (last_sector - first_sector - 1));
		errorAdr = VerifyFlashSector(last_sector, flash_sector_buffer);
		if(errorAdr)
			return 0xE000000 + 4096 * last_sector;
	}
}

__attribute__((section(".VerifySramFast_Flash")))
unsigned int VerifySramFast_Flash(unsigned char *src,unsigned char *tgt,unsigned int size)
{
	return VerifySramFast_Flash_Core(src, tgt, size);
}