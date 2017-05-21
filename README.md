# xkeyminator
An automated keyboard input tool for X11.

Comes in handy to securely input pubkeys into java-based web VNCs and in other
similar situations where there's no access to clipboard buffer but the string
of information is known, yes is too long to type in by hand.

## Usage
    sleep 5 && xkeyminator "ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAACA..."

## Build
    make clean all

## Install
    make install

## Uninstall
    make uninstall
