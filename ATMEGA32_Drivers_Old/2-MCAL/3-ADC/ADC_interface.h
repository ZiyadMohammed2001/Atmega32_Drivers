/************************************************/
/*                     Name: Ziyad Mohammed     */
/*                     Date: 16/10/2021         */
/*                     SWC: ADC                 */
/*                     Version: 1.0             */
/************************************************/
#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

#include "ADC_private.h"
#include "ADC_config.h"

//Macros for Reference Selection Bits.
#define ADC_u8_VREF_AREF                 0b00000000
#define ADC_u8_VREF_AVCC                 0b01000000
#define ADC_u8_VREF_RESERVED             0b10000000
#define ADC_u8_VREF_2_POINT_56           0b11000000

//Macros For Right or Left Adjust Result
#define ADC_u8_RIGHT_ADJUST        0b00000000
#define ADC_u8_LEFT_ADJUST         0b00100000

//Macros for channels.
#define ADC_u8_CHANNEL0            0b00000000
#define ADC_u8_CHANNEL1            0b00000001
#define ADC_u8_CHANNEL2            0b00000010
#define ADC_u8_CHANNEL3            0b00000011
#define ADC_u8_CHANNEL4            0b00000100
#define ADC_u8_CHANNEL5            0b00000101
#define ADC_u8_CHANNEL6            0b00000110
#define ADC_u8_CHANNEL7            0b00000111
#define ADC_u8_CHANNEL8            0b00001000
#define ADC_u8_CHANNEL9            0b00001001
#define ADC_u8_CHANNEL10           0b00001010
#define ADC_u8_CHANNEL11           0b00001011
#define ADC_u8_CHANNEL12           0b00001100
#define ADC_u8_CHANNEL13           0b00001101
#define ADC_u8_CHANNEL14           0b00001110
#define ADC_u8_CHANNEL15           0b00001111
#define ADC_u8_CHANNEL16           0b00010000
#define ADC_u8_CHANNEL17           0b00010001
#define ADC_u8_CHANNEL18           0b00010010
#define ADC_u8_CHANNEL19           0b00010011
#define ADC_u8_CHANNEL20           0b00010100
#define ADC_u8_CHANNEL21           0b00010101
#define ADC_u8_CHANNEL22           0b00010110
#define ADC_u8_CHANNEL23           0b00010111
#define ADC_u8_CHANNEL24           0b00011000
#define ADC_u8_CHANNEL25           0b00011001
#define ADC_u8_CHANNEL26           0b00011010
#define ADC_u8_CHANNEL27           0b00011011
#define ADC_u8_CHANNEL28           0b00011100
#define ADC_u8_CHANNEL29           0b00011101
#define ADC_u8_CHANNEL30           0b00011110
#define ADC_u8_CHANNEL31           0b00011111

//Macros for Single Ended Input
#define ADC_u8_SINGLE_ENDED_INPUT_PIN0      ADC_u8_CHANNEL0
#define ADC_u8_SINGLE_ENDED_INPUT_PIN1      ADC_u8_CHANNEL1
#define ADC_u8_SINGLE_ENDED_INPUT_PIN2      ADC_u8_CHANNEL2
#define ADC_u8_SINGLE_ENDED_INPUT_PIN3      ADC_u8_CHANNEL3
#define ADC_u8_SINGLE_ENDED_INPUT_PIN4      ADC_u8_CHANNEL4
#define ADC_u8_SINGLE_ENDED_INPUT_PIN5      ADC_u8_CHANNEL5
#define ADC_u8_SINGLE_ENDED_INPUT_PIN6      ADC_u8_CHANNEL6

//Macros for test.
#define ADC_u8_TEST_ANY_PIN_1_POINT_22_VOLT           ADC_u8_CHANNEL30
#define ADC_u8_TEST_ANY_PIN_0V                        ADC_u8_CHANNEL31

