#include <iostream>
#include <fstream>

#include "chip8.h"

int main(int argc, char* argv[])
{

	if (argc != 2) {
		std::cout << "Expected to receive path to ROM file as parameter" << std::endl;
		return -1;
	}

	Chip8 chip8(argv[1]);
	chip8.run();

	return 0;
}