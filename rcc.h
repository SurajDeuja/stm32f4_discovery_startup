#ifndef __RCC_H
#define __RCC_H

#define REG_RCC_ADDR            0x400023800

/** RCC register definition */
struct reg_rcc {
    unsigned volatile int cr;           /// Clock Control         offset 0x00 
    unsigned volatile int pllcfgr;      /// PLL configuration     offset 0x04 
    unsigned volatile int cfgr;         /// Clock Configuration   offset 0x08
    unsigned volatile int cirq;         /// Clock interrupt       offset 0x0c
    unsigned volatile int ahb1rst;      /// AHB1 peripheral reset offset 0x10
    unsigned volatile int ahb2rst;      /// AHB2 peripheral reset offset 0x14
    unsigned volatile int abb3rst;      /// AHB3 peripheral reset offset 0x18
    unsigned volatile int reserved0;    /// Reserved              offset 0x1c
    unsigned volatile int apb1rst;      /// APB1 peripheral reset offset 0x20
    unsigned volatile int apb2rst;      /// APB2 peripheral reset offset 0x24 
    unsigned volatile int reserved1[2]; /// Reserved              offset 0x28
    unsigned volatile int ahb1en;       /// AHB1 peripheral clock offset 0x30
    unsigned volatile int ahb2en;       /// ABH2 peripheral clock offset 0x34
    unsigned volatile int ahb3en;       /// ABH3 peripheral clock offset 0x38
    unsigned volatile int reserved2;    /// Reserved              offset 0x3c
    unsigned volatile int apb1en;       /// APB1 enable register  offset 0x40
    unsigned volatile int apb2en;       /// APB2 enable regiseter offset 0x44
    unsigned volatile int reserved3[2]; /// Reserved              offset 0x48
    unsigned volatile int ahb1lpwen;    /// AHB1 clock low power  offset 0x50
    unsigned volatile int ahb2lpwen;    /// AHB2 clock low power  offset 0x54
    unsigned volatile int ahb3lpwen;    /// ABH3 clock low poer   offset 0x58
    unsigned volatile int reserved4;    /// Reserved              offset 0x5c
    unsigned volatile int apb1lpen;     /// APB1 clock low power  offset 0x60
    unsigned volatile int apb2lpen;     /// APB2 clock low power  offset 0x64
    unsigned volatile int reserved5[2]; /// Reserved              offset 0x68
    unsigned volatile int bkpdctrl;     /// Backup domain control offset 0x6c
    unsigned volatile int csr;          /// control & status      offset 0x70
    unsigned volatile int reserved6[2]; /// Reserved              offset 0x78
    unsigned volatile int sscg;         /// spread spectrum clk   offset 0x80
    unsigned volatile int plli2scfg;    /// PLL I2S config        offset 0x84
}

#endif
