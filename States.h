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
 typedef enum BUTTONPRESS {NONE, PB1, PB2, BOTH} ButtonPress;

 // Global variables
extern volatile ButtonPress ButtonPressed;
extern volatile TvOperation tvState;

 // State functions
 void PowerOn(void);
 void PowerOff(void);
 void Change_Channel(unsigned char channel_dir);
 void Change_Volume(void);
 void startbit(unsigned int count);
 void digital_one(void);
 void digital_zero(void);

 // Helper functions
 void PollLength(void);

 #endif


