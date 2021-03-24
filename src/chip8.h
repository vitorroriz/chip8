#pragma once

#include <cstring>
#include <iostream>
#include "io/io.h"

const int MEMORY_SIZE = 4096; //Size (bytes) of main memory
const int N_GEN_PURPOSE_REGISTERS = 16; //Number of general purpose registers
const int STACK_SIZE = 16; // Size of the stack in words of 16 bits. Each word is used to store an address.
const int DISPLAY_HEIGHT = 32; // Height of display in pixels
const int DISPLAY_WIDTH = 64; // Width of display in pixels


const uint16_t MEMORY_START_ADDR = 0x200;


class Chip8
{
public:
	Chip8();
	~Chip8();

	void run();
	void stop();

private:
	uint8_t _memory[MEMORY_SIZE]; // Main memory

	//Registers
	uint16_t _reg_pc; //program counter
	uint16_t _reg_i; //register commonly used to store addresses
	uint8_t _reg_v[N_GEN_PURPOSE_REGISTERS]; //General purpose registers Vx (V0, V1, ...V9, VA, ..VF)
	uint8_t _reg_sp; //Stack pointer
	uint8_t _reg_delay;
	uint8_t _reg_timer;
	uint8_t _reg_vf; //used as flag by some instructions

	uint16_t _stack[STACK_SIZE]; //stack is 16x16 bits, it can store 16 addresses. Note that an address is only 12 bits.

	//IO
	IO<DISPLAY_HEIGHT, DISPLAY_WIDTH>* io;

	void executeInstruction(uint16_t opCode);
	void cycle();
	bool running{ true };

};

