#pragma once
#include <vector>
#include <string>
namespace SpriteGen {
class Sprite
{
public:
	Sprite() : _size{ 0 }
	{
	}

	Sprite(std::string lines) : _size{ 0 }
	{
		addLines(lines);
	}

	~Sprite()
	{
	}

	size_t size() { return _size; }

	void copyToMemory(uint8_t* location);
	//Each line is 8 chars, more than that will generate a new line
	void addLine(std::string newline);
	void addLines(std::string newLines);
	const uint8_t* data() { return lines.data(); }

private:
	size_t _size; //number (bytes) of sprite. Each byte is a line.
	std::vector<uint8_t> lines;
};

	const std::string FONT_A = {
	"11111   "
	"1   1   "
	"11111   "
	"1   1   "
	"1   1   "
	};
	const std::string FONT_a = {
	"        "
	"1111    "
	"1  1    "
	"1  1    "
	"11111   "
	};
	const std::string FONT_B = {
	"111     "
	"1  1    "
	"111     "
	"1  1    "
	"111     "
	};

	const std::string FONT_b = {
	"1       "
	"1       "
	"111     "
	"1  1    "
	"111     "
	};
	const std::string FONT_C = {
	" 111    "
	"1   1   "
	"1       "
	"1   1   "
	" 111    "
	};
	const std::string FONT_c = {
	"        "
	"        "
	"1111    "
	"1       "
	"1111    "
	};
	const std::string FONT_D = {
	"1111    "
	"1   1   "
	"1   1   "
	"1   1   "
	"1111    "
	};
	const std::string FONT_d = {
	"   1    "
	"   1    "
	"1111    "
	"1  1    "
	"1111    "
	};
	const std::string FONT_e = {
	"11111   "
	"1       "
	"11111   "
	"1       "
	"11111   "
	};
	const std::string FONT_E = {
	" 111    "
	"1   1   "
	"11111   "
	"1       "
	"1111    "
	};
	const std::string FONT_V = {
	"1   1   "
	"1   1   "
	" 1 1    "
	" 1 1    "
	"  1     "
	};
	const std::string FONT_I = {
	"1       "
	"        "
	"1       "
	"1       "
	"1       "
	};
	const std::string FONT_T = {
	"11111   "
	"  1     "
	"  1     "
	"  1     "
	"  1     "
	};
	const std::string FONT_O = {
	" 1111   "
	"1    1  "
	"1    1  "
	"1    1  "
	" 1111   "
	};
	const std::string FONT_R = {
	"1111    "
	"1  1    "
	"1 1     "
	"1  1    "
	"1   1   "
	};
}



