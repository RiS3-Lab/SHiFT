/*
 * GENERATED FILE - DO NOT EDIT
 * Copyright 2008-2013 Code Red Technologies Ltd,
 * Copyright 2013-2023 NXP
 * Generated linker script file for MIMXRT1176xxxxx
 * Created from memory.ldt by FMCreateLinkMemory
 * Using Freemarker v2.3.30
 * MCUXpresso IDE v11.8.0 [Build 1165] [2023-07-26] on Sep 15, 2023, 12:38:32 AM
 */

MEMORY
{
  /* Define each memory region */
  BOARD_FLASH (rx) : ORIGIN = 0x30000000, LENGTH = 0x1000000 /* 16M bytes (alias Flash) */  
  SRAM_DTC_cm7 (rwx) : ORIGIN = 0x20000000, LENGTH = 0x40000 /* 256K bytes (alias RAM) */  
  SRAM_ITC_cm7 (rwx) : ORIGIN = 0x0, LENGTH = 0x40000 /* 256K bytes (alias RAM2) */  
  SRAM_ITC_cm4 (rwx) : ORIGIN = 0x1ffe0000, LENGTH = 0x20000 /* 128K bytes (alias RAM3) */  
  SRAM_OC1 (rwx) : ORIGIN = 0x20240000, LENGTH = 0x80000 /* 512K bytes (alias RAM4) */  
  SRAM_OC2 (rwx) : ORIGIN = 0x202c0000, LENGTH = 0x40000 /* 256K bytes (alias RAM5) */  
  NCACHE_REGION (rwx) : ORIGIN = 0x20300000, LENGTH = 0x40000 /* 256K bytes (alias RAM6) */  
  SRAM_OC_ECC1 (rwx) : ORIGIN = 0x20340000, LENGTH = 0x10000 /* 64K bytes (alias RAM7) */  
  SRAM_OC_ECC2 (rwx) : ORIGIN = 0x20350000, LENGTH = 0x10000 /* 64K bytes (alias RAM8) */  
  BOARD_SDRAM (rwx) : ORIGIN = 0x80000000, LENGTH = 0x4000000 /* 64M bytes (alias RAM9) */  
}

  /* Define a symbol for the top of each memory region */
  __base_BOARD_FLASH = 0x30000000  ; /* BOARD_FLASH */  
  __base_Flash = 0x30000000 ; /* Flash */  
  __top_BOARD_FLASH = 0x30000000 + 0x1000000 ; /* 16M bytes */  
  __top_Flash = 0x30000000 + 0x1000000 ; /* 16M bytes */  
  __base_SRAM_DTC_cm7 = 0x20000000  ; /* SRAM_DTC_cm7 */  
  __base_RAM = 0x20000000 ; /* RAM */  
  __top_SRAM_DTC_cm7 = 0x20000000 + 0x40000 ; /* 256K bytes */  
  __top_RAM = 0x20000000 + 0x40000 ; /* 256K bytes */  
  __base_SRAM_ITC_cm7 = 0x0  ; /* SRAM_ITC_cm7 */  
  __base_RAM2 = 0x0 ; /* RAM2 */  
  __top_SRAM_ITC_cm7 = 0x0 + 0x40000 ; /* 256K bytes */  
  __top_RAM2 = 0x0 + 0x40000 ; /* 256K bytes */  
  __base_SRAM_ITC_cm4 = 0x1ffe0000  ; /* SRAM_ITC_cm4 */  
  __base_RAM3 = 0x1ffe0000 ; /* RAM3 */  
  __top_SRAM_ITC_cm4 = 0x1ffe0000 + 0x20000 ; /* 128K bytes */  
  __top_RAM3 = 0x1ffe0000 + 0x20000 ; /* 128K bytes */  
  __base_SRAM_OC1 = 0x20240000  ; /* SRAM_OC1 */  
  __base_RAM4 = 0x20240000 ; /* RAM4 */  
  __top_SRAM_OC1 = 0x20240000 + 0x80000 ; /* 512K bytes */  
  __top_RAM4 = 0x20240000 + 0x80000 ; /* 512K bytes */  
  __base_SRAM_OC2 = 0x202c0000  ; /* SRAM_OC2 */  
  __base_RAM5 = 0x202c0000 ; /* RAM5 */  
  __top_SRAM_OC2 = 0x202c0000 + 0x40000 ; /* 256K bytes */  
  __top_RAM5 = 0x202c0000 + 0x40000 ; /* 256K bytes */  
  __base_NCACHE_REGION = 0x20300000  ; /* NCACHE_REGION */  
  __base_RAM6 = 0x20300000 ; /* RAM6 */  
  __top_NCACHE_REGION = 0x20300000 + 0x40000 ; /* 256K bytes */  
  __top_RAM6 = 0x20300000 + 0x40000 ; /* 256K bytes */  
  __base_SRAM_OC_ECC1 = 0x20340000  ; /* SRAM_OC_ECC1 */  
  __base_RAM7 = 0x20340000 ; /* RAM7 */  
  __top_SRAM_OC_ECC1 = 0x20340000 + 0x10000 ; /* 64K bytes */  
  __top_RAM7 = 0x20340000 + 0x10000 ; /* 64K bytes */  
  __base_SRAM_OC_ECC2 = 0x20350000  ; /* SRAM_OC_ECC2 */  
  __base_RAM8 = 0x20350000 ; /* RAM8 */  
  __top_SRAM_OC_ECC2 = 0x20350000 + 0x10000 ; /* 64K bytes */  
  __top_RAM8 = 0x20350000 + 0x10000 ; /* 64K bytes */  
  __base_BOARD_SDRAM = 0x80000000  ; /* BOARD_SDRAM */  
  __base_RAM9 = 0x80000000 ; /* RAM9 */  
  __top_BOARD_SDRAM = 0x80000000 + 0x4000000 ; /* 64M bytes */  
  __top_RAM9 = 0x80000000 + 0x4000000 ; /* 64M bytes */  
  
  
  /* Initial 32K Flash is used to store kernel functions and
 * initial 32K RAM is used to store kernel data. */
__privileged_functions_region_size__  = 32K;
__privileged_data_region_size__       = 32K;
__unprivileged_data_region_size__     = 32K;
__BSS_region_start__     = 128K;

__FLASH_segment_start__               = ORIGIN( BOARD_FLASH );
__FLASH_segment_end__                 = __FLASH_segment_start__ + LENGTH( BOARD_FLASH );

__SRAM_segment_start__                = ORIGIN( SRAM_DTC_cm7 );
__SRAM_segment_end__                  = __SRAM_segment_start__ + LENGTH( SRAM_DTC_cm7 );

__privileged_functions_start__        = __FLASH_segment_start__;
__privileged_functions_end__          = __FLASH_segment_start__ + __privileged_functions_region_size__;

__privileged_data_start__             = __SRAM_segment_start__;
__privileged_data_end__               = __SRAM_segment_start__ + __privileged_data_region_size__;
  
  
  
  
