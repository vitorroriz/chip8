#include "chip8.h"
#include <cassert>


void Chip8::executeInstruction(uint16_t opcode)
{
	const uint8_t opcodeNibble3 = (opcode & 0xF000) >> 12;
	const uint8_t opcodeNibble2 = (opcode & 0x0F00) >> 8;
	const uint8_t opcodeNibble1 = (opcode & 0x00F0) >> 4;
	const uint8_t opcodeNibble0 = (opcode & 0x000F);

	_reg_pc += 2;

	switch (opcode & 0xF000) {
		case 0x0000: {
			switch (opcode) {
				case 0x00E0:
					io->Clear(olc::BLACK);
					break;
				case 0x00EE:
					_reg_pc = _stack[_reg_sp--];
					break;
				default: // 0x0nnn (This instruction can be ignored)
					break;
			}
			break;
		}
		case 0x1000:
			_reg_pc = opcode & 0x0FFF;
			break;
		case 0x2000:
			++_reg_sp;
			_stack[_reg_sp] = _reg_pc;
			_reg_pc = opcode & 0xFFF;
			break;
		case 0x3000:
			if (_reg_v[opcodeNibble2] == (opcode & 0x00FF)) {
				_reg_pc += 2;
			}
			break;
		case 0x4000:
			if (_reg_v[opcodeNibble2] != (opcode & 0x00FF)) {
				_reg_pc += 2;
			}
			break;
	}

}