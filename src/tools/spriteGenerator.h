#pragma once
#include <vector>
#include <string>

class Sprite
{
public:
	Sprite() : _size{ 0 }
	{
	}

	~Sprite()
	{
	}

	size_t size() { return _size; }

	void copyToMemory(uint8_t* location);
	//Each line is 8 chars, more than that will generate a new line
	void addLine(std::string line); 
	void addLines(std::string line);

private:
	size_t _size; //number (bytes) of sprite. Each byte is a line.
	std::vector<uint8_t> lines;
};




