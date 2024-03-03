
/********************************************************************/
/********************************************************************/
/*********************** Author: Ziyad Mohammed   *******************/
/*********************** File  : SPI_REG.h        *******************/
/*********************** Version: 1.00            *******************/
/********************************************************************/
/********************************************************************/

#ifndef SPI_REG_H_
#define SPI_REG_H_

#define SPCR    (*(volatile uint8*)0x2D)
#define SPSR    (*(volatile uint8*)0x2E)
#define SPDR    (*(volatile uint8*)0x2F)

/* SPCR Bit Definitions. */
#define SPR0 0
#define SPR1 1
#define CPHA 2
#define CPOL 3
#define MSTR 4
#define DORD 5
#define SPE  6
#define SPIE 7

/* SPSR Bit Definitions. */
#define SPI2X 0
#define WCOL  6
#define SPIF  7

#endif
