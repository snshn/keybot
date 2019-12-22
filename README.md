# keybot

Automated text input utility
 
Comes in handy:
- when need to securely input keys, passwords, and other chunks of text into UI applications that don't support pasting from clipboard
- for GUI automation

## Usage
    sleep 5 && keybot "ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAACA..."
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
<sub>Arguments supplied to this tool will be visible in the process list to all users and also via shell history</sub>
