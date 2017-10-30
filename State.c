#include "States.h"
#include "UART2.H"
#include "Timer1.h"
#include <p24F16KA101.h>
#include "IO.h"

/*
 *  void PowerOn(void)
 *  This functions sends the PowerOn signal (0xE0E040BF) to the TV.
 *  The functions startbit(), digital_one() and digital_zero() are used
 */

void PowerOn(void){
  startbit();               // The startbit is sent twice, because the first transmission does not happen
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


/*
 *  void PowerOff(void)
 * 
 *  This function sends Power Off signal (0xE0E040BF) to the TV.
 *  Note that separate functions are used to Power On and Power Off 
 *  because of the use of the LED (to indicate mode). The startbit(), 
 *  digital_one() and digital_zero() functions are used.
 */

void PowerOff(void){
    
  startbit();           // The startbit is sent twice, because the first transmission does not happen
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
  LATAbits.LATA3 = 1;           // When power is turned off blink the LED
  delay_ms(200);  
  LATAbits.LATA3 = 0;
  delay_ms(200);
  LATAbits.LATA3 = 1;
  delay_ms(200);
  LATAbits.LATA3 = 0;
}

/*
 *  void Change_Channel(unsigned char channel_dir)
 * 
 *  This function sends the channel up (0xE0E048B7) and channel 
 *  down (0xE0E008F7) signals to the TV. The startbit(), 
 *  digital_one() and digital_zero() functions are used.
 *  If channel_dir is 0 then channel is increasing
 *  If channel dir is anything else, channel is decreasing
 */

void Change_Channel(unsigned char channel_dir){
    if(!channel_dir) {
        if(PB1) {                            //If PushButton1 is pressed
            delay_ms(80);

            startbit();                       // The startbit is sent twice, because the first transmission does not happen
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
            
            startbit();                     // The startbit is sent twice, because the first transmission does not happen
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
}


/*
 *  void Change_Volume(unsigned char volume_dir)
 * 
 *  This function sends the volume up (0xE0E0E01F) and volume 
 *  down (0xE0E0D02F) signals to the TV. The startbit(), 
 *  digital_one() and digital_zero() functions are used.
 *  If volume_dir is 0 volume is increasing
 *  If volume_dir is anything else volume is decreasing
 */

void Change_Volume(unsigned char volume_dir){
    if(!volume_dir) {
        if(PB1) {                            //If PushButton1 is pressed
            delay_ms(80);
            
            startbit();                      //The startbit is sent twice, because the first transmission does not happen
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
            
            startbit();                     // The startbit is sent twice, because the first transmission does not happen
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

/*
 *  void PollLength(void)
 * 
 *  Checks how long both buttons have been pressed for.
 */

void PollLength(void){
  unsigned int count = 0;
  while (PB1 && PB2)            // while both buttons are pressed check how long they are pressed for, 
  {                             // if they are pressed for longer than 3 seconds, turn off TV 
    delay_ms(300);              // else change mode between channel and volume
    count++;

    if (count >= 10)
    {
      tvState = POWER_OFF;
      CNFlag = 0;
      ButtonPressed = NONE;
      return;
    }
  }
  if (tvState == CHANNEL_MODE) {       //If the current state is CHANNEL_MODE change to VOLUME_MODE
    tvState = VOLUME_MODE;
    LATAbits.LATA3 = 1;                // Volume mode LED is ON
    }
    
  else {
    tvState = CHANNEL_MODE;            //If the current state is VOLUME_MODE change to CHANNEL_MODE 
    LATAbits.LATA3 = 0;                // Channel mode LED is OFF
    }
    ButtonPressed = NONE;
    CNFlag = 0;
}

/*
 *  void startbit() 
 * 
 *  This function generates one pulse of 4.6ms HIGH 
 *  and 4.6ms LOW with a carrier frequency of 38kHz. This is the startbit.
 */

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
    }
}

/*
 *Void digital_zero(void)
 * 
 * This function generates a 0.56ms HIGH and 
 * 0.56ms LOW pulse with a carrier frequency of 
 * 38kHz. This is a digital zero.
 */

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

/*
 *Void digital_one(void)
 * 
 * This function generates a 0.56ms HIGH and 
 * 1.69ms LOW pulse with a carrier frequency of 
 * 38kHz. This is a digital one.
 */

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
    }
}
