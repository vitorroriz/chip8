#include "spriteGenerator.h"
#include "spriteGenerator.h"

void SpriteGen::Sprite::copyToMemory(uint8_t *location)
{
	memcpy(location, lines.data(), _size);
}

void SpriteGen::Sprite::addLine(std::string newLine)
{
	uint8_t res{ 0 };
	
	for (int i = 0; i < newLine.size(); ++i) {
		if (newLine[i] != ' ' &&  newLine[i] != '.' && newLine[i] != '0') {
			res |= (1 << (7 - i));
		}
	}

	lines.push_back(res);
	++_size;
}

void SpriteGen::Sprite::addLines(std::string newLines)
{
	int limit = newLines.size() % 8 ? newLines.size() + 1 : newLines.size();
	for (int i = 0; i < limit / 8; ++i) {
		auto line = newLines.substr(i * 8, 8);
		if (line.empty()) {
			break;
		}
		addLine(line);
	}
}


