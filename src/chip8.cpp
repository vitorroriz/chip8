#include "chip8.h"
#include <cassert>
#include <cstdlib>
#include <fstream>


void invalidInstruction(uint16_t opcode)
{
	std::cout << "Invalid instruction, opcode is " << std::hex << (int)opcode << std::endl;
	assert(false);
}

Chip8::Chip8(std::string romPath) : _reg_pc(MEMORY_START_ADDR), _reg_sp(0), _reg_i(0), _reg_delay_timer(0), _reg_sound_timer(0), io(new IO<DISPLAY_HEIGHT, DISPLAY_WIDTH>(8))
{
	std::memset(_memory, 0, sizeof _memory);
	std::memset(_reg_v, 0, sizeof _reg_v);
	std::memset(_stack, 0, sizeof _stack);

	uint8_t sprites[] = {
		0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
		0x20, 0x60, 0x20, 0x20, 0x70, // 1
		0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
		0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
		0x90, 0x90, 0xF0, 0x10, 0x10, // 4
		0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
		0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
		0xF0, 0x10, 0x20, 0x40, 0x40, // 7
		0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
		0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
		0xF0, 0x90, 0xF0, 0x90, 0x90, // A
		0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
		0xF0, 0x80, 0x80, 0x80, 0xF0, // C
		0xE0, 0x90, 0x90, 0x90, 0xE0, // D
		0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
		0xF0, 0x80, 0xF0, 0x80, 0x80, // F
	};

	//load sprites into cpu memory
	std::memcpy(&_memory[0], sprites, sizeof sprites);

	//load test code into memory (I = 0, Draw 5 bytes)
	/*
	uint8_t code[] = {
		0x0A, 0xA0, 0x05, 0xD0
	};
	std::memcpy(&_memory[MEMORY_START_ADDR], code, 4);
	*/
	//open rom file and load into memory
	std::ifstream ifs(romPath);
	std::string content((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));

	for (int i = 0; i < content.size(); i += 2) {
		_memory[MEMORY_START_ADDR + i] = content[i + 1];
		_memory[MEMORY_START_ADDR + i + 1] = content[i];
	}

}

Chip8::~Chip8()
{
	delete io;
}

void Chip8::run()
{
	//main loop
	while (running) {
		//handle io events
		io->pollInputEvents();
		running = io->isRunning();

		//cycle
		cycle();

		//update display
		io->displayUpdate();
	}
}

void Chip8::stop()
{
	running = false;
}

void Chip8::cycle()
{
	executeInstruction(uint16_t(_memory[_reg_pc] | (_memory[_reg_pc + 1] << 8)));
}

