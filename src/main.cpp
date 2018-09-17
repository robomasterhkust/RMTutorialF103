/*
 ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

/**
 * @brief This file is based on the MAPLE MINI example from ChibiOS
 *
 * @file main.cpp
 * @author Alex Au
 * @date 2018-09-11
 */

#include "ch.hpp"

#include "ch.h"
#include "hal.h"

#include "shell.h"
#include "chprintf.h"

using namespace chibios_rt;

bool ledOn = true;
bool ButtonPressing = false;
event_source_t ButtonPressedEvt;
event_source_t ButtonReleasedEvt;

THD_WORKING_AREA(blinker_wa, 128);
THD_FUNCTION(blinker, arg)
{
	(void)arg;
	event_listener_t buttonPressLis;
	chEvtRegisterMask(&ButtonPressedEvt, &buttonPressLis, EVENT_MASK(0));
	while (!chThdShouldTerminateX())
	{
		if (ledOn)
		{
			palToggleLine(LINE_LED);
		}
		if (chEvtWaitAnyTimeout(EVENT_MASK(0), 750))
		{
			palWriteLine(LINE_LED, ~LED_ON_STATE);
			ledOn = !ledOn;
		}
	}
};

//this is done for software button debouncing, simple implementation by sampling the pin state with delay
THD_WORKING_AREA(buttonSampler_wa, 64);
THD_FUNCTION(buttonSampler, arg)
{
	(void)arg;
	while (!chThdShouldTerminateX())
	{
		if (palWaitLineTimeout(LINE_BUTTON, TIME_INFINITE) == MSG_OK)
		{
			//delay and sample the button
			chThdSleepMilliseconds(20);
			if (palReadLine(LINE_BUTTON) == BUTTON_PRESSED_STATE)
			{
				chEvtBroadcast(&ButtonPressedEvt);
				ButtonPressing = true;

				while (palReadLine(LINE_BUTTON) == BUTTON_PRESSED_STATE)
				{
					chThdSleepMilliseconds(20);
				}
				chEvtBroadcast(&ButtonReleasedEvt);
				ButtonPressing = false;
			}
		}
	}
};

/*
 * Application entry point.
 */
int main(void)
{

	/*
	 * System initializations.
	 * - HAL initialization, this also initializes the configured device drivers
	 *   and performs the board-specific initializations.
	 * - Kernel initialization, the main() function becomes a thread and the
	 *   RTOS is active.
	 */
	halInit();
	chSysInit();

	chThdCreateStatic(blinker_wa, sizeof(blinker_wa), NORMALPRIO, blinker, NULL);

	//setup for button interrupt and events
	chEvtObjectInit(&ButtonPressedEvt);
	chEvtObjectInit(&ButtonReleasedEvt);
	palEnableLineEvent(LINE_BUTTON, PAL_EVENT_MODE_FALLING_EDGE);
	chThdCreateStatic(buttonSampler_wa, sizeof(buttonSampler_wa), NORMALPRIO, buttonSampler, NULL);

	volatile int i = 0;
	/*
	 * Normal main() thread activity
	 */
	while (true)
	{
		i++;
		systime_t startT = chibios_rt::System::getTime();

		//do something..

		chibios_rt::BaseThread::sleepUntil(startT + TIME_MS2I(500));
		//chThdSleepMilliseconds(500); <- any difference using this?
	}
}
