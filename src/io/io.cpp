#include "io.h"

bool IO::OnUserCreate()
{
	std::cout << "OnUserCreate" << std::endl;
	return true;
}

bool IO::OnUserUpdate(float elpasedTime)
{
	return true;
}

IO::IO(int displayHeight, int displayWidth)
{
	std::cout << "IO created" << std::endl;
	Construct(displayWidth, displayHeight, 8, 8);
	Start();
}

IO::~IO()
{
}
