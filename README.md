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

## Patch versions
* v0.x: 64K, hand-written driver
* v1.x: 64K, official driver
* v2.x: 128K, hand-written driver
* v3.x: 128K, official driver
