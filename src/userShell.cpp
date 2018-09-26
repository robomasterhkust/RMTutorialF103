/**
 * @brief 
 * 
 * @file shell.cpp
 * @author Alex Au
 * @date 2018-09-20
 */

#include "userShell.hpp"

namespace UserShell
{
const ShellCommand commands[] =
    {
        {"testPrint", shellTestPrint},
        {NULL, NULL}};

static const SerialConfig shellSDConfig =
    {SHELL_BAUD, 0, USART_CR2_STOP1_BITS, 0};

const ShellConfig shell_cfg1 = {
    (BaseSequentialStream *)&SHELL_SD,
    commands};

THD_WORKING_AREA(shell_wa, 512);

void initShell()
{
    sdStart(&SHELL_SD, &shellSDConfig);
    shellInit();
    thread_t *a_thread_pointer =
        chThdCreateStatic(&shell_wa,
                          sizeof(shell_wa),
                          NORMALPRIO + 1,
                          shellThread,
                          (void *)&shell_cfg1);

    chRegSetThreadNameX(a_thread_pointer,
                        "shell");
}

void shellTestPrint(BaseSequentialStream *chp, int argc, char *argv[])
{
    chprintf(chp, "argc = %d\n", argc);
    for (int i = 0; i < argc; i++)
    {
        chprintf(chp, "argv[%d] = %s\n", i, argv[i]);
    }
}
} // namespace UserShell
