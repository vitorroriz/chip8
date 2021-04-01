#include "spriteGenerator.h"
#include "spriteGenerator.h"

void Sprite::copyToMemory(uint8_t *location)
{
	memcpy(location, lines.data(), _size);
}

void Sprite::addLine(std::string line)
{
	uint8_t newLine{ 0 };
	
	for (int i = 0; i < line.size(); ++i) {
		if (line[i] != ' ' || line[i] != '.') {
			newLine |= (1 << i);
		}
	}

	++_size;
}

void Sprite::addLines(std::string line)
{
}

