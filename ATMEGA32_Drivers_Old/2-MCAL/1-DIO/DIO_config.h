/*Prebulid*/
/************************************************/
/*                     Name: Ziyad Mohammed     */
/*                     Date: 17/9/2021          */
/*                     SWC: DIO                 */
/*                     Version: 1.0             */
/***************************************** ******/
#ifndef DIO_CONFIG_H
#define DIO_CONFIG_H

// Port driver.

/*Configuration of direction of pins*/
/*Options : 1-DIO_u8_INIT_INPUT
            2-DIO_u8_INIT_OUTPUT*/
#define DIO_u8_PA0_DIRECTION            DIO_u8_INIT_INPUT
#define DIO_u8_PA1_DIRECTION            DIO_u8_INIT_OUTPUT
#define DIO_u8_PA2_DIRECTION            DIO_u8_INIT_OUTPUT
#define DIO_u8_PA3_DIRECTION            DIO_u8_INIT_OUTPUT
#define DIO_u8_PA4_DIRECTION            DIO_u8_INIT_OUTPUT
#define DIO_u8_PA5_DIRECTION            DIO_u8_INIT_OUTPUT
#define DIO_u8_PA6_DIRECTION            DIO_u8_INIT_OUTPUT
#define DIO_u8_PA7_DIRECTION            DIO_u8_INIT_OUTPUT

#define DIO_u8_PB0_DIRECTION            DIO_u8_INIT_OUTPUT
#define DIO_u8_PB1_DIRECTION            DIO_u8_INIT_OUTPUT
#define DIO_u8_PB2_DIRECTION            DIO_u8_INIT_OUTPUT
#define DIO_u8_PB3_DIRECTION            DIO_u8_INIT_OUTPUT
#define DIO_u8_PB4_DIRECTION            DIO_u8_INIT_INPUT
#define DIO_u8_PB5_DIRECTION            DIO_u8_INIT_INPUT
#define DIO_u8_PB6_DIRECTION            DIO_u8_INIT_INPUT
#define DIO_u8_PB7_DIRECTION            DIO_u8_INIT_INPUT

#define DIO_u8_PC0_DIRECTION            DIO_u8_INIT_OUTPUT
#define DIO_u8_PC1_DIRECTION            DIO_u8_INIT_OUTPUT
#define DIO_u8_PC2_DIRECTION            DIO_u8_INIT_OUTPUT
#define DIO_u8_PC3_DIRECTION            DIO_u8_INIT_INPUT
#define DIO_u8_PC4_DIRECTION            DIO_u8_INIT_INPUT
#define DIO_u8_PC5_DIRECTION            DIO_u8_INIT_INPUT
#define DIO_u8_PC6_DIRECTION            DIO_u8_INIT_INPUT
#define DIO_u8_PC7_DIRECTION            DIO_u8_INIT_INPUT

#define DIO_u8_PD0_DIRECTION            DIO_u8_INIT_OUTPUT
#define DIO_u8_PD1_DIRECTION            DIO_u8_INIT_OUTPUT
#define DIO_u8_PD2_DIRECTION            DIO_u8_INIT_OUTPUT
#define DIO_u8_PD3_DIRECTION            DIO_u8_INIT_OUTPUT
#define DIO_u8_PD4_DIRECTION            DIO_u8_INIT_OUTPUT
#define DIO_u8_PD5_DIRECTION            DIO_u8_INIT_OUTPUT
#define DIO_u8_PD6_DIRECTION            DIO_u8_INIT_OUTPUT
#define DIO_u8_PD7_DIRECTION            DIO_u8_INIT_OUTPUT

/*Macros for initial VALUES of all pins*/
/*Options : 1- DIO_u8_OUTPUT_HIGH
            2- DIO_u8_OUTPUT_LOW
            3- DIO_u8_INPUT_FLOATING
            4- DIO_u8_INPUT_PULLUP*/
#define DIO_u8_PA0_VALUES               DIO_u8_INPUT_PULLUP
#define DIO_u8_PA1_VALUES               DIO_u8_INPUT_FLOATING
#define DIO_u8_PA2_VALUES               DIO_u8_INPUT_FLOATING
#define DIO_u8_PA3_VALUES               DIO_u8_INPUT_FLOATING
#define DIO_u8_PA4_VALUES               DIO_u8_INPUT_FLOATING
#define DIO_u8_PA5_VALUES               DIO_u8_INPUT_FLOATING
#define DIO_u8_PA6_VALUES               DIO_u8_INPUT_FLOATING
#define DIO_u8_PA7_VALUES

#define DIO_u8_PB0_VALUES               DIO_u8_OUTPUT_HIGH
#define DIO_u8_PB1_VALUES               DIO_u8_OUTPUT_HIGH
#define DIO_u8_PB2_VALUES               DIO_u8_OUTPUT_HIGH
#define DIO_u8_PB3_VALUES               DIO_u8_OUTPUT_HIGH
#define DIO_u8_PB4_VALUES               DIO_u8_INPUT_PULLUP
#define DIO_u8_PB5_VALUES               DIO_u8_INPUT_PULLUP
#define DIO_u8_PB6_VALUES               DIO_u8_INPUT_PULLUP
#define DIO_u8_PB7_VALUES               DIO_u8_INPUT_PULLUP

#define DIO_u8_PC0_VALUES               DIO_u8_OUTPUT_LOW
#define DIO_u8_PC1_VALUES               DIO_u8_OUTPUT_LOW
#define DIO_u8_PC2_VALUES               DIO_u8_OUTPUT_LOW
#define DIO_u8_PC3_VALUES               DIO_u8_INPUT_FLOATING
#define DIO_u8_PC4_VALUES               DIO_u8_INPUT_FLOATING
#define DIO_u8_PC5_VALUES               DIO_u8_INPUT_FLOATING
#define DIO_u8_PC6_VALUES               DIO_u8_INPUT_FLOATING
#define DIO_u8_PC7_VALUES               DIO_u8_INPUT_FLOATING

#define DIO_u8_PD0_VALUES               DIO_u8_OUTPUT_LOW
#define DIO_u8_PD1_VALUES               DIO_u8_OUTPUT_LOW
#define DIO_u8_PD2_VALUES               DIO_u8_OUTPUT_LOW
#define DIO_u8_PD3_VALUES               DIO_u8_OUTPUT_LOW
#define DIO_u8_PD4_VALUES               DIO_u8_OUTPUT_LOW
#define DIO_u8_PD5_VALUES               DIO_u8_OUTPUT_LOW
#define DIO_u8_PD6_VALUES               DIO_u8_OUTPUT_LOW
#define DIO_u8_PD7_VALUES               DIO_u8_OUTPUT_LOW

#endif
