/************************************************/
/*                     Name: Ziyad Mohammed     */
/*                     Date: 16/10/2021         */
/*                     SWC: ADC                 */
/*                     Version: 1.0             */
/************************************************/
#ifndef ADC_PRIVATE_H
#define ADC_PRIVATE_H

// Register Definition.

#define ADC_u8_SFIOR_REG                     *((volatile u8*)0x50)
#define ADC_u8_ADMUX_REG                     *((volatile u8*)0x27)
#define ADC_u8_ADCSRA_REG                    *((volatile u8*)0x26)

#define ADC_u8_ADCH_REG                      *((volatile u8*)0x25)
#define ADC_u8_ADCL_REG                      *((volatile u8*)0x24)

#define ADC_u16_ADC_REG                     *((volatile u16*)0x24)
#define ADC_u8_BUSY                           1
#define ADC_u8_NOT_BUSY                       0


#define ADC_u8_RIGHT_ADJUSTMENT    0b00000000
#define ADC_u8_LEFT_ADJUSTMENT     0b00100000

#define  ADC_u8_AsynchVersion1       1
#define  ADC_u8_AsynchVersion2       2

#endif
