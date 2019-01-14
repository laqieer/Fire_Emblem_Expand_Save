#include "flash_driver.h"

__attribute__((section(".libraryIdentifier")))
const char libraryIdentifier[] = "FLASH_V123";

void (**FlashTimerIntrFunc)(void) = NULL;

void WriteFlash(u8 *src, u8 *dst, u32 size)
{
	u8 sector_buffer[4096];
	u32 addr_WRAM;
	u32 addr_Flash;
	u32 byte_number;
	int sector_number_start;
	int sector_number_end;
	int i;
	
	addr_WRAM = (u32)src;
	addr_Flash = (u32)dst;
	
	if(addr_Flash < FLASH_ADR || addr_Flash + size > FLASH_ADR + FLASH_SIZE || size == 0)
		return;
	
	sector_number_start = (addr_Flash - FLASH_ADR) / flash->sector.size;
	sector_number_end = (addr_Flash + size - 1 - FLASH_ADR) / flash->sector.size;
	
	SetFlashTimerIntr(2, FlashTimerIntrFunc);
	
	// start sector
    if(addr_Flash + size > FLASH_ADR + flash->sector.size * (sector_number_start + 1))
        byte_number = FLASH_ADR + flash->sector.size * (sector_number_start + 1) - addr_Flash;
    else
        byte_number = size;
    ReadFlash(sector_number_start, 0, sector_buffer, flash->sector.size);
    gba_memcpy(&sector_buffer[addr_Flash - FLASH_ADR - flash->sector.size * sector_number_start], src, byte_number);
    (*ProgramFlashSector)(sector_number_start, sector_buffer);
    
    // middle sectors
    if(sector_number_end > sector_number_start + 1)
        for(i = sector_number_start + 1; i <= sector_number_end - 1; i++)
            (*ProgramFlashSector)(i, src + byte_number + flash->sector.size * (i - sector_number_start - 1));
    
    // end sector
    if(sector_number_end > sector_number_start)
    {
        ReadFlash(sector_number_end, 0, sector_buffer, flash->sector.size);
        gba_memcpy(sector_buffer, src + byte_number + flash->sector.size * (sector_number_end - sector_number_start - 1), size - byte_number - flash->sector.size * (sector_number_end - sector_number_start - 1));
        (*ProgramFlashSector)(sector_number_end, sector_buffer);
    }
}

__attribute__((section(".callWriteFlash")))
void callWriteFlash(u8 *src, u8 *dst, u32 size)
{
	WriteFlash(src, dst, size);
}

void ReadFlash_Wrapper(u8 *src, u8 *dst, u32 size)
{
	ReadFlash(((u32)src - FLASH_ADR) / flash->sector.size, ((u32)src - FLASH_ADR) % flash->sector.size, dst, size);
}

// omit for speed
u32 VerifyFlash_Wrapper(u8 *src,u8 *tgt,u32 size)
{
	return 0;
}

__attribute__((section(".callIdentifyFlash")))
u16 callIdentifyFlash()
{
	ReadSramFast = ReadFlash_Wrapper;
	VerifySramFast = VerifyFlash_Wrapper;
	return IdentifyFlash();
}