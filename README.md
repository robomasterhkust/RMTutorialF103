# For Windows, refer to the [Wiki](https://github.com/robomasterhkust/RMTutorialF103/wiki/1_0_Setup_ChibiStudio_Windows) pages

# For Unix system(Tested on Ubuntu 16.04 & Mac OS Sierra 10.12.6)
By Yang Shaohui, Alex Au on 2018.09.13

## Getting started on Unix
run the following commands in the project directory
1.  For Linux, ubuntu to be exact: 
    `sudo apt-get install openocd gcc-arm-none-eabi`

    For Mac OSX, do the following: install homebrew first via https://brew.sh
    
    then install the XCode command line toolchain `xcode-select --install`
    
    `brew cask install xquartz java`
    
    `brew install open-ocd`
    
    `brew tap PX4/px4`
    
    `brew install px4-dev` 
    
2. `git clone https://github.com/robomasterhkust/RMTutorialF103` and
`cd RMTutorialF103` in your preferred directory

4. `make` or `make -j4` where 4 is the thread count

5. run `openocd -f openocd/start_st-link_flash.cfg` with board connected via st-link to flash the program
---
#### Optional:
- for debugging, run `openocd -f openocd/start_st-link_debug.cfg` , followed by a gdb connection with you own IDE/editor, the VSCode configuration is provided and is used with the "Cortex-Debug" extension
- of course you can always use `telnet localhost 4444` and use terminal to interface with the openocd debug server directly

## Submitting assignments 
This part will come up later on. 
