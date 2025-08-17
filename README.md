
# Overview
This is an emulation of IR remote. This project aims to bring basic RS-232 control to consumer-grade VCRs is based on modified [ATmega8 IR library](https://github.com/itpcc/IRremote-ATMega8) and is intended to be used with [RS-232 software remote](https://github.com/r3dfx080/RS232_remote) app.

Only Panasonic protocol is tested & available at the moment.

ATmega328P is used since it's cheap & available in form of Arduino Nano clones. This repository has Microchip project file as well as already assembled firmware.
# Command set
This "remote" is based on Panasonic's [VEQ1656](https://lirc.sourceforge.net/remotes/panasonic/VEQ1656) with basic functions implemented. Here's the list of available commands:
| Button | Command |
|--|--|
| PLAY | 0x09000009 |
| STOP/EJECT | 0x09000009 |
| FF | 0x0900C0C9 |
| REW | 0x09004049 |
| PAUSE | 0x09006069 |
| SLOW | 0x0900F0F9 |
| REC | 0x09001019 |
| MENU | 0x09806AE3 |
| OSD | 0x0900EAE3 |
| TRACKING+/ 'UP' key | 0x098066EF |
| TRACKING- | 0x098040C9 |
| 'DOWN' key | 0x0980C049 |
| STORE/OK | 0x09801A93 |

EJECT is implemented by emulating STOP press for 2-3s. Long pressing STOP button triggers EJECT on later Panasonic models.

# Physical connection

<img width="1389" height="1000" alt="atmega_connectivity" src="https://github.com/user-attachments/assets/186748f5-ccda-4002-95cd-1ea4f842c97d" />

IR transmitter connects to D9 (PWM) pin and RS-232 receiver to RX0 accordingly. As simple as it gets!

# What's next?
I own only Panasonic and Philips VCRs atm, so Philips protocol will be my first priority. 

Whole remote emulation is out of scope of this project, however I'm going to add a few more of 'basic' buttons. 
