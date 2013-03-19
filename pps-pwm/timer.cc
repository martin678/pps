/*
 * timer.cc
 *
 *  Created on: 2012-10-28
 *      Author: martin.gagnon
 */

#include "timer.h"
#include <sys/netmgr.h>

Timer::Timer() {
}

Timer::Timer(int chid, int pulse_code) {
	init(chid, pulse_code);
}

Timer::~Timer() {
}

void Timer::init(int chid, int pulse_code) {
	struct sigevent event;

	SIGEV_PULSE_INIT(&event,
			ConnectAttach(ND_LOCAL_NODE, 0, chid, _NTO_SIDE_CHANNEL, 0),
			getprio(0),
			pulse_code,
			0);

	//	event->sigev_notify = SIGEV_PULSE;
	//	event->sigev_coid = ConnectAttach(ND_LOCAL_NODE, 0, chid, _NTO_SIDE_CHANNEL,
	//			0);
	//	event->sigev_priority = getprio(0);
	//	event->sigev_code = pulse_code;

	timer_create(CLOCK_REALTIME, &event, &mTimerID);
}

void Timer::start_ms(int ms) {
	int secs = 0;
	int nsecs = 0;
	struct itimerspec timerSpec;

	secs = (int) (ms / 1000);
	nsecs = ms % 1000 * 1000000;

	timerSpec.it_value.tv_sec = secs;
	timerSpec.it_value.tv_nsec = nsecs;
	timerSpec.it_interval.tv_sec = secs;
	timerSpec.it_interval.tv_nsec = nsecs;

	timer_settime(mTimerID, 0, &timerSpec, NULL);
}
