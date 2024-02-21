/************************************************/
/*                     Name: Ziyad Mohammed     */
/*                     Date: 29/10/2021         */
/*                     SWC: TMR                 */
/*                     Version: 1.0             */
/************************************************/
#ifndef TMR_INTERFACE_H
#define TMR_INTERFACE_H

//Macros for Timer 0
#define TMR_u8_TMR0_OVF_MODE                   0
#define TMR_u8_TMR0_CTC_MODE                   1

//Macros For Force Output Compare.
#define TMR_u8_TMR0_FORCE_OUTPUT_COMPARE_NO_PWM_ENABLE                          0b10000000 //BIN 6 MUST BE 0
#define TMR_u8_TMR0_FORCE_OUTPUT_COMPARE_DISABLE                                0b00000000

//MACROS FOR WAVEFORM GENERATION MODE.
#define TMR_u8_TMR0_NORMAL_WAVEFORM_GENERATION_MODE                             0b00000000
#define TMR_u8_TMR0_PWM_PHASE_CORRECT_WAVEFORM_GENERATION_MODE_PINB3            0b01000000
#define TMR_u8_TMR0_CTC_WAVEFORM_GENERATION_MODE_PINB0                          0b00001000
#define TMR_u8_TMR0_FAST_PWM_WAVEFORM_GENERATION_MODE_PINB3                     0b01001000

//Macros For Compare Match Output.
#define TMR_u8_TMR0_NORMAL_PORT_OPERATION_DISCONNECTED_PB3                      0b00000000
#define TMR_u8_TMR0_TOGGLE_ON_COMPARE_MATCH_PB3                                 0b00010000
#define TMR_u8_TMR0_CLEAR_ON_COMPARE_MATCH_NON_INVERTED_PB3                     0b00100000
#define TMR_u8_TMR0_SET_ON_COMPARE_MATCH_INVERTED_PB3                           0b00110000

//MACROS FOR CLOCK SELECT.
#define TMR_u8_TMR0_NO_SOURCE_CLK                                               0b00000000
#define TMR_u8_TMR0_MP_CLK                                                      0b00000001
#define TMR_u8_TMR0_CLK_DIVIDED_8                                               0b00000010
#define TMR_u8_TMR0_CLK_DIVIDED_64                                              0b00000011
#define TMR_u8_TMR0_CLK_DIVIDED_256                                             0b00000100
#define TMR_u8_TMR0_CLK_DIVIDED_1024                                            0b00000101
#define TMR_u8_TMR0_EXTERNAL_CLK_FALLING_EDGE_PIN_PB0                           0b00000110
#define TMR_u8_TMR0_EXTERNAL_CLK_RISING_EDGE_PIN_PB0                            0b00000111

//Macros for enable & disable compare match flow interrupt.
#define TMR_u8_TMR0_COMPARE_MATCH_INTERRUPT_ENABLE                              0b00000010
#define TMR_u8_TMR0_COMPARE_MATCH_INTERRUPT_DISABLE                             0b00000000

//Macros for Enable & Disable Over Flow Interrupt.
#define TMR_u8_TMR0_OVER_FLOW_INTERRUPT_ENABLE                                  0b00000001
#define TMR_u8_TMR0_OVER_FLOW_INTERRUPT_DISABLE                                 0b00000000

//Macro for Enable & Disable CTC Interrupt.Clear Timer on Compare
#define TMR_u8_TMR0_CLEAR_OUTPUT_FLOW_INTERRUPT_ENABLE                          0b00000010
#define TMR_u8_TMR0_CLEAR_OUTPUT_FLOW_INTERRUPT_DISABLE                         0b00000000

//Macro for Clear Output Flow Flag.
#define TMR_u8_TMR0_CLEAR_OUTPUT_FLOW_FLAG                                      0b00000010

//Macro for Clear Over Flow Flag.
#define TMR_u8_TMR0_CLEAR_OVER_FLOW_FLAG                                        0b00000001

//Macros for Timer 1.
#define TMR_u8_TMR1_OVF_MODE                           2
#define TMR_u8_TMR1_CTC_MODE_Channel_A                 3
#define TMR_u8_TMR1_CTC_MODE_Channel_B                 4

