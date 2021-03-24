#pragma once

#include <iostream>
#include "sdl/include/SDL2/SDL.h"
#include <vector>
#include <bitset>

class IO
{
public:
	IO(int displayHeight, int displayWidth, int pixelSize = 12);
	~IO(void);

	void handleInputEvents();
	void clearScreen();

	bool isRunning() { return running; }
private:
	SDL_Window* window{ nullptr };
	SDL_Renderer* renderer{ nullptr };
	int pixelSize{ 8 };

	bool running{ true };
	SDL_Event inputEvent;
};
