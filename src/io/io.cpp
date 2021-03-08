#include "io.h"

bool IO::OnUserCreate()
{
	return true;
}

bool IO::OnUserUpdate(float elpasedTime)
{
	return true;
}

IO::IO(int displayHeight, int displayWidth)
{
	Construct(displayWidth, displayHeight, 8, 8);
	Start();
}

IO::~IO()
{
}