//Macros For choosing channel
#define TMR_u8_TMR1_COMPARE_OUTPUT_MODE_CAHNNEL_A_PIN_PD5                       0b00000000
#define TMR_u8_TMR1_COMPARE_OUTPUT_MODE_CAHNNEL_B_PIN_PD4                       0b00000001

//Macros for Compare Output Mode Channel A.
#define TMR_u8_TMR1_NORMAL_PORT_OPERATION_DISCONNECTED_A_PD5                    0b00000000
#define TMR_u8_TMR1_TOGGLE_ON_COMPARE_MATCH_A_PD5                               0b01000000
#define TMR_u8_TMR1_CLEAR_ON_COMPARE_MATCH_NON_INVERTED_A_PD5                   0b10000000
#define TMR_u8_TMR1_SET_ON_COMPARE_MATCH_INVERTED_A_PD5                         0b11000000

//Macros for Compare Output Mode Channel B.
#define TMR_u8_TMR1_NORMAL_PORT_OPERATION_DISCONNECTED_B_PD4                    0b00000000
#define TMR_u8_TMR1_TOGGLE_ON_COMPARE_MATCH_B_PD4                               0b00010000
#define TMR_u8_TMR1_CLEAR_ON_COMPARE_MATCH_NON_INVERTED_B_PD4                   0b00100000
#define TMR_u8_TMR1_SET_ON_COMPARE_MATCH_INVERTED_B_PD4                         0b00110000

//Macros for forced Compare Match Unit
#define  TMR_u8_TMR1_FORCED_COMPARE_MATCH_UNIT_CHANNEL_A                        0b00001000
#define  TMR_u8_TMR1_FORCED_COMPARE_MATCH_UNIT_CHANNEL_B                        0b00000100

//Macros for Waveform Generation Mode.
#define TMR_u16_TMR1_NORMAL_WAVEFORM_GENERATION_MODE                                            0b0000000000000000
#define TMR_u16_TMR1_PWM_PHASE_CORRECT_8_Bit_WAVEFORM_GENERATION_MODE                           0b0000000100000000
#define TMR_u16_TMR1_PWM_PHASE_CORRECT_9_Bit_WAVEFORM_GENERATION_MODE                           0b0000001000000000
#define TMR_u16_TMR1_PWM_PHASE_CORRECT_10_Bit_WAVEFORM_GENERATION_MODE                          0b0000001100000000
#define TMR_u16_TMR1_CTC_WAVEFORM_GENERATION_MODE_1                                             0b0000000000001000
#define TMR_u16_TMR1_PWM_FAST_8_Bit_WAVEFORM_GENERATION_MODE                                    0b0000000100001000
#define TMR_u16_TMR1_PWM_FAST_9_Bit_WAVEFORM_GENERATION_MODE                                    0b0000001000001000
#define TMR_u16_TMR1_PWM_FAST_10_Bit_WAVEFORM_GENERATION_MODE                                   0b0000001100001000
#define TMR_u16_TMR1_PWM_PHASE_AND_FREQUENCY_CORRECT_WAVEFORM_GENERATION_MODE_1_Bottom          0b0000000000010000
#define TMR_u16_TMR1_PWM_PHASE_AND_FREQUENCY_CORRECT_WAVEFORM_GENERATION_MODE_2_Bottom          0b0000000100010000
#define TMR_u16_TMR1_PWM_PHASE_CORRECT_WAVEFORM_GENERATION_MODE_1_TOP                           0b0000001000010000
#define TMR_u16_TMR1_PWM_PHASE_CORRECT_WAVEFORM_GENERATION_MODE_2_TOP                           0b0000001100010000
#define TMR_u16_TMR1_CTC_WAVEFORM_GENERATION_MODE_2                                             0b0000000000011000
#define TMR_u16_TMR1_RESERVED_WAVEFORM_GENERATION_MODE                                          0b0000000100011000
#define TMR_u16_TMR1_PWM_FAST_WAVEFORM_GENERATION_MODE_1                                        0b0000001000011000
#define TMR_u16_TMR1_PWM_FAST_WAVEFORM_GENERATION_MODE_2                                        0b0000001100011000

