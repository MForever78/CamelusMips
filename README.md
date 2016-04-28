# CamelusMips ![build_status](https://travis-ci.org/MForever78/CamelusMips.svg?branch=master)

![Camel](doc/camel.jpg)

Yet Another MIPS Emulator.

## Instructions Supported

- R-type: addu, add, subu, sub, and, or, xor, nor, sltu, slt, sllv, srlv, srav, jr, sll, srl, sra
- I-type: addiu, addi, andi, ori, xori, lui, lw, sw, beq, bne, sltiu, slti
- J-type: j, jal

## Road Map

- [x] Assembler
    - [x] Basic intructions
    - [ ] Advanced intructions
    - [ ] Directives
- [x] Disassembler
- [x] Exporter
    - [x] Export to Xilinx coe file, ASCII hex, ASCII bin, and binary file
- [x] MIPS CPU core
    - [x] Interrupt
    - [ ] Exception
- [ ] Basic GUI
- [ ] Peripheral 
    - [x] VGA
    - [x] Timer
    - [ ] PS2 keyboard
    - [ ] Serial port
    - [ ] Ethernet
- [ ] Advanced GUI
- [x] Command line tools

## Commandline Usage

```
$ ./CamelusMips [-d] [-f filepath] [-h]
Supported options:
  -d [ --debug ]        Enable debug mode
  -f [ --file ] arg     Assign assembly file
  -h [ --help ]         This help message
```
