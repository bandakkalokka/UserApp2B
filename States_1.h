/*
 * File:   State.h
 * Author: badeniran
 *
 * Created on September 27, 2017
 */

 #ifndef STATE_H
 #define STATE_H

 #ifdef  __cplusplus
 extern "C" {
 #endif

 #include "IO.h"
 #include "Timer1.h"
 #include "Timer2.h"
 #include "UART2.H"
 #include "ChangeClk.h"
 #include <p24F16KA101.h>
 #include <stdio.h>
 // Define State Macros
 #define S_ZERO_DISPLAY       0
 #define S_WAIT_BUTTON_PRESS  1
 #define S_INC_TIMER          2
 #define S_COUNTDOWN          3
 #define S_ALARM              4
 #define S_RESET              5

 // Push button Macros
 #define PB1                  PORTBbits.RB4
 #define PB2                  PORTAbits.RA4

 // Global variables
 extern volatile unsigned int State;   // Keeps track of current state
 extern volatile unsigned int ButtonPressed;

 // State functions
 void ZeroDisplay(void);
 void WaitForButtonPress(void);
 void IncrementTimer(void);
 void Countdown(void);
 void Alarm(void);
 void Reset(void);
 #endif
