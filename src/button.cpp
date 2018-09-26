#include "button.hpp"

namespace Button
{
volatile bool ButtonPressing = false;
event_source_t ButtonPressedEvt;
event_source_t ButtonReleasedEvt;

//this is done for software button debouncing, simple implementation by sampling the pin state with delay
THD_WORKING_AREA(buttonSampler_wa, 64);
THD_FUNCTION(buttonThdFunc, arg)
{
    (void)arg;
    chRegSetThreadName("buttonThdFunc");
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

void buttonStart()
{
    chEvtObjectInit(&ButtonPressedEvt);
    chEvtObjectInit(&ButtonReleasedEvt);
    palEnableLineEvent(LINE_BUTTON, PAL_EVENT_MODE_FALLING_EDGE);
    chThdCreateStatic(&buttonSampler_wa,
                      sizeof(buttonSampler_wa),
                      NORMALPRIO + 2,
                      buttonThdFunc,
                      NULL);
}

} // namespace Button