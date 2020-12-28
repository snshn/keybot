# keybot

[![Travis CI Build Status](https://travis-ci.org/Y2Z/keybot.svg?branch=master)](https://travis-ci.org/Y2Z/keybot)

Automated text input utility for macOS and GNU/Linux

Comes in handy:
- for GUI automation
- when need to input keys, passwords, and other senstive information into GUI applications

Currently does not have support for non-ASCII characters


## Usage

    sleep 5 && keybot "john.doe@mywebsite.net"
or

    sleep 5 && cat ~/.ssh/id_rsa.pub | keybot


## Build

    make clean all


## Install

    make install


## Uninstall

    make uninstall


## License

<a href="http://creativecommons.org/publicdomain/zero/1.0/">
    <img src="http://i.creativecommons.org/p/zero/1.0/88x31.png" alt="CC0" />
</a>
<br />
To the extent possible under law, the author(s) have dedicated all copyright related and neighboring rights to this software to the public domain worldwide.
This software is distributed without any warranty.


<!-- Microtext -->
<sub>Arguments supplied to this tool will be visible in the process list to all users as well as via shell history</sub>
