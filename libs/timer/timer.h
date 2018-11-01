/*
 * timer.h
 *
 * Created: 22-12-2016 10:29:56 PM
 *  Author: JOMON THOMAS
 */ 


#ifndef TIMER_H_
#define TIMER_H_


void timer_init(void);
void timer_start(void);

int get_timer_seconds(void);
int get_timer_minutes(void);
void set_timer_seconds(int time);
void set_timer_minutes(int time);

#endif /* INCFILE1_H_ */