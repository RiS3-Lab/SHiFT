/*
 * GENERATED FILE - DO NOT EDIT
 * Copyright 2008-2013 Code Red Technologies Ltd,
 * Copyright 2013-2023 NXP
 * Generated linker script file for MK66FN2M0xxx18
 * Created from memory.ldt by FMCreateLinkMemory
 * Using Freemarker v2.3.30
 * MCUXpresso IDE v11.8.0 [Build 1165] [2023-07-26] on Oct 17, 2023, 11:57:09 PM
 */

MEMORY
{
  /* Define each memory region */
  PROGRAM_FLASH (rx) : ORIGIN = 0x0, LENGTH = 0x200000 /* 2M bytes (alias Flash) */  
  SRAM_UPPER (rwx) : ORIGIN = 0x20000000, LENGTH = 0x20000 /* 192K bytes (alias RAM)   128k for memory and 68k for shadow  */  
  SRAM_LOWER (rwx) : ORIGIN = 0x1fff0000, LENGTH = 0x10000 /* 64K bytes (alias RAM2) */  
  FLEX_RAM (rwx) : ORIGIN = 0x14000000, LENGTH = 0x1000 /* 4K bytes (alias RAM3) */  
}

  /* Define a symbol for the top of each memory region */
  __base_PROGRAM_FLASH = 0x0  ; /* PROGRAM_FLASH */  
  __base_Flash = 0x0 ; /* Flash */  
  __top_PROGRAM_FLASH = 0x0 + 0x200000 ; /* 2M bytes */  
  __top_Flash = 0x0 + 0x200000 ; /* 2M bytes */  
  __base_SRAM_UPPER = 0x20000000  ; /* SRAM_UPPER */  
  __base_RAM = 0x20000000 ; /* RAM */  
  __top_SRAM_UPPER = 0x20000000 + 0x20000 ; /* 192K bytes */  
  __top_RAM = 0x20000000 + 0x20000 ; /* 192K bytes */  
  __base_SRAM_LOWER = 0x1fff0000  ; /* SRAM_LOWER */  
  __base_RAM2 = 0x1fff0000 ; /* RAM2 */  
  __top_SRAM_LOWER = 0x1fff0000 + 0x10000 ; /* 64K bytes */  
  __top_RAM2 = 0x1fff0000 + 0x10000 ; /* 64K bytes */  
  __base_FLEX_RAM = 0x14000000  ; /* FLEX_RAM */  
  __base_RAM3 = 0x14000000 ; /* RAM3 */  
  __top_FLEX_RAM = 0x14000000 + 0x1000 ; /* 4K bytes */  
  __top_RAM3 = 0x14000000 + 0x1000 ; /* 4K bytes */  
