/************************************************/
/*                     Name: Ziyad Mohammed     */
/*                     Date: 29/10/2021         */
/*                     SWC: TMR                 */
/*                     Version: 1.0             */
/************************************************/
#ifndef TMR_PRIVATE_H
#define TMR_PRIVATE_H

//Macros for Timer 0.
#define TMR_u8_TMR0_TCCR0_REG                 *((volatile u8*)0x53)
#define TMR_u8_TMR0_TCNT0_REG                 *((volatile u8*)0x52)
#define TMR_u8_TMR0_OCR0_REG                  *((volatile u8*)0x5c)

#define TMR_u8_TIMSK_REG                      *((volatile u8*)0x59)
#define TMR_u8_TIFR_REG                       *((volatile u8*)0x58)

#define TMR_TIMER0_ON                                           0
#define TMR_TIMER0_OFF                                          1

#define TMR_u8_TIMER0_NORMAL_MODE                               0
#define TMR_u8_TIMER0_PWM_MODE                                  1
#define TMR_u8_TIMER0_CTC_WAVEFORM_GENERATION_MODE              2
#define TMR_u8_TIMER0_NORMAL_COUNTER                            3


//Macros for Timer 1.
#define TMR_u8_TMR1_TCCR1A_REG				  *((volatile u8*) 0x4F )
#define TMR_u8_TMR1_TCCR1B_REG				  *((volatile u8*) 0x4E )
#define TMR_u16_TMR1_TCCR1_REG                *((volatile u16*) 0x4E )

#define TMR_u16_TMR1_TCNT1_REG				  *((volatile u16*) 0x4C )
#define TMR_u16_TMR1_OCR1A_REG				  *((volatile u16*) (0x4A))
#define TMR_u16_TMR1_OCR1B_REG				  *((volatile u16*) (0x48))
#define TMR_u16_TMR1_ICR1_REG				  *((volatile u16*) 0x46 )

#define TMR_u8_TMR1_NO_SELECTED_TIME          0

#define TMR_TIMER1_ON                                           0
#define TMR_TIMER1_OFF                                          1

#define TMR_u8_TIMER1_NORMAL_MODE                                                     1
#define TMR_u8_TIMER1_CTC_WAVEFORM_GENERATION_MODE                                    2
#define TMR_u8_TIMER1_PWM_8_9_10_BIT_PHASE_CORRECT_AND_FAST_PWM_MODE                  3
#define TMR_u8_TIMER1_NORMAL_COUNTER                                                  4
#define TMR_u8_TIMER1_ADVANCED_PWM_FREQ_AND_TICK_TIME                                 5
#define TMR_u8_TIMER1_SoftWare_ICU                                                    6
#endif