//Macros for Input Capture Noise Canceler.
#define TMR_u8_TMR1_ACTIVATE_INPUT_CAPTURE_NOISE_CANCELER                      0b10000000
#define TMR_u8_TMR1_DEACTIVATE_INPUT_CAPTURE_NOISE_CANCELER                    0b00000000

//Macros For Input Capture Edge Select.
#define TMR_u8_TMR1_SELECTING_NEGATIVE_EDGE_TRIGGER                            0b00000000
#define TMR_u8_TMR1_SELECTING_POSITIVE_EDGE_TRIGGER                            0b01000000

//MACROS FOR CLOCK SELECT.
#define TMR_u8_TMR1_NO_SOURCE_CLK                                               0b00000000
#define TMR_u8_TMR1_MP_CLK                                                      0b00000001
#define TMR_u8_TMR1_CLK_DIVIDED_8                                               0b00000010
#define TMR_u8_TMR1_CLK_DIVIDED_64                                              0b00000011
#define TMR_u8_TMR1_CLK_DIVIDED_256                                             0b00000100
#define TMR_u8_TMR1_CLK_DIVIDED_1024                                            0b00000101
#define TMR_u8_TMR1_EXTERNAL_CLK_FALLING_EDGE_PIN_PB1                           0b00000110
#define TMR_u8_TMR1_EXTERNAL_CLK_RISING_EDGE_PIN_PB1                            0b00000111

//Macros foe Enable & Disable interrupts.
#define TMR_u8_TMR1_INPUT_CAPTURE_INTERRUPT_ENABLE                              0b00100000
#define TMR_u8_TMR1_INPUT_CAPTURE_INTERRUPT_DISABLE                             0b00000000
#define TMR_u8_TMR1_OUTPUT_COMPARE_MATCH_INTERRUPT_ENABLE_A                     0b00010000
#define TMR_u8_TMR1_OUTPUT_COMPARE_MATCH_INTERRUPT_DISABLE_A                    0b00000000
#define TMR_u8_TMR1_OUTPUT_COMPARE_MATCH_INTERRUPT_ENABLE_B                     0b00001000
#define TMR_u8_TMR1_OUTPUT_COMPARE_MATCH_INTERRUPT_DISABLE_B                    0b00000000
#define TMR_u8_TMR1_OVER_FLOW_INTERRUPT_ENABLE                                  0b00000100
#define TMR_u8_TMR1_OVER_FLOW_INTERRUPT_DISABLE                                 0b00000000

//Macros for Timer Interrupt Flag Register.
#define TMR_u8_TMR1_CLEAR_INPUT_CAPTURE_FLAG                                    0b00100000
#define TMR_u8_TMR1_CLEAR_OUTPUT_COMPARE_MATCH_INTERRUPT_A                      0b00010000
#define TMR_u8_TMR1_CLEAR_OUTPUT_COMPARE_MATCH_INTERRUPT_b                      0b00001000
#define TMR_u8_TMR1_CLEAR_OVER_FLOW_FLAG                                        0b00000100

//Macros for Fast PWM or Phase Correct.
#define TMR_u8_TMR1_FAST_PWM_WAVEFORM_GENERATION_MODE                        1
#define TMR_u8_TMR1_PWM_PHASE_CORRECT_WAVEFORM_GENERATION_MODE               2

u8 TMR_u8SetCallBack(u8 Copy_u8TMRMode,void(*Copy_pf)(void));

//Function Of Timer 0.
#if TMR_u8_TIMER0_ON_OR_OFF == TMR_TIMER0_ON
#if TMR_u8_TIMER0_MODE ==TMR_u8_TIMER0_NORMAL_MODE
u8 TMR_u8TMR0NormalINIT(u8 Copy_u8CLK,u32 Copy_u32Time_NanoSec,u8 Copy_u8CompareMatchUnit,u8 Copy_u8_CompareMatchOutputMode);
#elif TMR_u8_TIMER0_MODE == TMR_u8_TIMER0_PWM_MODE
u8 TMR_u8TMR0PWM_TMR0INIT(u8 Copy_u8TimerMode,u8 Copy_u8ClockSelect,u8 Copy_u8InvertedORNonInverted,u8 Copy_u8SetDutyCycle);
#elif TMR_u8_TIMER0_MODE == TMR_u8_TIMER0_CTC_WAVEFORM_GENERATION_MODE
u8 TMR_u8TMR0CTCINIT(u8 Copy_u8NearestCompareMatchUnit,u8 Copy_u8CLK,u32 Copy_u32Time_NanoSec,u8 Copy_u8_CompareMatchOutputMode);
void TMR_voidTMR0ForcedOutputCompare(u8 Copy_u8_CompareMatchOutputMode);//not tried.
#elif TMR_u8_TIMER0_MODE == TMR_u8_TIMER0_NORMAL_COUNTER
u8 TMR_u8TMR0NormalCounter0INIT(u8 Copy_u8CLK , u32 *Copy_u32Counter );
#endif
void TMR_voidTMR0SetCompareValue(u8 Copy_u8CompareMatchValue);
#endif

