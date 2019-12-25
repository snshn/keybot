# keybot

[![Travis CI Build Status](https://travis-ci.org/Y2Z/keybot.svg?branch=master)](https://travis-ci.org/Y2Z/keybot)

Automated text input utility for macOS and GNU/Linux

Comes in handy:
- for GUI automation
- when need to input keys, passwords, and other chunks of text into UI applications

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
The Unlicense

<!-- Microtext -->
<sub>Arguments supplied to this tool will be visible in the process list to all users as well as via shell history</sub>