void Chip8::executeInstruction(uint16_t opcode)
{
	const uint8_t opcodeNibble3 = (opcode & 0xF000) >> 12;
	const uint8_t opcodeNibble2 = (opcode & 0x0F00) >> 8;
	const uint8_t opcodeNibble1 = (opcode & 0x00F0) >> 4;
	const uint8_t opcodeNibble0 = (opcode & 0x000F);

	uint8_t & Vx = _reg_v[opcodeNibble2];
	uint8_t & Vy = _reg_v[opcodeNibble1];

	auto incrementProgramCounter = [&]() { _reg_pc += 2 % (MEMORY_SIZE -2); };

	// prepare for next fetch
	incrementProgramCounter(); 

	switch (opcode & 0xF000) {
		case 0x0000: {
			switch (opcode) {
				// 0x00E0 - clear the display
				case 0x00E0:
				io->displayClearMemory();
					break;
				// 0x00EE - return from a subroutine
				case 0x00EE:
					_reg_pc = _stack[_reg_sp--];
					break;
				default: // 0x0nnn (This instruction can be ignored)
					break;
			}
			break;
		}
		// 1nnn - Jump to address nnn
		case 0x1000:
			_reg_pc = opcode & 0x0FFF;
			break;
		// 2nnn - Call subroutine at address nnn after saving current PC into the stack
		case 0x2000:
			++_reg_sp;
			_stack[_reg_sp] = _reg_pc;
			_reg_pc = opcode & 0x0FFF;
			break;
		// 3xkk - Skip the next instruction if V[x] == kk
		case 0x3000:
			if (Vx == (opcode & 0x00FF)) {
				incrementProgramCounter();
			}
			break;
		// 4xkk - Skip the next instruction if V[x] != kk
		case 0x4000:
			if (Vx != (opcode & 0x00FF)) {
				incrementProgramCounter();
			}
			break;
		// 5xy0 - Skip the next instruction if V[x] == V[y]
		case 0x5000:
			if (Vx == Vy) {
				incrementProgramCounter();
			}
			break;
		// 6xkk - Loads the value kk into V[x]
		case 0x6000:
			Vx = opcode & 0x00FF;
			break;
		// 7xkk - Loads the value V[x] + kk into V[x]
		case 0x7000:
			Vx = Vx + (opcode & 0x00FF);
			break;
		// 8xy_
		case 0x8000: {
			switch (opcodeNibble0) {
				// 8xy0 - V[x] = V[y]
				case 0x0:
					Vx = Vy;
					break;
				// 8xy1 - V[x] = V[x] or V[y]
				case 0x1:
					Vx |= Vy;
					break;
				// 8xy2 - V[x] = V[x] and V[y]
				case 0x2:
					Vx &= Vy;
					break;
				// 8xy3 - V[x] = V[x] xor V[y]
				case 0x3:
					Vx ^= Vy;
					break;
				// 8xy4 - V[x] = V[x] + V[y], also set VF to carry
				case 0x4: {
					uint16_t sum = Vx + Vy;
					_reg_vf = (sum & 0xF00) ? 1 : 0;
					Vx = static_cast<uint8_t>(sum & 0xFF);
					break;
				}
				// 8xy5 - V[x] = V[x] - V[y], VF = not borrow (If Vx > Vy, Vf = 1, otherwise Vf = 0)
				case 0x5:
					_reg_vf = Vx >= Vy ? 1 : 0;
						Vx -= Vy;
					break;
				// 8xy6 - Vx = SHR 1 (Shift Logical Right of Vx by 1). If the least-significant bit of Vx is 1, Vf = 1, otherwise Vf = 0.
				case 0x6:
					_reg_vf = Vx & 1;
					Vx <<= 1;
					Vx >>= 1;
					break;
				// 8xy7 - V[x] = V[y] - V[x], VF = not borrow (If Vy > Vx, Vf = 1, otherwise Vf = 0)
				case 0x7:
					_reg_vf = Vy >= Vx ? 1 : 0;
					Vx = Vy - Vx;
					break;
				// 8xyE - Vx = SHL 1 (Shift Logical Left of Vx by 1). If the most-significant bit of Vx is 1, Vf = 1, otherwise Vf = 0.
				case 0xE:
					_reg_vf = Vx & (1 << 7);
					Vx <<= 1;
					break;
				default:
					/* todo: create logger/assert to log invalid instruction */
					invalidInstruction(opcode);
					break;
			}
			break;
		}
		//0x9xy0 - Skip next instruction if V[x] != V[y]
		case 0x9000:
			if (opcodeNibble0 !=  0) {
				invalidInstruction(opcode);
				break;
			}
			if (Vx != Vy) {
				incrementProgramCounter();
			}
			break;
		//0xAnnn - Set register I = nnn
		case 0xA000:
			_reg_i = opcode & 0x0FFF;
			break;
		//0xBnnn Jump to location nnn + V[0] (pc = nnn + V[0])
		case 0xB000:
			_reg_pc = (opcode & 0x0FFF) + _reg_v[0];
			break;
		//0xCxkk - Vx = random (byte) AND kk
		case 0xC000:
			Vx = (std::rand() % 256) & (opcode & 0x00FF);
			break;
		//0xDxyn - Draw n-byte sprite starting at memory location I at (V[x], V[y]), set VF = collision
		case 0xD000: {
			_reg_vf = 0;
			_reg_vf |= io->displayLoadData(Vx, Vy, &_memory[_reg_i], opcodeNibble0);
			break;
		}
		//
		case 0xE000: {
			//0xEx9E - Skip next instruction if key with the value of Vx is pressed.
			if ((opcode & 0xFF) == 0x9E) {
				if (io->isKeyPressed(Vx)) {
					incrementProgramCounter();
				} 
			//0xExA1 - Skip next instruction if key with the value of Vx is not pressed.
			} else if ((opcode & 0xFF) == 0xA1) {
				if (!io->isKeyPressed(Vx)) {
					incrementProgramCounter();
				} 
			} else {
				invalidInstruction(opcode);
			}
			break;
		}
		case 0xF000: {
			switch (opcode & 0xFF) {
				// 0xFx07 - Set Vx = delay timer value.
				case 0x07:
					Vx = _reg_delay_timer;
					break;
				// 0xFx0A - Wait for a key press, store the value of the key in Vx.
				case 0x0A:
					Vx = io->waitForInputEvent();
					break;
				// 0xFx15 - Set delay timer = Vx.
				case 0x15:
					_reg_delay_timer = Vx;
					break;
				// 0xFx18 - Set sound timer = Vx.
				case 0x18:
					_reg_sound_timer = Vx;
					break;
				// 0xFx1E - Set I = I + Vx.
				case 0x1E:
					_reg_i += Vx;
					break;
				// 0xFx29 - Set I = location of sprite for digit Vx.
				case 0x29:
					_reg_i = Vx * 5; // sprites (5 bytes) are stored starting from virtual addr 0 
					break;
				/* 0xFx33 - The interpreter takes the decimal value of Vx, and places the hundreds digit in memory at location in I,
							the tens digit at location I+1, and the ones digit at location I+2. */
				case 0x33: {
					_memory[_reg_i + 2] = Vx % 10;
					_memory[_reg_i + 1] = (Vx / 10) % 10;
					_memory[_reg_i]		= (Vx / 100); //we can ommit % 10, because max val (255) is smaller than 1000 
					break;
				}
				// Fx55 - Store registers V0 through Vx in memory starting at location I.
				case 0x55:
					for (int i = 0; i <= opcodeNibble2; ++i) {
						_memory[_reg_i + i] = _reg_v[i];
					}
					break;
				// Fx65 - Read registers V0 through Vx from memory starting at location I. 
				case 0x65:
					for (int i = 0; i <= opcodeNibble2; ++i) {
						_reg_v[i] = _memory[_reg_i + i];
					}
					break;
				default:
					invalidInstruction(opcode);
					break;
			}
			break;
		}

		default:
			//std::cout << "Instruction not implemented" << std::endl;
			break;
	}
}