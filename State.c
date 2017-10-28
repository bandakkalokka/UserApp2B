#include "States.h"
#include "UART2.H"
#include "Timer1.h"
#include <p24F16KA101.h>
#include "IO.h"


void PowerOn(void){
  startbit();
  startbit();
  
  digital_one();
  digital_one();
  digital_one();
  digital_zero();

  digital_zero();
  digital_zero();
  digital_zero();
  digital_zero();

  digital_one();
  digital_one();
  digital_one();
  digital_zero();

  digital_zero();
  digital_zero();
  digital_zero();
  digital_zero();

  digital_zero();
  digital_one();
  digital_zero();
  digital_zero();

  digital_zero();
  digital_zero();
  digital_zero();
  digital_zero();

  digital_one();
  digital_zero();
  digital_one();
  digital_one();

  digital_one();
  digital_one();
  digital_one();
  digital_one();

  digital_zero();
  
  delay_ms(50);
 
}

void PowerOff(void){
    
  startbit();
  startbit();
  
  digital_one();
  digital_one();
  digital_one();
  digital_zero();

  digital_zero();
  digital_zero();
  digital_zero();
  digital_zero();

  digital_one();
  digital_one();
  digital_one();
  digital_zero();

  digital_zero();
  digital_zero();
  digital_zero();
  digital_zero();

  digital_zero();
  digital_one();
  digital_zero();
  digital_zero();

  digital_zero();
  digital_zero();
  digital_zero();
  digital_zero();

  digital_one();
  digital_zero();
  digital_one();
  digital_one();

  digital_one();
  digital_one();
  digital_one();
  digital_one();

  digital_zero();
  
  delay_ms(50);
  LATAbits.LATA3 = 1;
  delay_ms(200);  
  LATAbits.LATA3 = 0;
  delay_ms(200);
  LATAbits.LATA3 = 1;
  delay_ms(200);
  LATAbits.LATA3 = 0;
}
void Change_Channel(unsigned char channel_dir){
  // TODO -- Put code for increasing channel
    if(!channel_dir) {
        if(PB1) {                            //If PushButton1 is pressed
            delay_ms(80);

            startbit();
            startbit();
            digital_one();
            digital_one();
            digital_one();
            digital_zero();

            digital_zero();
            digital_zero();
            digital_zero();
            digital_zero();

            digital_one();
            digital_one();
            digital_one();
            digital_zero();

            digital_zero();
            digital_zero();
            digital_zero();
            digital_zero();            
            
            digital_zero();
            digital_one();
            digital_zero();
            digital_zero();
            
            digital_one();
            digital_zero();
            digital_zero();
            digital_zero();
            
            digital_one();
            digital_zero();
            digital_one();
            digital_one();
            
            digital_zero();
            digital_one();
            digital_one();
            digital_one();
            
            digital_zero();
            
            delay_ms(50);
            delay_ms(80);
        }
        else {
            ButtonPressed = NONE;                          
            CNFlag = 0;
        }
    }
    else {
        if(PB2) {                            //If PushButton2 is pressed
            delay_ms(80);
            
            startbit();
            startbit();
            digital_one();
            digital_one();
            digital_one();
            digital_zero();

            digital_zero();
            digital_zero();
            digital_zero();
            digital_zero();

            digital_one();
            digital_one();
            digital_one();
            digital_zero();

            digital_zero();
            digital_zero();
            digital_zero();
            digital_zero(); 
            
            digital_zero();
            digital_zero();
            digital_zero();
            digital_zero(); 
            
            digital_one();
            digital_zero();
            digital_zero();
            digital_zero();
            
            digital_one();
            digital_one();
            digital_one();
            digital_one(); 
            
            
            digital_zero();
            digital_one();
            digital_one();
            digital_one();
            
            digital_zero();
            
            delay_ms(50);
            delay_ms(80);
        }
        else {
            ButtonPressed = NONE;                          
            CNFlag = 0;
        }
    }
    
     delay_ms(50);
  // TODO -- Put code for decreasing channel
}
void Change_Volume(unsigned char volume_dir){
    //DispString("Change Volume!");
    if(!volume_dir) {
        if(PB1) {                            //If PushButton1 is pressed
            delay_ms(80);
            
            startbit();
            startbit();
            digital_one();
            digital_one();
            digital_one();
            digital_zero();

            digital_zero();
            digital_zero();
            digital_zero();
            digital_zero();

            digital_one();
            digital_one();
            digital_one();
            digital_zero();

            digital_zero();
            digital_zero();
            digital_zero();
            digital_zero(); 
            
            digital_one();
            digital_one();
            digital_one();
            digital_zero();

            digital_zero();
            digital_zero();
            digital_zero();
            digital_zero();

            digital_zero();
            digital_zero();
            digital_zero();
            digital_one();
            
            digital_one();
            digital_one();
            digital_one();
            digital_one();
 
            digital_zero();
            
            delay_ms(50);
            delay_ms(80);
        }
        else {
            ButtonPressed = NONE;                          
            CNFlag = 0;
        }
    }
    else {
        if(PB2) {                            //If PushButton2 is pressed
            delay_ms(80);
            
            startbit();
            startbit();
            digital_one();
            digital_one();
            digital_one();
            digital_zero();

            digital_zero();
            digital_zero();
            digital_zero();
            digital_zero();

            digital_one();
            digital_one();
            digital_one();
            digital_zero();

            digital_zero();
            digital_zero();
            digital_zero();
            digital_zero(); 
            
            digital_one();
            digital_one();
            digital_zero();
            digital_one();
            
            digital_zero();
            digital_zero();
            digital_zero();
            digital_zero();
            
            digital_zero();
            digital_zero();
            digital_one();
            digital_zero();
            
            digital_one();
            digital_one();
            digital_one();
            digital_one();
            
            digital_zero();
            
            delay_ms(50);
            delay_ms(80);
        }
        else {
            ButtonPressed = NONE;                          
            CNFlag = 0;
        }
    }
}

