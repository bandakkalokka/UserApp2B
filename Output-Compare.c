
#include <p24F16KA101.h>
#include "Output-Compare.h"


void InitOutComp(void) {
    OC1CONbits.OCM = 6;             // Set output compare mode to PWM
    OC1CONbits.OCTSEL = 0;          // Use Timer 3 for Output Compare
    IFS0bits.OC1IF = 0;             // Clear the Output compare flag
    IEC0bits.OC1IE = 1;             // Enable output compare interrupt
    IPC0bits.OC1IP = 6;             // Set to highest priority level
    PADCFG1bits.OC1TRIS = 0;        // Enable output pin
    OC1CONbits.OCSIDL = 0;          // work in Idle mode
    OC1R = 32768;                   // Initialize Duty Cycle to 50%
    TMR2 = 0;
}

void PWM(unsigned int length_ms){
    
    PR2 = 0;
    //TMR3 = 0;
    //Duty Cycle works
    OC1RS = 32768;
    T2CONbits.TON = 1;
    //Idle();
    
    return;
}