//Macros for Double Differential Input
#define ADC_u8_DOUBLE_DIFFERENTIAL_INPUT_POSITIVE_PIN0_NEGATIVE_PIN0_10X     ADC_u8_CHANNEL8
#define ADC_u8_DOUBLE_DIFFERENTIAL_INPUT_POSITIVE_PIN1_NEGATIVE_PIN0_10X     ADC_u8_CHANNEL9
#define ADC_u8_DOUBLE_DIFFERENTIAL_INPUT_POSITIVE_PIN0_NEGATIVE_PIN0_200X    ADC_u8_CHANNEL10
#define ADC_u8_DOUBLE_DIFFERENTIAL_INPUT_POSITIVE_PIN1_NEGATIVE_PIN0_200X    ADC_u8_CHANNEL11
#define ADC_u8_DOUBLE_DIFFERENTIAL_INPUT_POSITIVE_PIN2_NEGATIVE_PIN2_10X     ADC_u8_CHANNEL12
#define ADC_u8_DOUBLE_DIFFERENTIAL_INPUT_POSITIVE_PIN3_NEGATIVE_PIN2_10X     ADC_u8_CHANNEL13
#define ADC_u8_DOUBLE_DIFFERENTIAL_INPUT_POSITIVE_PIN2_NEGATIVE_PIN2_200X    ADC_u8_CHANNEL14
#define ADC_u8_DOUBLE_DIFFERENTIAL_INPUT_POSITIVE_PIN3_NEGATIVE_PIN2_200X    ADC_u8_CHANNEL15
#define ADC_u8_DOUBLE_DIFFERENTIAL_INPUT_POSITIVE_PIN0_NEGATIVE_PIN1         ADC_u8_CHANNEL16
#define ADC_u8_DOUBLE_DIFFERENTIAL_INPUT_POSITIVE_PIN1_NEGATIVE_PIN1         ADC_u8_CHANNEL17
#define ADC_u8_DOUBLE_DIFFERENTIAL_INPUT_POSITIVE_PIN2_NEGATIVE_PIN1         ADC_u8_CHANNEL18
#define ADC_u8_DOUBLE_DIFFERENTIAL_INPUT_POSITIVE_PIN3_NEGATIVE_PIN1         ADC_u8_CHANNEL19
#define ADC_u8_DOUBLE_DIFFERENTIAL_INPUT_POSITIVE_PIN4_NEGATIVE_PIN1         ADC_u8_CHANNEL20
#define ADC_u8_DOUBLE_DIFFERENTIAL_INPUT_POSITIVE_PIN5_NEGATIVE_PIN1         ADC_u8_CHANNEL21
#define ADC_u8_DOUBLE_DIFFERENTIAL_INPUT_POSITIVE_PIN6_NEGATIVE_PIN1         ADC_u8_CHANNEL22
#define ADC_u8_DOUBLE_DIFFERENTIAL_INPUT_POSITIVE_PIN7_NEGATIVE_PIN1         ADC_u8_CHANNEL23
#define ADC_u8_DOUBLE_DIFFERENTIAL_INPUT_POSITIVE_PIN0_NEGATIVE_PIN2         ADC_u8_CHANNEL24
#define ADC_u8_DOUBLE_DIFFERENTIAL_INPUT_POSITIVE_PIN1_NEGATIVE_PIN2         ADC_u8_CHANNEL25
#define ADC_u8_DOUBLE_DIFFERENTIAL_INPUT_POSITIVE_PIN2_NEGATIVE_PIN2         ADC_u8_CHANNEL26
#define ADC_u8_DOUBLE_DIFFERENTIAL_INPUT_POSITIVE_PIN3_NEGATIVE_PIN2         ADC_u8_CHANNEL27
#define ADC_u8_DOUBLE_DIFFERENTIAL_INPUT_POSITIVE_PIN4_NEGATIVE_PIN2         ADC_u8_CHANNEL28
#define ADC_u8_DOUBLE_DIFFERENTIAL_INPUT_POSITIVE_PIN5_NEGATIVE_PIN2         ADC_u8_CHANNEL29

// Macro for ADC Enable &Disable.
#define ADC_u8_ENABLE                             0b10000000
#define ADC_u8_DISABLE                            0b00000000

// Macro for ADC Activate Conversion.
#define ADC_u8_CONVERSION_ENABLE                  0b01000000
#define ADC_u8_CONVERSION_DISABLE                 0b00000000

// Macro for ADC Type of Conversion.
#define ADC_u8_SINGLE_CONVERSION_MODE             0b00000000
#define ADC_u8_DOUBLE_CONVERSION_MODE             0b00100000

