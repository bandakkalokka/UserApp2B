#include <p24F16KA101.h>
#include "IO.h"
#include "Timer2.h"
#include "UART2.H"
#include "States.h"

volatile unsigned int CNFlag;

void InitCN(void){
    TRISBbits.TRISB4 = 1;           //Set RB4 as input
    TRISAbits.TRISA4 = 1;           //Set RA4 as input
    CNEN1bits.CN1IE = 1;            //Enable CN1
    CNEN1bits.CN0IE = 1;            //Enable CN0
    CNPD1bits.CN0PDE = 1;           //Pin CN0 pull down enable
    CNPD1bits.CN1PDE = 1;           //Pin CN1 pull down enable
    IPC4bits.CNIP = 6;              //2nd Highest priority interrupt
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
//    if(PB1 && PB2) {
//        if(tvState == S_COUNTDOWN) {                                    //If both buttons pressed and current state is countdown 
//            tvState = S_RESET;                                          //Change state to reset
//        }
//        else if(tvState ==  S_WAIT_BUTTON_PRESS){                       //If both buttons pressed and current state is wait for button press
//            delay_onesec();                                           //Change state to countdown
//            tvState = S_COUNTDOWN;
//        }
//    }
//    else if(PB1 && ~PB2 && tvState ==  S_WAIT_BUTTON_PRESS) {           //If only PushButton1 is pressed and current state is wait for button press
//        tvState = S_INC_TIMER;                                          //Change state to increment timer
//        ButtonPressed = 1;
//    }
//    else if(PB2 && ~PB1 && tvState ==  S_WAIT_BUTTON_PRESS){           //If only PushButton2 is pressed and current state is wait for button pressed
//        tvState = S_INC_TIMER;                                         //Change state to increment timer   
//        ButtonPressed = 2;
//    }
}


/*
 *
 * void __attribute__ ((interrupt, no_auto_psv)) _CNInterrupt(void){} 
 * 
 * Subroutine for CNInterrupt
 */
void __attribute__ ((interrupt, no_auto_psv)) _CNInterrupt(void){
    
    if(PB1 || PB2) {                    //If either button is pressed, set CNFlag to 1
        CNFlag = 1;
    }
    
    IFS1bits.CNIF = 0;                  
}

