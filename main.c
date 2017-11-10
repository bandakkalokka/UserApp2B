/* 
 * File:   main.c
 * Author: rv
 *
 * Created on January 9, 2017, 5:26 PM
 */


#include "xc.h"
//#include <p24fxxxx.h>
#include <p24F16KA101.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include "Timer2.h"
#include "UART2.H"
#include "Input-Capture.h"


#include "ChangeClk.h"

//// CONFIGURATION BITS ////

// Code protection 
#pragma config BSS = OFF // Boot segment code protect disabled
#pragma config BWRP = OFF // Boot sengment flash write protection off
#pragma config GCP = OFF // general segment code protecion off
#pragma config GWRP = OFF

// CLOCK CONTROL 
#pragma config IESO = OFF    // 2 Speed Startup disabled
#pragma config FNOSC = FRC  // Start up CLK = 8 MHz
#pragma config FCKSM = CSECMD // Clock switching is enabled, clock monitor disabled
#pragma config SOSCSEL = SOSCLP // Secondary oscillator for Low Power Operation
#pragma config POSCFREQ = MS  //Primary Oscillator/External clk freq betwn 100kHz and 8 MHz. Options: LS, MS, HS
#pragma config OSCIOFNC = ON  //CLKO output disabled on pin 8, use as IO. 
#pragma config POSCMOD = NONE  // Primary oscillator mode is disabled

// WDT
#pragma config FWDTEN = OFF // WDT is off
#pragma config WINDIS = OFF // STANDARD WDT/. Applicable if WDT is on
#pragma config FWPSA = PR32 // WDT is selected uses prescaler of 32
#pragma config WDTPS = PS1 // WDT postscler is 1 if WDT selected

//MCLR/RA5 CONTROL
#pragma config MCLRE = OFF // RA5 pin configured as input, MCLR reset on RA5 diabled

//BOR  - FPOR Register
#pragma config BORV = LPBOR // LPBOR value=2V is BOR enabled
#pragma config BOREN = BOR0 // BOR controlled using SBOREN bit
#pragma config PWRTEN = OFF // Powerup timer disabled
#pragma config I2C1SEL = PRI // Default location for SCL1/SDA1 pin

//JTAG FICD Register
#pragma config BKBUG = OFF // Background Debugger functions disabled
#pragma config ICS = PGx2 // PGC2 (pin2) & PGD2 (pin3) are used to connect PICKIT3 debugger

// Deep Sleep RTCC WDT
#pragma config DSWDTEN = OFF // Deep Sleep WDT is disabled
#pragma config DSBOREN = OFF // Deep Sleep BOR is disabled
#pragma config RTCOSC = LPRC// RTCC uses LPRC 32kHz for clock
#pragma config DSWDTOSC = LPRC // DeepSleep WDT uses Lo Power RC clk
#pragma config DSWDTPS = DSWDTPS7 // DSWDT postscaler set to 32768 


// GLOBAL VARIABLES
unsigned int temp;
volatile TvState STATE = READ;
volatile unsigned int CNFlag = 0;
volatile unsigned int ICFlag = 0;

// MACROS
#define Nop() {__asm__ volatile ("nop");}
#define ClrWdt() {__asm__ volatile ("clrwdt");}
#define Sleep() {__asm__ volatile ("pwrsav #0");}   // set sleep mode
#define Idle() {__asm__ volatile ("pwrsav #1");}
#define dsen() {__asm__ volatile ("BSET DSCON, #15");}


int main(void) {
    //Clock output on REFO
    TRISBbits.TRISB15 = 0;  // Set RB15 as output for REFO
    REFOCONbits.ROEN = 1; // Ref oscillator is enabled
    REFOCONbits.ROSSLP = 0; // Ref oscillator is disabled in sleep
    REFOCONbits.ROSEL = 0; // Output base clk showing clock switching
    REFOCONbits.RODIV = 0b0000;
     
    // Switch clock: 32 for 32kHz, 500 for 500 kHz, 8 for 8MHz 
    i = 0;
    
    NewClk(8); //
    InitTimer2();
    InitInComp();
    TRISBbits.TRISB8 = 0;           // Configured as output LED pin
    LATBbits.LATB8 = 0;
    
    while(1) {
        switch(STATE) {
            
            case READ:
                if(IC1CONbits.ICBNE) {
                    LATBbits.LATB8 = 1;
                    IC1CONbits.ICM = 0;                     //Reset the Buffer
                    IC1CONbits.ICM = 0b010;
                }
                
                
                if (CNFlag)
                {
                    
                    IFS0bits.IC1IF = 0;         //Set Flag status bit to 0 of Input-Compare
                    IEC0bits.IC1IE = 0;         //Disable the interrupt
                    
                    T2CONbits.TON  = 0;         //Turn off timer
                    
                    IFS0bits.T2IF = 0;          //Clear Flag status of Timer 2
                    IEC0bits.T2IE = 0;          //Disable the Timer2 interrupts
                    STATE = CHECK;
                    i = 1;                      // Set to 1 to ignore first garbage value
                    CNFlag = 0;
                }
                else
                {
                    Idle();
                    
                }
                break;
                
                
            case CHECK:
                CHECKCOMMAND = 0;
                CHECKCOMMAND = checkCommand();
                
                if(CHECKCOMMAND == CHANNEL_UP) {
                    DispString("Channel Up!");
                }
                else if(CHECKCOMMAND == CHANNEL_DOWN) {
                    DispString("Channel Down!");
                }
                else if(CHECKCOMMAND == VOLUME_UP) {
                    DispString("Volume Up!");
                }
                else if(CHECKCOMMAND == VOLUME_DOWN) {
                    DispString("Volume Down!");
                }
                else if(CHECKCOMMAND == POWER) {
                    DispString("Power On/Off!");
                }
                else {
                    DispString("Invalid Command!");
                }
            
                STATE = RESET;
                i = 0;
                
                break;
                
                
            case RESET:
                TMRVAL[i] = 0;
                i++;
                
                if(i == LENGTH){
                    STATE = READ;
                    DispString("");
                    i = 0;
                    IC1BUF = 0xFFFF;
                    IEC0bits.T2IE = 1;                //Enable the Timer2 interrupts
                    IEC0bits.IC1IE = 1;               //Enable Input-Compare interrupt   
                }
                break; 
                
            default:
                STATE = READ;
                break;
        }
    }
    return 0;
}

