#include <p24F16KA101.h>
#include "IO.h"
#include "Timer2.h"
#include "UART2.H"
#include "States.h"



void InitCN(void){
    TRISBbits.TRISB4 = 1;           //Set RB4 as input
    TRISAbits.TRISA4 = 1;           //Set RA4 as input
    CNEN1bits.CN1IE = 1;            //Enable CN1
    CNEN1bits.CN0IE = 1;            //Enable CN0
    CNPD1bits.CN0PDE = 0;           //Pin CN0 pull down enable
    CNPD1bits.CN1PDE = 0;           //Pin CN1 pull down enable
    IPC4bits.CNIP = 5;              //2nd Highest priority interrupt
    IFS1bits.CNIF = 0;              //Clear interrupt
    IEC1bits.CNIE = 1;              //Enables change notification interrupt
}

/*
 * 
 * void PollCN(void){}
 * 
 * Checks for button presses and changes state respectively
 */

void PollCN (void){
    delay_ms(100);
    if(PB1 && PB2) {
        ButtonPressed = BOTH;
    }
    else if(PB1 && ~PB2) {           
        ButtonPressed = UP;
    }
    else if(PB2 && ~PB1) {                                        
        ButtonPressed = DOWN;
    }
}


/*
 *
 * void __attribute__ ((interrupt, no_auto_psv)) _CNInterrupt(void){} 
 * 
 * Subroutine for CNInterrupt
 */
void __attribute__ ((interrupt, no_auto_psv)) _CNInterrupt(void){
    
                      //If either button is pressed, set CNFlag to 1
        CNFlag = 1;
    
    
    IFS1bits.CNIF = 0;                  //Clear CN interrupt flag      
}

