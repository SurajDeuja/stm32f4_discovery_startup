#ifndef __ADDR_H
#define __ADDR_H

#define PERIPH_BASE           (0x40000000)                      /*!< Base for all peripherals */

#define AHB1PERIPH_BASE       (PERIPH_BASE + 0x00020000)        /*!< AHB1 peripherals are at offset of 0x00020000 */

#define RCC_BASE              (AHB1PERIPH_BASE + 0x3800)        /*!< RCC is at offset of 0x3800 from AHB1 */
#define FLASH_BASE            (AHB1PERIPH_BASE + 0x3C00)        /*!< Flash memory is at offset of 0x3C00 from AHB1 */

/* Special Registers */
#define VTOR_BASE             (0xE000ED08)                      /*!< Vector Table Offset Register address */

#endif