//Macro for clear flag.
#define ADC_u8_CLEARFLAG                          0b00010000

//Macro for Interrupt Enable & Disable.
#define ADC_u8_INTERRUPTENABLE                    0b00001000
#define ADC_u8_INTERRUPTDISABLE                   0b00000000

//Macros for ADC Prescaler Selection.
#define ADC_u8_DIVISIONFACTOR_2                   0b00000000
#define ADC_u8_DIVISION_FACTOR_2                  0b00000001
#define ADC_u8_DIVISIONFACTOR_4                   0b00000010
#define ADC_u8_DIVISIONFACTOR_8                   0b00000011
#define ADC_u8_DIVISIONFACTOR_16                  0b00000100
#define ADC_u8_DIVISIONFACTOR_32                  0b00000101
#define ADC_u8_DIVISIONFACTOR_64                  0b00000110
#define ADC_u8_DIVISIONFACTOR_125                 0b00000111

//Macros for Auto Trigger Source.
#define ADC_u8_FREE_RUNNING_MODE                  0b00000000
#define ADC_u8_ANALOG_COMPARATOR                  0b00100000
#define ADC_u8_EXTERNAL_INTERRUPT_REQUEST_0       0b01000000
#define ADC_u8_TIMER_COUNTER0_COMPARE_MATCH       0b01100000
#define ADC_u8_TIMER_COUNTER0_OVERFLOW            0b10000000
#define ADC_u8_TIMER_COUNTER0_COMPARE_MATCH_B     0b10100000
#define ADC_u8_TIMER_COUNTER1_OVERFLOW            0b11000000
#define ADC_u8_TIMER_COUNTER1_CAPTURE_EVENT       0b11100000

//Macro for Reversed Bit.
#define ADC_u8_REVERSED_BIT                       0b000000000
void ADC_voidInit(u8 Copy_u8VREF,u8 Copy_u8TypeOfConversion,u8 Copy_u8Prescaler_CLK,u8 Copy_u8EN_OR_DIS_ADC);

  #if ADC_u8_RIGHT_OR_LEFT_ADJUSTMENT == ADC_u8_RIGHT_ADJUSTMENT
        u8 ADC_u8GedDigitalValueSynch(u8 Copy_u8ChannelNum,u16 * Copy_pu16ReturnedDigitalValue,u8 Copy_u8EN_OR_DIS_Conversion);
        #if ADC_u8_AsynchVersion == 1
        u8 ADC_u8GedDigitalValueAsynch(u8 Copy_u8ChannelNum,u16 * Copy_pu16ReturnedDigitalValue,void(*Copy_pf)(void),u8 Copy_u8EN_OR_DIS_Conversion,u8 Copy_u8EN_OR_DIS_Intrrupt);//NotiFication function.
        #elif ADC_u8_AsynchVersion == 2
        u8 ADC_u8GedDigitalValueAsynch(u8 Copy_u8ChannelNum,void(*Copy_pf)(u16),u8 Copy_u8EN_OR_DIS_Conversion,u8 Copy_u8EN_OR_DIS_Intrrupt);
        #endif
  #elif ADC_u8_RIGHT_OR_LEFT_ADJUSTMENT == ADC_u8_LEFT_ADJUSTMENT
        u8 ADC_u8GedDigitalValueSynch(u8 Copy_u8ChannelNum,u8 * Copy_pu8ReturnedDigitalValue,u8 Copy_u8EN_OR_DIS_Conversion);
        #if ADC_u8_AsynchVersion == 1
        u8 ADC_u8GedDigitalValueAsynch(u8 Copy_u8ChannelNum,u8 * Copy_pu8ReturnedDigitalValue,void(*Copy_pf)(void),u8 Copy_u8EN_OR_DIS_Conversion,u8 Copy_u8EN_OR_DIS_Intrrupt);//NotiFication function.
        #elif ADC_u8_AsynchVersion == 2
        u8 ADC_u8GedDigitalValueAsynch(u8 Copy_u8ChannelNum,void(*Copy_pf)(u8),u8 Copy_u8EN_OR_DIS_Conversion,u8 Copy_u8EN_OR_DIS_Intrrupt);
        #endif
  #endif
#endif

