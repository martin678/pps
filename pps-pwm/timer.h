/*
 * timer.h
 *
 *  Created on: 2012-10-28
 *      Author: martin.gagnon
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <time.h>
#include <sys/neutrino.h>

class Timer {
public:
	Timer();
	Timer(int chid, int pulse_code);
	virtual ~Timer();

	void init(int chid, int pulse_code);
	void start_ms(int ms);

private:
	int mTimerID;
	int	mChID;
	int mPulseCode;
};

#endif /* TIMER_H_ */
