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
	const std::string FONT_E = {
	"11111   "
	"1       "
	"11111   "
	"1       "
	"11111   "
	};
	const std::string FONT_e = {
	" 111    "
	"1   1   "
	"11111   "
	"1       "
	"1111    "
	};
	const std::string FONT_F = {
	"11111   "
	"1       "
	"11111   "
	"1       "
	"1       "
	};
	const std::string FONT_f = {
	" 1111   "
	"1       "
	"1111    "
	"1       "
	"1       "
	};
	const std::string FONT_G = {
	" 1111   "
	"1       "
	"1  111  "
	"1   1   "
	" 111    "
	};
	const std::string FONT_H = {
	"1  1    "
	"1  1    "
	"1111    "
	"1  1    "
	"1  1    "
	};
	const std::string FONT_I = {
	"1       "
	"1       "
	"1       "
	"1       "
	"1       "
	};
	const std::string FONT_i = {
	"1       "
	"        "
	"1       "
	"1       "
	"1       "
	};
	const std::string FONT_J = {
	" 111    "
	"  1     "
	"  1     "
	"1 1     "
	"111     "
	};
	const std::string FONT_K = {
	"1  1    "
	"1 1     "
	"11      "
	"1 1     "
	"1  1    "
	};
	const std::string FONT_O = {
	" 1111   "
	"1    1  "
	"1    1  "
	"1    1  "
	" 1111   "
	};
	const std::string FONT_o = {
	"        "
	" 111    "
	"1   1   "
	"1   1   "
	" 111    "
	};
	const std::string FONT_P = {
	"1111    "
	"1  1    "
	"111     "
	"1       "
	"1       "
	};
	const std::string FONT_R = {
	"1111    "
	"1  1    "
	"1 1     "
	"1  1    "
	"1   1   "
	};
	const std::string FONT_r = {
	"        "
	"111     "
	"1       "
	"1       "
	"1       "
	};
	const std::string FONT_S = {
	" 111    "
	"1       "
	" 11     "
	"   1    "
	"1111    "
	};
	const std::string FONT_T = {
	"11111   "
	"  1     "
	"  1     "
	"  1     "
	"  1     "
	};
	const std::string FONT_t = {
	"        "
	" 1      "
	"111     "
	" 1      "
	" 1      "
	};
	const std::string FONT_V = {
	"1   1   "
	"1   1   "
	" 1 1    "
	" 1 1    "
	"  1     "
	};
	const std::string FONT_Y = {
	"1   1   "
	"1   1   "
	" 111    "
	"  1     "
	"  1     "
	};
}



