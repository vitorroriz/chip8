#pragma once

#include "olcPixelGameEngine.h"
#include <iostream>

class IO : public olc::PixelGameEngine
{
public:
	IO();
	~IO();

	bool OnUserCreate() override;
	bool OnUserUpdate(float elpasedTime) override;

private:

};
