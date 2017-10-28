/* 
 * File:   Timer3.h
 * Author: bandakka
 *
 * Created on October 20, 2017, 11:18 AM
 */

#ifndef TIMER3_H
#define	TIMER3_H

#define START_BIT           18000
#define IR_FREQ             6
#define DIGITAL_ZERO        2240
#define DIGITAL_ONE_HIGH    2240
#define DIGITAL_ONE_LOW     6760

extern volatile unsigned int main_timer_done;
extern volatile unsigned int timer_state;

#ifdef	__cplusplus
extern "C" {
#endif

    
    
void InitTimer1(void);
void delay_ms(unsigned int time_ms);
void delay_us1(unsigned int time_us);
void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void);

#ifdef	__cplusplus
}
#endif

#endif	/* TIMER3_H */

