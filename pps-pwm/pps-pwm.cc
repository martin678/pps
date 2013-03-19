#include <cstdlib>
#include <iostream>
#include <sys/neutrino.h>
#include <unistd.h>
#include <stdio.h>

#include "Timer.h"
#include "pps.h"

#define PULSE_CODE_ON   _PULSE_CODE_MINAVAIL
#define PULSE_CODE_OFF   (_PULSE_CODE_MINAVAIL + 1)

typedef union {
	struct _pulse pulse;
} my_message_t;

int main(int argc, char *argv[]) {
	int freq_hz = 10;
	int dutyCycle = 50;
	int period = 0;
	int tON = 0;

	int chid;
	int rcvid;
	my_message_t msg;

	// Prends vie dans le filesystem pps
	PPSObject	ppsObj("/pps/PWM1");

	// Setup des timers Ton, Toff
	chid = ChannelCreate(0);
	Timer	tmrON(chid, PULSE_CODE_ON);
	Timer	tmrOFF(chid, PULSE_CODE_OFF);

	// Calcule la période et temps ON
	period = (int)(1000 / freq_hz);
	tON = dutyCycle * period / 100;

	tmrON.start_ms(period);
	usleep(tON * 1000);	// en micro secomdes
	tmrOFF.start_ms(period);

	for (;;) {
		rcvid = MsgReceive(chid, &msg, sizeof(msg), NULL);
		if (rcvid == 0) { /* we got a pulse */
			if (msg.pulse.code == PULSE_CODE_ON) {
				printf("ON\n");
			}
			if (msg.pulse.code == PULSE_CODE_OFF) {
				printf("OFF\n");
				// Read dutyCycle and freq values
				// Update if requis!
			}
			fflush(stdout);
		}
	}

	return EXIT_SUCCESS;
}
