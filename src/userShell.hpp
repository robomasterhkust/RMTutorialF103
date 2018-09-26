/**
 * @brief header file for the shell things 
 * 
 * @file shell.hpp
 * @author Alex Au
 * @date 2018-09-20
 */
#include "ch.hpp"

#include "ch.h"
#include "hal.h"

#include "shell.h"
#include "chprintf.h"

#define SHELL_SD SD1
#define SHELL_BAUD 115200u

namespace UserShell
{
extern const ShellCommand commands[];
extern const ShellConfig shell_cfg1;

/**
 * @brief start the thread on the specified serial port, this function should only be called once
 * 
 */
void initShell();

/**
 * @brief just a sample function that print something the terminal
 * 
 * @param chp 
 * @param argc 
 * @param argv 
 */
void shellTestPrint(BaseSequentialStream *chp, int argc, char *argv[]);
} // namespace UserShell