// Helper functions
void PollLength(void){
  unsigned int count = 0;
  while (PB1 && PB2)
  {
    delay_ms(300);
    count++;

    if (count >= 10)
    {
      tvState = POWER_OFF;
      CNFlag = 0;
      ButtonPressed = NONE;
      return;
    }
  }
  if (tvState == CHANNEL_MODE) {
    tvState = VOLUME_MODE;
    LATAbits.LATA3 = 1;         // Volume mode LED is ON
    }
    
  else {
    tvState = CHANNEL_MODE;
    LATAbits.LATA3 = 0;         // Channel mode LED is OFF
    }
    ButtonPressed = NONE;
    CNFlag = 0;
}

void startbit(){
    
  while(1){
        if (timer_state)
            {
                PR1 = START_BIT;
                T1CONbits.TON = 1;
                PR2 = IR_FREQ;
                T2CONbits.TON = 1;
                if (main_timer_done)
                {
                    timer_state = 0;
                    T2CONbits.TON = 0;
                    TMR2 = 0;
                    main_timer_done = 0;
                }
                else
                {
                    LATBbits.LATB8 = !LATBbits.LATB8;
                }
            }
            else
            {

               PR1 = START_BIT;
               T1CONbits.TON = 1;
               LATBbits.LATB8 = 0;
                if (main_timer_done)
                {
                    timer_state = 1;
                    main_timer_done = 0;
                    break;
                }
            }
        //LATAbits.LATA4 ^= 1;
    }
}

void digital_zero(void) {
    while(1){
        if (timer_state)
            {
                PR1 = DIGITAL_ZERO;
                T1CONbits.TON = 1;
                PR2 = IR_FREQ;
                T2CONbits.TON = 1;
                if (main_timer_done)
                {
                    timer_state = 0;
                    T2CONbits.TON = 0;
                    TMR2 = 0;
                    main_timer_done = 0;
                }
                else
                {
                    LATBbits.LATB8 = !LATBbits.LATB8;
                }
            }
            else
            {

               PR1 = DIGITAL_ZERO;
               T1CONbits.TON = 1;
               LATBbits.LATB8 = 0;
                if (main_timer_done)
                {
                    timer_state = 1;
                    main_timer_done = 0;
                    return;
                }
            }
    }
}

void digital_one(void){
    while(1){
        if (timer_state)
            {
                PR1 = DIGITAL_ONE_HIGH;
                T1CONbits.TON = 1;
                PR2 = IR_FREQ;
                T2CONbits.TON = 1;
                if (main_timer_done)
                {
                    timer_state = 0;
                    T2CONbits.TON = 0;
                    TMR2 = 0;
                    main_timer_done = 0;
                }
                else
                {
                    LATBbits.LATB8 = !LATBbits.LATB8;
                }
            }
            else
            {

               PR1 = DIGITAL_ONE_LOW;
               T1CONbits.TON = 1;
               LATBbits.LATB8 = 0;
                if (main_timer_done)
                {
                    timer_state = 1;
                    main_timer_done = 0;
                    break;
                }
            }
        //LATAbits.LATA4 ^= 1;
    }
}
