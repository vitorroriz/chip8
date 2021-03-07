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

IO::IO()
{
	std::cout << "IO created" << std::endl;
	Construct(256, 240, 4, 4);
	Start();
}

IO::~IO()
{
}
