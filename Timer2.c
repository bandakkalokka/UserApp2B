#include <p24F16KA101.h>
#include "Timer2.h"
#include "Timer1.h"
#include "ChangeClk.h"


void InitTimer2(void) {
    T2CONbits.T32 = 0b00;               //Set timer2 to 16-bit
    T2CONbits.TCKPS = 0b00;             //Set pre-scale to 1
    T2CONbits.TCS = 0;                //Use Internal Clock
    
    IPC1bits.T2IP = 0b110;              //Set to second highest priority
    IFS0bits.T2IF = 0;                //Clear Flag status
    IEC0bits.T2IE = 1;                //Enable the Timer Interrupt
}




void delay_us2(unsigned int time_us) {
    
        PR2 = time_us;                  // Setting PR2 
        
        T2CONbits.TON = 1;                // Turn on Timer
}


//Timer2 Interrupt subroutine
void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void)
{
    IFS0bits.T2IF = 0;                //Clear Flag status
    //T2CONbits.TON = 0;                //Turn off timer
     //TMR2 = 0;
                            // Clear TMR2 register
}
