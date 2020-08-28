# ARM-ISA-Simulator
Simulator program for the ARM Instruction Set Architecture

## Motivation
> TODO

## Build Status
![Main CI](https://github.com/KaravolisL/ARM-ISA-Simulator/workflows/Main%20CI/badge.svg)

## Code style
> TODO

## Screenshots
> TODO

## Features
### Instructions
Currently, the following ARM instructions are supported:  
| Logic | Arithmetic | Flow Control | Memory | Other |  
|:-----:|:----------:|:------------:|:------:|:-----:|
| AND   | ADD        | B            | LDR    | MOV   |
| ORR   | SUB        | BL           | STR    | CMP   |
| BIC   |            | BX           | LDM    | CMN   |
| EOR   |            | BLX          | STM    | TST   |
| LSL   |            |              | PUSH   | NOP   |
| LSR   |            |              | POP    |       |

Variants of these instructions are also supported according to the ARM instruction set architecture. For instance, conditional codes can be appended to enable conditional execution.

### Memory Layout
At startup, memory is allocated for the user's program. 1024 bytes are designated for the process's stack. 512 bytes are provided for the process's heap memory. 15360 additional bytes are allocated for the user's static data section.


## Installation
1. Clone Repository
2. Run following commands: \
   ```mkdir build``` \
   ```cd build``` \
   ```cmake ..``` \
   ```make```
3. To run unit and integration tests, execute following command \
   ```make test```
4. To execute program, execute following command \
   ```./src/ARM-ISA-Simulator <Name of main file>```

### Dependencies
Two external libraries are used, Catch2 and CLI11. You can find their respective installation guides at the links below:
* [CLI11](https://github.com/CLIUtils/CLI11#install)
* [Catch2](https://github.com/catchorg/Catch2/blob/master/docs/cmake-integration.md#installing-catch2-from-git-repository)
