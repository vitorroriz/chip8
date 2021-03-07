#pragma once

#include <cstring>
#include <iostream>
#include "io/io.h"

const int MEMORY_SIZE = 4096; //Size (bytes) of main memory
const int N_GEN_PURPOSE_REGISTERS = 16; //Number of general purpose registers
const int STACK_SIZE = 16; // Size of the stack in words of 16 bits. Each word is used to store an address.

const uint16_t MEMORY_START_ADDR = 0x200;


class Chip8
{
public:
	Chip8();
	~Chip8();

private:
	uint8_t _memory[MEMORY_SIZE]; // Main memory

	//Registers
	uint16_t _reg_pc; //program counter
	uint16_t _reg_i; //register commonly used to store addresses
	uint8_t _reg_v[N_GEN_PURPOSE_REGISTERS]; //General purpose registers Vx (V0, V1, ...V9, VA, ..VF)
	uint8_t _reg_sp; //Stack pointer
	uint8_t _reg_delay;
	uint8_t _reg_timer;

	uint16_t _stack[STACK_SIZE]; //stack is 16x16 bits, it can store 16 addresses. Note that an address is only 12 bits.

	//IO
	IO* io;

};

Chip8::Chip8() : _reg_pc(MEMORY_START_ADDR), _reg_sp(0), _reg_i(0), _reg_delay(0), _reg_timer(0), io(new IO())
{
	std::cout << "helloooooooooooo" << std::endl;
	std::memset(_memory, 0, sizeof _memory);
	std::memset(_reg_v, 0, sizeof _reg_v);
	std::memset(_stack, 0, sizeof _stack);
}

Chip8::~Chip8()
{
	delete io;
}
