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

THD_WORKING_AREA(blinker_wa, 128);
THD_FUNCTION(blinker, arg)
{
  (void)arg;
  while (!chThdShouldTerminateX())
  {
    if (ledOn)
    {
      palToggleLine(LINE_LED);
      chThdSleepMilliseconds(250);
    }
    else
    {
      chThdSleepMilliseconds(50);
    }
  }
};

void buttonPressedCallback(void *arg)
{
  (void)arg;
  chibios_rt::System::lockFromIsr(); //same as chSysLockFromISR();
  if (palReadLine(LINE_BUTTON) == BUTTON_PRESSED_STATE)
  {
    ledOn = !ledOn;
    if (!ledOn)
      palWriteLine(LINE_LED, ~LED_ON_STATE);
  }
  chSysUnlockFromISR();
}

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

  palEnableLineEvent(LINE_BUTTON, PAL_EVENT_MODE_FALLING_EDGE);
  palSetLineCallback(LINE_BUTTON, buttonPressedCallback, NULL);

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
