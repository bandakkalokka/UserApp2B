/* 
 * File:   IO.h
 * Author: bandakka
 *
 * Created on September 25, 2017, 9:54 AM
 */

#ifndef IO_H
#define	IO_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

extern volatile unsigned int CNFlag;

void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void);

void InitCN(void);

void PollCN (void);


#endif	/* IO_H */