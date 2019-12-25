# keybot

Automated text input utility for macOS and GNU/Linux (X11)

Comes in handy:
- when need to securely input keys, passwords, and other chunks of text into UI applications
- for GUI automation

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
