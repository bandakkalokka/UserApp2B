#include "States.h"
#include "UART2.H"
#include "Timer1.h"
#include <p24F16KA101.h>
#include "IO.h"


void PowerOn(void){
  // TODO -- Put code for powering on
  startbit(1);

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

  //DispString("Powering On!");
}
void PowerOff(void){
  // TODO -- Put code for powering off
  DispString("Powering Off!");
}
void Change_Channel(unsigned char channel_dir){
  // TODO -- Put code for increasing channel
  PollCN();
  // TODO -- Put code for decreasing channel
}
void Change_Volume(void){
  // TODO -- Put code for increasing volume
  // TODO -- Put code for decreasing volume
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
      return;
    }
  }
  if (tvState == CHANNEL_MODE)
    tvState = VOLUME_MODE;
  else
    tvState = CHANNEL_MODE;
}

void startbit(unsigned int count){

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
                    //LATAbits.LATA4 = 1;
                    break;
                }
            }
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
        LATAbits.LATA4 ^= 1;
    }
}
