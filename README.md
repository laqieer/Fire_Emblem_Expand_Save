# Fire_Emblem_Expand_Save

Fire Emblem on GBA use 32KB save.

## Native Save Type
* FE6 & FE7: Sram_F_v102
* FE8 : Sram_F_v103

This project is to expand it to 64KB. The save type is changed to FLASH 512K.

## Extern library
* libagbbackup
* libgcc
* libc

## Compiler option
* SRAM_Flash : -O0
* others : -O2

## Patch Selection
* VBA-M & mgba : V0.0
* NO$GBA : v1.3 & Set "GBA Cartridge Backup Media" to "FLASH 64K Atmel"