This repository is unpolished and contains duplicated code with minor changes.
I guess this can be confusing.
The repository contains:
1. A bitbang protocol to write FABulous bitstreams from Arduino Flash
2. A custom UART protocol (implements a weird clock rate that was needed because of an undetected error made before tape-out) to send data from host PC via UART to Arduino that sends with a custom baud rate (UART) to FPGA
3. The custom UART protocol from before but here the configuration is taken from FLASH

For the more polished repository refer to: [FABulous Arduino](https://github.com/matztron/FABulous_Arduino_Bitbang).
