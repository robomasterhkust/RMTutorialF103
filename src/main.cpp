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

#include "chprintf.h"
#include "userShell.hpp"

#include "button.hpp"
#include "morseCode.hpp"

using namespace chibios_rt;

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

  UserShell::initShell();
  Button::buttonStart();
  MorseCode::morseCodeStart();
  /*
	 * Normal main() thread activity
   * since this is doing nothing, you can just call "return 0;" here
   * as long as CH_CFG_NO_IDLE_THREAD is FALSE in cfg/chconf.h
	 */
  while (true)
  {
    //example for interval waiting instead of delays
    systime_t startT = chibios_rt::System::getTime();

    // ... something to be done every 1000 ms ...

    //this function will wait until 1000 ms is passed since startT
    chibios_rt::BaseThread::sleepUntil(startT + TIME_MS2I(1000));

    //chThdSleepMilliseconds(1000); // <- delay which waits for a duration, not waiting until time point
  }
}
