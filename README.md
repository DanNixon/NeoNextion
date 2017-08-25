# NeoNextion

[![Build Status](https://travis-ci.org/DanNixon/NeoNextion.svg?branch=master)](https://travis-ci.org/DanNixon/NeoNextion)

An Arduino library for the
[Nextion](http://wiki.iteadstudio.com/Nextion_HMI_Solution) line of displays.

The code is heavily based on the [official
library](https://github.com/itead/ITEADLIB_Arduino_Nextion) but aims to be
cleaner, more user friendly and with a bit of luck, faster.

Avaliable through the library manager of the Arduio IDE as `NeoNextion`.

## New features

Added by Viktor1970: 
- removed a check in sendMessage method, that prevents to control objects in other pages.  Now the page's show() method it's working.


## Links

- Original Repository: https://github.com/DanNixon/NeoNextion
- Travis CI: https://travis-ci.org/DanNixon/NeoNextion
- Documentation: https://dannixon.github.io/NeoNextion
