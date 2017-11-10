/* 
 * File:   Input-Capture.h
 * Author: bandakka
 *
 * Created on November 3, 2017, 11:11 AM
 */

#ifndef INPUT_CAPTURE_H
#define	INPUT_CAPTURE_H

#define LENGTH 34

#define LOWER_ZERO 0x1000
#define UPPER_ZERO 0x1FFF
#define LOWER_ONE 0x2000
#define UPPER_ONE 0x2FFF
#define LOWER_START 0x8000
#define UPPER_START 0x8FFF
typedef enum STATE {RESET, READ, CHECK} TvState;
typedef enum MODE {CHANNEL_UP, CHANNEL_DOWN, VOLUME_UP, VOLUME_DOWN, POWER, INVALID} mode;

extern volatile unsigned int CNFlag;
extern volatile unsigned int ICFlag;
extern volatile TvState STATE;
extern volatile mode CHECKCOMMAND;

extern volatile unsigned int TMRVAL[LENGTH];
extern volatile int i;
#ifdef	__cplusplus
extern "C" {
#endif

    void InitInComp(void);
    void __attribute__((interrupt, no_auto_psv)) _IC1Interrupt(void);
    mode checkCommand(void);


#ifdef	__cplusplus
}
#endif

#endif	/* INPUT_CAPTURE_H */

