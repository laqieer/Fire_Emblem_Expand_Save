#include "flash_driver_1M_v103.h"

__attribute__((section(".libraryIdentifier")))
const char libraryIdentifier[] = "FLASH1M_V10";

void (**FlashTimerIntrFunc)(void) = NULL;

void WriteFlash(u8 *src, u8 *dst, u32 size)
{
	u8 sector_buffer[FLASH_SECTOR_SIZE];
	u32 addr_WRAM;
	u32 addr_Flash;
	u32 byte_number;
	int sector_number_start;
	int sector_number_end;
	int i;
	
	addr_WRAM = (u32)src;
	addr_Flash = (u32)dst;
	
	if(addr_Flash < (u32)FLASH_BASE || addr_Flash + size > (u32)FLASH_BASE + FLASH_ROM_SIZE_1M || size == 0)
		return;
	
	sector_number_start = (addr_Flash - (u32)FLASH_BASE) / FLASH_SECTOR_SIZE;
	sector_number_end = (addr_Flash + size - 1 - (u32)FLASH_BASE) / FLASH_SECTOR_SIZE;
	
	SetFlashTimerIntr(2, FlashTimerIntrFunc);
	
	// start sector
    if(addr_Flash + size > (u32)FLASH_BASE + FLASH_SECTOR_SIZE * (sector_number_start + 1))
        byte_number = (u32)FLASH_BASE + FLASH_SECTOR_SIZE * (sector_number_start + 1) - addr_Flash;
    else
        byte_number = size;
    ReadFlash(sector_number_start, 0, sector_buffer, FLASH_SECTOR_SIZE);
    gba_memcpy(&sector_buffer[addr_Flash - (u32)FLASH_BASE - FLASH_SECTOR_SIZE * sector_number_start], src, byte_number);
    (*ProgramFlashSector)(sector_number_start, sector_buffer);
    
    // middle sectors
    if(sector_number_end > sector_number_start + 1)
        for(i = sector_number_start + 1; i <= sector_number_end - 1; i++)
            (*ProgramFlashSector)(i, src + byte_number + FLASH_SECTOR_SIZE * (i - sector_number_start - 1));
    
    // end sector
    if(sector_number_end > sector_number_start)
    {
        ReadFlash(sector_number_end, 0, sector_buffer, FLASH_SECTOR_SIZE);
        gba_memcpy(sector_buffer, src + byte_number + FLASH_SECTOR_SIZE * (sector_number_end - sector_number_start - 1), size - byte_number - FLASH_SECTOR_SIZE * (sector_number_end - sector_number_start - 1));
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
	ReadFlash(((u32)src - (u32)FLASH_BASE) / FLASH_SECTOR_SIZE, ((u32)src - (u32)FLASH_BASE) % FLASH_SECTOR_SIZE, dst, size);
}

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