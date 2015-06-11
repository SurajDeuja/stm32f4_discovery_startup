#ifndef __FLASH_H
#define __FLASH_H

#define FLASH_ACR_ICEN          ((unsigned int) 0x00000200)
#define FLASH_ACR_DCEN          ((unsigned int) 0x00000400)
#define FLASH_ACR_LATENCY_5WS   ((unsigned int) 0x00000005)

struct flash_reg {
        volatile unsigned int acr;              /*!< access control */
        volatile unsigned int keyr;             /*!< key register */
        volatile unsigned int optkeyr;          /*!< option key register */
        volatile unsigned int sr;               /*!< status register */
        volatile unsigned int cr;               /*!< control register */
        volatile unsigned int optcr;            /*!< option control register */
};

#endif
