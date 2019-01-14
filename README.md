# Fire_Emblem_Expand_Save

Fire Emblem on GBA use 32KB save.

## Native Save Type
* FE6 & FE7: Sram_F_v102
* FE8 : Sram_F_v103

This project is to expand it to 64KB/128KB. The save type is changed to FLASH 512K/1M.

## Extern library
* libagbbackup
* libgcc
* libc

## Compiler option
* SRAM_Flash & SRAM_Flash_1M : -O0
* others : -O2

## Patch Selection
### 64KB Save
* VBA-M & mgba : V0.0
* NO$GBA : V1.3 & Set "Options -> Emulation Setup -> Files -> GBA Cartridge Backup Media" to "FLASH 64K Atmel"
### 128KB Save
* VBA-M & mgba : V3.0
   * VBA-M : Set "Options -> Game Boy Advance -> Configure -> Save Type" to "Flash 128K" or click "Detect Now"
   * mgba: Set "Tools -> Game overrides -> Game Boy Advance -> Save Type" to "Flash 1Mb"