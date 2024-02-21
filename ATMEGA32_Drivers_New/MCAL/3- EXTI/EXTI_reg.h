
/********************************************************************/
/********************************************************************/
/*********************** Author: Ziyad Mohammed   *******************/
/*********************** File  : EXTI_REG.h       *******************/
/*********************** Version: 1.00            *******************/
/********************************************************************/
/********************************************************************/

#ifndef EXTI_REG_H_
#define EXTI_REG_H_

#define GICR			*((volatile uint8*)0x5B) /*@brief Global Interrupt control register.*/
#define GICR_INT1		7u						 /*@brief INT1 Control Bit.*/
#define GICR_INT0		6u						 /*@brief INT0 Control Bit.*/
#define GICR_INT2		5u						 /*@brief INT2 Control Bit.*/

#define MCUCR			*((volatile uint8*)0x55)	 /*@brief MCU Control Register.*/
#define MCUCR_ISC00      0u 					 /*@brief Interrupt Sense control 0 bit 0.*/
#define MCUCR_ISC01      1u						 /*@brief Interrupt Sense control 0 bit 1.*/
#define MCUCR_ISC10      2u 					 /*@brief Interrupt Sense control 1 bit 0.*/
#define MCUCR_ISC11      3u						 /*@brief Interrupt Sense control 1 bit 1.*/


#define MCUCSR			*((volatile uint8*)0x54)  /*@brief MCU Control and Status Register.*/
#define MCUCSR_ISC2		 6u						  /*@brief Interrupt Sense Control 2.*/

#endif
