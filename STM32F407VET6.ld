/*
    STM32F407VET6 Linker Script (512KB Flash)
    Reserved last 128KB sector (Sector 7) for settings.
*/

/* On devices with 256K RAM, use additional memory SRAM3. */
/* STM32F40x do not have SRAM3 */
RAM3_SIZE = 0;

/* SDRAM */
SDRAM_SIZE = 0;

/* change address & length if bootloader */
bootloader_size = 0k;
flash_start = 0x08000000;

/* Force 512KB total, but reserve 128KB for settings */
/* 512KB - 128KB (Sector 7) = 384KB available for firmware */
flash_size = 384k;
image_size = flash_size;

/* OpenBLT <-> main FW shared area */
_OpenBLT_Shared_Params_Size = 0;

MEMORY
{
    flash0  : org = flash_start, len = image_size
    flash1  : org = 0x00000000, len = 0
    flash2  : org = 0x00000000, len = 0
    flash3  : org = 0x00000000, len = 0
    flash4  : org = 0x00000000, len = 0
    flash5  : org = 0x00000000, len = 0
    flash6  : org = 0x00000000, len = 0
    flash7  : org = 0x00000000, len = 0
    shared  : org = 0x20000000, len = _OpenBLT_Shared_Params_Size
    ram0    : org = 0x20000000 + _OpenBLT_Shared_Params_Size, len = 128k - _OpenBLT_Shared_Params_Size /* SRAM1 + SRAM2 */
    ram1    : org = 0x20000000 + _OpenBLT_Shared_Params_Size, len = 112k - _OpenBLT_Shared_Params_Size      /* SRAM1 */
    ram2    : org = 0x2001C000, len = 16k       /* SRAM2 */
    ram3    : org = 0x20020000, len = 0k
    ram4    : org = 0x10000000, len = 64k       /* CCM SRAM */
    ram5    : org = 0x40024000, len = 4k        /* BCKP SRAM */
    ram6    : org = 0x00000000, len = 0
    ram7    : org = 0xD0000000, len = 0
}

__backup_sram_addr__ = ORIGIN(ram5);

/* For each data/text section two region are defined, a virtual region
   and a load region (_LMA suffix).*/

/* Flash region to be used for exception vectors.*/
REGION_ALIAS("VECTORS_FLASH", flash0);
REGION_ALIAS("VECTORS_FLASH_LMA", flash0);

/* Flash region to be used for constructors and destructors.*/
REGION_ALIAS("XTORS_FLASH", flash0);
REGION_ALIAS("XTORS_FLASH_LMA", flash0);

/* Flash region to be used for code text.*/
REGION_ALIAS("TEXT_FLASH", flash0);
REGION_ALIAS("TEXT_FLASH_LMA", flash0);

/* Flash region to be used for read only data.*/
REGION_ALIAS("RODATA_FLASH", flash0);
REGION_ALIAS("RODATA_FLASH_LMA", flash0);

/* Flash region to be used for various.*/
REGION_ALIAS("VARIOUS_FLASH", flash0);
REGION_ALIAS("VARIOUS_FLASH_LMA", flash0);

/* Flash region to be used for RAM(n) initialization data.*/
REGION_ALIAS("RAM_INIT_FLASH_LMA", flash0);

/* RAM region to be used for Main stack. This stack accommodates the processing
   of all exceptions and interrupts.*/
REGION_ALIAS("MAIN_STACK_RAM", ram0);

/* RAM region to be used for the process stack. This is the stack used by
   the main() function.*/
REGION_ALIAS("PROCESS_STACK_RAM", ram0);

/* RAM region to be used for data segment.*/
REGION_ALIAS("DATA_RAM", ram0);
REGION_ALIAS("DATA_RAM_LMA", flash0);

/* RAM region to be used for BSS segment.*/
REGION_ALIAS("BSS_RAM", ram0);

/* RAM region to be used for the default heap.*/
REGION_ALIAS("HEAP_RAM", ram0);

/* Use CCM RAM leftovers for additional LUA heap */
REGION_ALIAS("HEAP_CCM_RAM", ram4);

/* RAM region to be used for battery backuped data */
REGION_ALIAS("BKUP_RAM", ram5);

SECTIONS
{
  /* shared between main FW and OpenBLT */
  .shared (NOLOAD) :
  {
    . = ALIGN(4);
    _sshared = .;
    __shared_start__ = _sshared;
    *(.shared)
    *(.shared.*)
    KEEP(*(.shared))
    . = ALIGN(4);
    _eshared = .;
    __shared_end__ = _eshared;
  } > shared

  .bkup_ram_noinit (NOLOAD):
  {
    *(.bkup_ram_noinit)
  } > BKUP_RAM
}

/* Include standard rules from ChibiOS */
INCLUDE rules.ld

SECTIONS
{
  /* Additional LUA heap uses the unused part of a CCM RAM section.*/
  .heap_ccm (NOLOAD) :
  {
    . = ALIGN(8);
    __heap_ccm_base__ = .;
    . = ORIGIN(HEAP_CCM_RAM) + LENGTH(HEAP_CCM_RAM);
    __heap_ccm_end__ = .;
  } > HEAP_CCM_RAM
}
