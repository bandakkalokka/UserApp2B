/*
 * File:   State.h
 * Author: badniran
 *
 * Created on September 27, 2017
 */

 #ifndef STATE_H
 #define STATE_H

 #ifdef  __cplusplus
 extern "C" {
 #endif

 // Define State Enums
 typedef enum TV_OPERATION {IDLE, POWER_ON, POWER_OFF, CHANNEL_MODE, VOLUME_MODE} TvOperation;
 typedef enum BUTTONPRESS {NONE, UP, DOWN, BOTH} ButtonPress;
 
 // Push button Macros
 #define PB1                  PORTBbits.RB4
 #define PB2                  PORTAbits.RA4

 // Global variables
extern volatile ButtonPress ButtonPressed;
extern volatile TvOperation tvState;

 // State functions
 void PowerOn(void);
 void PowerOff(void);
 void Change_Channel(unsigned char channel_dir);
 void Change_Volume(unsigned char volume_dir);
 void startbit(void);
 void digital_one(void);
 void digital_zero(void);

 // Helper functions
 void PollLength(void);

 #endif


