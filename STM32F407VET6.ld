/*
 * STM32F407VET6 Memory Map (512KB Flash, 192KB RAM)
 */

MEMORY
{
    flash0 (rx) : org = 0x08000000, len = 384k
    ram0   (wx) : org = 0x20000000, len = 128k
    ram1   (wx) : org = 0x20020000, len = 0k
    ram2   (wx) : org = 0x2001c000, len = 16k
    ram3   (wx) : org = 0x00000000, len = 0k
    ram4   (wx) : org = 0x10000000, len = 64k
    ram5   (wx) : org = 0x40024000, len = 4k
    ram6   (wx) : org = 0x00000000, len = 0k
    ram7   (wx) : org = 0x00000000, len = 0k
}

INCLUDE common_stm32f407.ld
