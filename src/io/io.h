#pragma once

#include "olcPixelGameEngine.h"
#include <iostream>

class IO : public olc::PixelGameEngine
{
public:
	IO(int display_height, int display_width);
	~IO();

	bool OnUserCreate() override;
	bool OnUserUpdate(float elpasedTime) override;

private:

};