#if TMR_u8_TIMER1_ON_OR_OFF == TMR_TIMER1_ON
//Function Of Timer 1.
#if TMR_u8_TIMER1_MODE ==TMR_u8_TIMER1_NORMAL_MODE
u8 TMR_u8TMR1NormalINIT(u8 Copy_u8CLK,u32 Copy_u32Time_MicroSec,u8 Copy_u8CompareMatchUnitChannelA,u8 Copy_u8_CompareMatchOutputModeChannelA,u8 Copy_u8CompareMatchUnitChannelB,u8 Copy_u8_CompareMatchOutputModeChannelB);
#elif TMR_u8_TIMER1_MODE == TMR_u8_TIMER1_CTC_WAVEFORM_GENERATION_MODE
u8 TMR_u8TMR1CTCINIT(u8 Copy_u8CTCMode,u8 Copy_u8SelectChannel_AORB,u16 Copy_u16NearestCompareMatchUnit,u8 Copy_u8CLK,u32 Copy_u32Time_MicroSec,u8 Copy_u8_CompareMatchOutputModeAORB);
void TMR_voidTMR1_AForcedOutputCompare(u8 Copy_u8_CompareMatchOutputMode);//not tried.
void TMR_voidTMR1_BForcedOutputCompare(u8 Copy_u8_CompareMatchOutputMode);//not tried.
#elif TMR_u8_TIMER1_MODE == TMR_u8_TIMER1_PWM_8_9_10_BIT_PHASE_CORRECT_AND_FAST_PWM_MODE
u8 TMR_u8TMR1_A_PWM_TMR1INIT(u8 Copy_u8TimerMode_A,u16 Copy_u16PWMSelecion_A,u8 Copy_u8ClockSelect,u8 Copy_u8InvertedORNonInverted_A,u16 Copy_u8SetDutyCycle_A);
u8 TMR_u8TMR1_B_PWM_TMR1INIT(u8 Copy_u8TimerMode_B,u16 Copy_u16PWMSelecion_B,u8 Copy_u8ClockSelect,u8 Copy_u8InvertedORNonInverted_B,u16 Copy_u8SetDutyCycle_B);
#elif TMR_u8_TIMER1_MODE == TMR_u8_TIMER1_NORMAL_COUNTER
u8 TMR_u8TMR1NormalCounter1INIT(u8 Copy_u8CLK , u32 *Copy_u8Counter);//not tried.
#elif TMR_u8_TIMER1_MODE == TMR_u8_TIMER1_ADVANCED_PWM_FREQ_AND_TICK_TIME
u8 TMR_u8TMR1AdvancedPWMModes(u8 Copy_u8CLK,u16 Copy_u16PWMSelecion,u8 Copy_u8InvertedORNonInverted,u16 Copy_u16_TotalTimeMSec,u16 Copy_u16SetDutyCycle);
#elif TMR_u8_TIMER1_MODE == TMR_u8_TIMER1_SoftWare_ICU
u8 TMR_u8TMR1SoftwareICU(u8 *Copy_u8DutyCycle,u32 *Copy_u32ToTalPeriodTime,u16 *Copy_u16OnPeriod,u16 *Copy_u16OffPeriod,u8 *Copy_u8Frequnecy);
#endif
void TIMER_voidTimer1SetInputCaptureValue(u16 Copy_u16CaptureValue);
void TMR_voidTMR1ASetCompareValue(u16 Copy_u16CompareValue);
void TMR_voidTMR1BSetCompareValue(u16 Copy_u16CompareValue);
#endif
#endif

