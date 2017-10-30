
#include <p24F16KA101.h>
#include "Timer1.h"
#include "Timer2.h"
#include "ChangeClk.h"


volatile unsigned int main_timer_done;

void InitTimer1(void) {
    T1CONbits.TCKPS = 0b00;             //Set pre-scale to 1
    T1CONbits.TCS = 0;                  //Use Internal Clock
    
    IPC0bits.T1IP = 0b111;              //Set to highest priority
    IFS0bits.T1IF = 0;                  //Clear Flag status
    IEC0bits.T1IE = 1;                  //Enable the Timer Interrupt
}


void delay_ms(unsigned int time_ms) {     
    NewClk(32);
    PR1 = (time_ms) * 16;           // Setting PR2
    T1CONbits.TON = 1;                //Turn on Timer
    Idle();                         // Go into Idle mode   
    NewClk(8);
    return;
}


void delay_us1(unsigned int time_us) {
        PR1 = time_us;                    // Setting PR2 
        T1CONbits.TON = 1;                // Turn on Timer
        delay_us2(IR_FREQ);
        main_timer_done = 0;
}


//Timer1 Interrupt subroutine
void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void)
{
    IFS0bits.T1IF = 0;                //Clear Flag status
    T1CONbits.TON = 0;                //Turn off timer
    main_timer_done = 1;
    TMR1 = 0;                         // Clear TMR2 register
}
