/*
******************************************************************************
**
**  File        : LinkerScript.ld
**
**  Author      : STM32CubeIDE
**
**  Abstract    : Linker script for STM32H7 series
**                      1024Kbytes FLASH
**                       800Kbytes RAM
**
**                Set heap size, stack size and stack location according
**                to application requirements.
**
**                Set memory bank area and size if external memory is used.
**
**  Target      : STMicroelectronics STM32
**
**  Distribution: The file is distributed as is without any warranty
**                of any kind.
**
*****************************************************************************
** @attention
**
** <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
** All rights reserved.</center></h2>
**
** This software component is licensed by ST under BSD 3-Clause license,
** the "License"; You may not use this file except in compliance with the
** License. You may obtain a copy of the License at:
**                        opensource.org/licenses/BSD-3-Clause
**
*****************************************************************************
*/

/* Entry Point */
ENTRY(Reset_Handler)

/* Highest address of the user mode stack */
_estack = ORIGIN(RAM_D1) + LENGTH(RAM_D1); /* end of "RAM_D1" Ram type memory */

_Min_Heap_Size = 0x200 ; /* required amount of heap  */
_Min_Stack_Size = 0x400 ; /* required amount of stack */

/* Memories definition */
MEMORY
{
  DTCMRAM (xrw)  : ORIGIN = 0x20000000, LENGTH = 128K
  ITCMRAM (xrw)  : ORIGIN = 0x00000000, LENGTH = 64K
  RAM_D1 (xrw)   : ORIGIN = 0x24000000, LENGTH = 256K
  RAM_D11 (xrw)  : ORIGIN = 0x24040000, LENGTH = 256K
  RAM_D2 (xrw)   : ORIGIN = 0x30000000, LENGTH = 288K
  RAM_D3 (xrw)   : ORIGIN = 0x38000000, LENGTH = 64K
  FLASH  (rx)    : ORIGIN = 0x08000000, LENGTH = 1024K    /* Memory is divided. Actual start is 0x08000000 and actual length is 2048K */  
}

/* Initial 32K Flash is used to store kernel functions and
 * initial 32K RAM is used to store kernel data. */
__privileged_functions_region_size__  = 32K;
__privileged_data_region_size__       = 32K;


__FLASH_segment_start__               = ORIGIN( FLASH );
__FLASH_segment_end__                 = __FLASH_segment_start__ + LENGTH( FLASH );

__SRAM_segment_start__                = ORIGIN( RAM_D1 );
__SRAM_segment_end__                  = __SRAM_segment_start__ + LENGTH( RAM_D1 );

__privileged_functions_start__        = __FLASH_segment_start__;
__privileged_functions_end__          = __FLASH_segment_start__ + __privileged_functions_region_size__;

__privileged_data_start__             = __SRAM_segment_start__;
__privileged_data_end__               = __SRAM_segment_start__ + __privileged_data_region_size__;


/* Sections */
SECTIONS
{
  /* The startup code and FreeRTOS kernel code are placed into privileged
   * flash. */
  .privileged_functions :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector)) /* Startup code */
    . = ALIGN(4);
    *(privileged_functions)
    . = ALIGN(4);
    FILL(0xDEAD);
    /* Ensure that non-privileged code is placed after the region reserved for
     * privileged kernel code. */
    /* Note that dot (.) actually refers to the byte offset from the start of
     * the current section (.privileged_functions in this case). As a result,
     * setting dot (.) to a value sets the size of the section. */
    . = __privileged_functions_region_size__;
  } >FLASH

  /* The program code and other data into "FLASH" Rom type memory */
  .text :
  {
    /* Place the FreeRTOS System Calls first in the unprivileged region. */
    . = ALIGN(4);
    __syscalls_flash_start__ = .;
    *(freertos_system_calls)
    __syscalls_flash_end__ = .;
    . = ALIGN(4);
    *(.text)           /* .text sections (code) */
    *(.text*)          /* .text* sections (code) */
    *(.glue_7)         /* glue arm to thumb code */
    *(.glue_7t)        /* glue thumb to arm code */
    *(.eh_frame)

    KEEP (*(.init))
    KEEP (*(.fini))

    . = ALIGN(4);
    _etext = .;        /* define a global symbols at end of code */
  } >FLASH

  /* Constant data into "FLASH" Rom type memory */
  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)         /* .rodata sections (constants, strings, etc.) */
    *(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
    . = ALIGN(4);
  } >FLASH

  .ARM.extab   : {
    . = ALIGN(4);
    *(.ARM.extab* .gnu.linkonce.armextab.*)
    . = ALIGN(4);
  } >FLASH

  .ARM : {
    . = ALIGN(4);
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
    . = ALIGN(4);
  } >FLASH

  .preinit_array     :
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
    . = ALIGN(4);
  } >FLASH

  .init_array :
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
    . = ALIGN(4);
  } >FLASH

  .fini_array :
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
    . = ALIGN(4);
  } >FLASH

  /* Used by the startup to initialize data */
  _sidata = LOADADDR(.privileged_data);

  /* FreeRTOS kernel data. */
  .privileged_data :
  {
    . = ALIGN(4);
    _sdata = .;        /* Create a global symbol at data start. */
    *(privileged_data)
    . = ALIGN(4);
    FILL(0xDEAD);
    /* Ensure that non-privileged data is placed after the region reserved for
     * privileged kernel data. */
    /* Note that dot (.) actually refers to the byte offset from the start of
     * the current section (.privileged_data in this case). As a result, setting
     * dot (.) to a value sets the size of the section. */
    . = __privileged_data_region_size__;
  } >RAM_D1 AT> FLASH

  /* Initialized data sections into "RAM_D1" Ram type memory */
  .data :
  {
    . = ALIGN(4);
    *(.data)           /* .data sections */
    *(.data*)          /* .data* sections */
    . = ALIGN(4); 
    _edata = .;        /* define a global symbol at data end */

  } >RAM_D1 AT> FLASH

  /* Uninitialized data section into "RAM_D1" Ram type memory */
  . = ALIGN(4);
  .bss :
  {
    /* This is used by the startup in order to initialize the .bss section */
    _sbss = .;         /* define a global symbol at bss start */
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)
    *(COMMON)

    . = ALIGN(4);
    _ebss = .;         /* define a global symbol at bss end */
    __bss_end__ = _ebss;
  } >RAM_D1

  /* User_heap_stack section, used to check that there is enough "RAM_D1" Ram  type memory left */
  ._user_heap_stack :
  {
    . = ALIGN(8);
    PROVIDE ( end = . );
    PROVIDE ( _end = . );
    . = . + _Min_Heap_Size;
    . = . + _Min_Stack_Size;
    . = ALIGN(8);
  } >RAM_D1
  
  


  /* Remove information from the compiler libraries */
  /DISCARD/ :
  {
    libc.a ( * )
    libm.a ( * )
    libgcc.a ( * )
  }

  .ARM.attributes 0 : { *(.ARM.attributes) }
}
