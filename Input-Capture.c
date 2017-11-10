#include "Input-Capture.h"
#include <p24F16KA101.h>
#include "IO.h"
#include "UART2.H"

volatile unsigned int TMRVAL[LENGTH];
volatile int i;
volatile mode CHECKCOMMAND;

void InitInComp(void) {
    TRISAbits.TRISA6 = 1;       //Configure as input
    IC1CONbits.ICTMR = 1;       //Use timer 2 for input compare
    IC1CONbits.ICI = 0;         //Interrupt on every capture event
    IC1CONbits.ICM = 0b010;         //Capture on faling edges
    IC1CONbits.ICSIDL = 0;      //Operate in idle
    IFS0bits.IC1IF = 0;         //Set Flag status bit to 0
    IEC0bits.IC1IE = 1;         //Enable the interrupt
    IPC0bits.IC1IP = 7;         //Set to highest priority
}

mode checkCommand(void) {
    static int modeState = 0;
    
    //Check start bit
    if(!(TMRVAL[i] >= LOWER_START && TMRVAL[i] <= UPPER_START)) {
        return INVALID;
    }
    
    
    i++;
    
    // Check E0E0
    if(!(TMRVAL[i] >= LOWER_ONE && TMRVAL[i] <= UPPER_ONE &&              //E
       TMRVAL[i+1] >= LOWER_ONE && TMRVAL[i+1] <= UPPER_ONE && 
       TMRVAL[i+2] >= LOWER_ONE && TMRVAL[i+2] <= UPPER_ONE &&     
       TMRVAL[i+3] >= LOWER_ZERO && TMRVAL[i+3] <= UPPER_ZERO)) {
        return INVALID;
    }
    
    i+=4;
    
     if(!(TMRVAL[i] >= LOWER_ZERO && TMRVAL[i] <= UPPER_ZERO &&             //0
       TMRVAL[i+1] >= LOWER_ZERO && TMRVAL[i+1] <= UPPER_ZERO && 
       TMRVAL[i+2] >= LOWER_ZERO && TMRVAL[i+2] <= UPPER_ZERO &&     
       TMRVAL[i+3] >= LOWER_ZERO && TMRVAL[i+3] <= UPPER_ZERO)) {
        return INVALID;
    }
    
    i+=4;
    
    if(!(TMRVAL[i] >= LOWER_ONE && TMRVAL[i] <= UPPER_ONE &&              //E
       TMRVAL[i+1] >= LOWER_ONE && TMRVAL[i+1] <= UPPER_ONE && 
       TMRVAL[i+2] >= LOWER_ONE && TMRVAL[i+2] <= UPPER_ONE &&     
       TMRVAL[i+3] >= LOWER_ZERO && TMRVAL[i+3] <= UPPER_ZERO)) {
        return INVALID;
    }
    
    i+=4;
    
     if(!(TMRVAL[i] >= LOWER_ZERO && TMRVAL[i] <= UPPER_ZERO &&             //0
       TMRVAL[i+1] >= LOWER_ZERO && TMRVAL[i+1] <= UPPER_ZERO && 
       TMRVAL[i+2] >= LOWER_ZERO && TMRVAL[i+2] <= UPPER_ZERO &&     
       TMRVAL[i+3] >= LOWER_ZERO && TMRVAL[i+3] <= UPPER_ZERO)) {
        return INVALID;
    }
    
    i+=4;
    
    modeState = 0;
    if(TMRVAL[i] >= LOWER_ONE && TMRVAL[i] <= UPPER_ONE) {
        modeState = 1;
        
    }
    else if(TMRVAL[i] >= LOWER_ZERO && TMRVAL[i] <= UPPER_ZERO) {
        modeState = 2;
    }
    else {
        return INVALID;
    }
    
    
    i++;
    
    if(modeState == 1) {
        //Check volume down
        if((TMRVAL[i] >= LOWER_ONE && TMRVAL[i] <= UPPER_ONE &&
            TMRVAL[i+1] >= LOWER_ZERO && TMRVAL[i+1] <= UPPER_ZERO &&
            TMRVAL[i+2] >= LOWER_ONE && TMRVAL[i+2] <= UPPER_ONE)) {
            
            i+=3;
        
            if(!(TMRVAL[i] >= LOWER_ZERO && TMRVAL[i] <= UPPER_ZERO &&             //0
            TMRVAL[i+1] >= LOWER_ZERO && TMRVAL[i+1] <= UPPER_ZERO && 
            TMRVAL[i+2] >= LOWER_ZERO && TMRVAL[i+2] <= UPPER_ZERO &&     
            TMRVAL[i+3] >= LOWER_ZERO && TMRVAL[i+3] <= UPPER_ZERO)) {
                return INVALID;
            }

            i+=4;

            if(!(TMRVAL[i] >= LOWER_ZERO && TMRVAL[i] <= UPPER_ZERO &&             //2
            TMRVAL[i+1] >= LOWER_ZERO && TMRVAL[i+1] <= UPPER_ZERO && 
            TMRVAL[i+2] >= LOWER_ONE && TMRVAL[i+2] <= UPPER_ONE &&     
            TMRVAL[i+3] >= LOWER_ZERO && TMRVAL[i+3] <= UPPER_ZERO)) {
                return INVALID;
            }

            i+=4;

            if(!(TMRVAL[i] >= LOWER_ONE && TMRVAL[i] <= UPPER_ONE &&             //F
            TMRVAL[i+1] >= LOWER_ONE && TMRVAL[i+1] <= UPPER_ONE && 
            TMRVAL[i+2] >= LOWER_ONE && TMRVAL[i+2] <= UPPER_ONE &&     
            TMRVAL[i+3] >= LOWER_ONE && TMRVAL[i+3] <= UPPER_ONE)) {
                return INVALID;
            }

            return VOLUME_DOWN;
        }
        // Check Volume Up
        else if ((TMRVAL[i] >= LOWER_ONE && TMRVAL[i] <= UPPER_ONE &&
            TMRVAL[i+1] >= LOWER_ONE && TMRVAL[i+1] <= UPPER_ONE &&
            TMRVAL[i+2] >= LOWER_ZERO && TMRVAL[i+2] <= UPPER_ZERO))
        {
            
            i+=3;
        
            if(!(TMRVAL[i] >= LOWER_ZERO && TMRVAL[i] <= UPPER_ZERO &&             //0
            TMRVAL[i+1] >= LOWER_ZERO && TMRVAL[i+1] <= UPPER_ZERO && 
            TMRVAL[i+2] >= LOWER_ZERO && TMRVAL[i+2] <= UPPER_ZERO &&     
            TMRVAL[i+3] >= LOWER_ZERO && TMRVAL[i+3] <= UPPER_ZERO)) {
                return INVALID;
            }

            i+=4;

            if(!(TMRVAL[i] >= LOWER_ZERO && TMRVAL[i] <= UPPER_ZERO &&             //1
            TMRVAL[i+1] >= LOWER_ZERO && TMRVAL[i+1] <= UPPER_ZERO && 
            TMRVAL[i+2] >= LOWER_ZERO && TMRVAL[i+2] <= UPPER_ZERO &&     
            TMRVAL[i+3] >= LOWER_ONE && TMRVAL[i+3] <= UPPER_ONE)) {
                return INVALID;
            }

            i+=4;

            if(!(TMRVAL[i] >= LOWER_ONE && TMRVAL[i] <= UPPER_ONE &&             //F
            TMRVAL[i+1] >= LOWER_ONE && TMRVAL[i+1] <= UPPER_ONE && 
            TMRVAL[i+2] >= LOWER_ONE && TMRVAL[i+2] <= UPPER_ONE &&     
            TMRVAL[i+3] >= LOWER_ONE && TMRVAL[i+3] <= UPPER_ONE)) {
                return INVALID;
            }
            
            return VOLUME_UP;
        }
        
        return INVALID;
    }
    else if(modeState == 2) {
        // Check Channel Up
        if((TMRVAL[i] >= LOWER_ONE && TMRVAL[i] <= UPPER_ONE &&                     //4
            TMRVAL[i+1] >= LOWER_ZERO && TMRVAL[i+1] <= UPPER_ZERO &&
            TMRVAL[i+2] >= LOWER_ZERO && TMRVAL[i+2] <= UPPER_ZERO)) {
            
            i+=3;
            
            if ((TMRVAL[i] >= LOWER_ONE && TMRVAL[i] <= UPPER_ONE &&                //8 
            TMRVAL[i+1] >= LOWER_ZERO && TMRVAL[i+1] <= UPPER_ZERO &&
            TMRVAL[i+2] >= LOWER_ZERO && TMRVAL[i+2] <= UPPER_ZERO &&
            TMRVAL[i+3] >= LOWER_ZERO && TMRVAL[i+3] <= UPPER_ZERO))
            {
                i+=4;

                if(!(TMRVAL[i] >= LOWER_ONE && TMRVAL[i] <= UPPER_ONE &&             //B
                TMRVAL[i+1] >= LOWER_ZERO && TMRVAL[i+1] <= UPPER_ZERO && 
                TMRVAL[i+2] >= LOWER_ONE && TMRVAL[i+2] <= UPPER_ONE &&     
                TMRVAL[i+3] >= LOWER_ONE && TMRVAL[i+3] <= UPPER_ONE)) {
                    return INVALID;
                }

                i+=4;

                if(!(TMRVAL[i] >= LOWER_ZERO && TMRVAL[i] <= UPPER_ZERO &&             //7
                TMRVAL[i+1] >= LOWER_ONE && TMRVAL[i+1] <= UPPER_ONE && 
                TMRVAL[i+2] >= LOWER_ONE && TMRVAL[i+2] <= UPPER_ONE &&     
                TMRVAL[i+3] >= LOWER_ONE && TMRVAL[i+3] <= UPPER_ONE)) {
                    return INVALID;
                }
                
                return CHANNEL_UP;;
            }
            // Check Power On/Off
            else if ((TMRVAL[i] >= LOWER_ZERO && TMRVAL[i] <= UPPER_ZERO &&             //0
            TMRVAL[i+1] >= LOWER_ZERO && TMRVAL[i+1] <= UPPER_ZERO && 
            TMRVAL[i+2] >= LOWER_ZERO && TMRVAL[i+2] <= UPPER_ZERO &&     
            TMRVAL[i+3] >= LOWER_ZERO && TMRVAL[i+3] <= UPPER_ZERO))
            {
                i+=4;

                if(!(TMRVAL[i] >= LOWER_ONE && TMRVAL[i] <= UPPER_ONE &&             //B
                TMRVAL[i+1] >= LOWER_ZERO && TMRVAL[i+1] <= UPPER_ZERO && 
                TMRVAL[i+2] >= LOWER_ONE && TMRVAL[i+2] <= UPPER_ONE &&     
                TMRVAL[i+3] >= LOWER_ONE && TMRVAL[i+3] <= UPPER_ONE)) {
                    return INVALID;
                }

                i+=4;

                if(!(TMRVAL[i] >= LOWER_ONE && TMRVAL[i] <= UPPER_ONE &&             //F
                TMRVAL[i+1] >= LOWER_ONE && TMRVAL[i+1] <= UPPER_ONE && 
                TMRVAL[i+2] >= LOWER_ONE && TMRVAL[i+2] <= UPPER_ONE &&     
                TMRVAL[i+3] >= LOWER_ONE && TMRVAL[i+3] <= UPPER_ONE)) {
                    return INVALID;
                }
                
                return POWER;
            }
            else
            {
                return INVALID;
            }
            
        }
        // Check Channel Down
        else if((TMRVAL[i] >= LOWER_ZERO && TMRVAL[i] <= UPPER_ZERO &&          //  0
            TMRVAL[i+1] >= LOWER_ZERO && TMRVAL[i+1] <= UPPER_ZERO &&
            TMRVAL[i+2] >= LOWER_ZERO && TMRVAL[i+2] <= UPPER_ZERO)) {
            
            i += 3;
            
            if (!(TMRVAL[i] >= LOWER_ONE && TMRVAL[i] <= UPPER_ONE &&                //8 
            TMRVAL[i+1] >= LOWER_ZERO && TMRVAL[i+1] <= UPPER_ZERO &&
            TMRVAL[i+2] >= LOWER_ZERO && TMRVAL[i+2] <= UPPER_ZERO &&
            TMRVAL[i+3] >= LOWER_ZERO && TMRVAL[i+3] <= UPPER_ZERO))
            {
                return INVALID;
            }
            
            i+=4;

            if(!(TMRVAL[i] >= LOWER_ONE && TMRVAL[i] <= UPPER_ONE &&             //F
            TMRVAL[i+1] >= LOWER_ONE && TMRVAL[i+1] <= UPPER_ONE && 
            TMRVAL[i+2] >= LOWER_ONE && TMRVAL[i+2] <= UPPER_ONE &&     
            TMRVAL[i+3] >= LOWER_ONE && TMRVAL[i+3] <= UPPER_ONE)) {
                return INVALID;
            }

            i+=4;

            if(!(TMRVAL[i] >= LOWER_ZERO && TMRVAL[i] <= UPPER_ZERO &&             //7
            TMRVAL[i+1] >= LOWER_ONE && TMRVAL[i+1] <= UPPER_ONE && 
            TMRVAL[i+2] >= LOWER_ONE && TMRVAL[i+2] <= UPPER_ONE &&     
            TMRVAL[i+3] >= LOWER_ONE && TMRVAL[i+3] <= UPPER_ONE)) {
                return INVALID;
            }
            
            return CHANNEL_DOWN;
            
        }
        else 
        {
            return INVALID;
        }
    }
    
    return INVALID;
    
}

void __attribute__((interrupt, no_auto_psv)) _IC1Interrupt(void)
{
    IFS0bits.IC1IF = 0;         //Clear status bit
    
    PR2 = 65535;
    TMR2 = 0;
    T2CONbits.TON = 1;
    TMRVAL[i] = IC1BUF;
     i++;
    //IC1BUF = 0xFFFF;
    
    if (i == LENGTH)
        CNFlag = 1;
}
