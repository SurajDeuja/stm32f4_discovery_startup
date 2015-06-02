/** @file startup.h
 *  @brief Startup header file for STM32M4Discovery board.
 *
 *  @author Suraj Deuja
 */

#ifndef __REG_H
#define __REG_H

/// Macros to access registers 
#define __REG(x) (*((unsigned int *)x))

/// Register definition
#define __VTOR      0xE000ED08

#endif /* End of __REG_H */

