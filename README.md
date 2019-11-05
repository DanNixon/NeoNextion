# NeoNextion

[![Build Status](https://travis-ci.org/DanNixon/NeoNextion.svg?branch=master)](https://travis-ci.org/DanNixon/NeoNextion)
[![No Maintenance Intended](http://unmaintained.tech/badge.svg)](http://unmaintained.tech/)

An Arduino library for the
[Nextion](http://wiki.iteadstudio.com/Nextion_HMI_Solution) line of displays.

The code is heavily based on the [official
library](https://github.com/itead/ITEADLIB_Arduino_Nextion) but aims to be
cleaner, more user friendly and with a bit of luck, faster.

Available through the library manager of the Arduio IDE as `NeoNextion`.

## New features

Added by Viktor1970: 
1. Removed a check in sendMessage method, that prevents to control objects in other pages.  Now the page's show() method it's working.

2. Added 2 methods to Nextion.h/.cpp:

`ActivateWakeEvent(uint8_t page_id, uint8_t component_id);`
This method permits to execute a callback handler attached to **component_id** in **page_id** when the display wakes up after sleep.

`DeActivateWakeEvent();`
This method stops to execute callback described above (so wake-up after sleep send no event to code).

## Links

- Original Repository: https://github.com/DanNixon/NeoNextion
- Travis CI: https://travis-ci.org/DanNixon/NeoNextion
- Documentation: https://dannixon.github.io/NeoNextion
