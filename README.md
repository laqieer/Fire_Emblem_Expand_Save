# Fire_Emblem_Expand_Save

Fire Emblem on GBA use 32KB save.

## Native Save Type
* FE6 & FE7: Sram_F_v102
* FE8 : Sram_F_v103

This project is to expand it to 64KB/128KB. The save type is changed to FLASH 512K/1M.

## Extern library
* libagbbackup / [libgbabackup](https://github.com/laqieer/libgbabackup)
* libgcc & libc in devkitpro

## Patch versions
* v0.x: 64K, hand-written driver
* v1.x: 64K, official driver
   * v1.4: Flash_v123
   * v1.5: Flash512_v131
* v2.x: 128K, hand-written driver
* v3.x: 128K, official driver
   * v3.0: Flash1M_v102
   * v3.1: Flash1M_v103
