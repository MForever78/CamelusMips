# CamelusMips

![Camel](doc/camel.jpg)

Yet Another MIPS Emulator.

## Instructions Supported

- R-type: addu, add, subu, sub, and, or, xor, nor, sltu, slt, sllv, srlv, srav, jr, sll, srl, sra
- I-type: addiu, addi, andi, ori, xori, lui, lw, sw, beq, bne, sltiu, slti
- J-type: j, jal

## Road Map

- [x] Assembler
- [x] Disassembler
    - [x] Basic intructions
    - [ ] Advanced intructions
    - [ ] Directives
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
- [ ] Command line tools
