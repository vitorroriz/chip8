#include "chip8.h"
#include <cassert>

void Chip8::cycle()
{
	executeInstruction(_memory[_reg_pc]);
}

void Chip8::executeInstruction(uint16_t opcode)
{
	const uint8_t opcodeNibble3 = (opcode & 0xF000) >> 12;
	const uint8_t opcodeNibble2 = (opcode & 0x0F00) >> 8;
	const uint8_t opcodeNibble1 = (opcode & 0x00F0) >> 4;
	const uint8_t opcodeNibble0 = (opcode & 0x000F);

	auto incrementProgramCounter = [&]() { _reg_pc += 2; };

	incrementProgramCounter(); // prepare for next fetch

	switch (opcode & 0xF000) {
		case 0x0000: {
			switch (opcode) {
				// 0x00E0 - clear the display
				case 0x00E0:
					io->Clear(olc::BLACK);
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
		// 2nnn - Call subroutine at address nnn after saving placing current PC into the stack
		case 0x2000:
			++_reg_sp;
			_stack[_reg_sp] = _reg_pc;
			_reg_pc = opcode & 0x0FFF;
			break;
		// 3xkk - Skip the next instruction if V[x] == kk
		case 0x3000:
			if (_reg_v[opcodeNibble2] == (opcode & 0x00FF)) {
				incrementProgramCounter();
			}
			break;
		// 4xkk - Skip the next instruction if V[x] != kk
		case 0x4000:
			if (_reg_v[opcodeNibble2] != (opcode & 0x00FF)) {
				incrementProgramCounter();
			}
			break;
		// 5xy0 - Skip the next instruction if V[x] == V[y]
		case 0x5000:
			if (_reg_v[opcodeNibble2] == _reg_v[opcodeNibble1]) {
				incrementProgramCounter();
			}
			break;
		// 6xkk - Loads the value kk into V[x]
		case 0x6000:
			_reg_v[opcodeNibble2] = opcode & 0x00FF;
			break;
		// 7xkk - Loads the value V[x] + kk into V[x]
		case 0x7000:
			_reg_v[opcodeNibble2] = _reg_v[opcodeNibble2] + (opcode & 0x00FF);
			break;
		// 8xy_
		case 0x8000: {
			switch (opcodeNibble0) {
				// 8xy0 - V[x] = V[y]
				case 0x0:
					_reg_v[opcodeNibble2] = _reg_v[opcodeNibble1];
					break;
				// 8xy1 - V[x] = V[x] or V[y]
				case 0x1:
					_reg_v[opcodeNibble2] |= _reg_v[opcodeNibble1];
					break;
				// 8xy2 - V[x] = V[x] and V[y]
				case 0x2:
					_reg_v[opcodeNibble2] &= _reg_v[opcodeNibble1];
					break;
				// 8xy3 - V[x] = V[x] xor V[y]
				case 0x3:
					_reg_v[opcodeNibble2] ^= _reg_v[opcodeNibble1];
					break;
				// 8xy4 - V[x] = V[x] + V[y], also set VF to carry
				case 0x4:
					uint16_t sum = _reg_v[opcodeNibble2] + _reg_v[opcodeNibble1];
					_reg_vf = (sum & 0xF0) ? 1 : 0;
					_reg_v[opcodeNibble2] = static_cast<uint8_t>(sum & 0xF);
					break;
			}
		}
	}

}