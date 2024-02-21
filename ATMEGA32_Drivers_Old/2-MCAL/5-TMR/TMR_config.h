/************************************************/
/*                     Name: Ziyad Mohammed     */
/*                     Date: 29/10/2021         */
/*                     SWC: TMR                 */
/*                     Version: 1.0             */
/************************************************/
#ifndef TMR_CONFIG_H
#define TMR_CONFIG_H

// Macros foe On or Off Timer0
/*
TMR_TIMER0_ON
TMR_TIMER0_OFF
*/
#define TMR_u8_TIMER0_ON_OR_OFF                 TMR_TIMER0_ON

// Macroes for selecting timer 0 Mode
/*
TMR_u8_TIMER0_NORMAL_MODE
TMR_u8_TIMER0_PWM_MODE
TMR_u8_TIMER0_CTC_WAVEFORM_GENERATION_MODE
TMR_u8_TIMER0_NORMAL_COUNTER
 */
#define TMR_u8_TIMER0_MODE             TMR_u8_TIMER0_PWM_MODE


// Macros foe On or Off Timer0
/*
TMR_TIMER1_ON
TMR_TIMER1_OFF
*/
#define TMR_u8_TIMER1_ON_OR_OFF                 TMR_TIMER1_ON
// Macroes for selecting timer 0 Mode
/*
Options :
          -TMR_u8_TIMER1_NORMAL_MODE
          -TMR_u8_TIMER1_CTC_WAVEFORM_GENERATION_MODE
          -TMR_u8_TIMER1_PWM_8_9_10_BIT_PHASE_CORRECT_AND_FAST_PWM_MODE
          -TMR_u8_TIMER1_NORMAL_COUNTER
          -TMR_u8_TIMER1_ADVANCED_PWM_FREQ_AND_TICK_TIME
          -TMR_u8_TIMER1_SoftWare_ICU
 */
#define TMR_u8_TIMER1_MODE            TMR_u8_TIMER1_SoftWare_ICU
#endif
