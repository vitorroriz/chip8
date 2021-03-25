#pragma once

#include <iostream>
#include "sdl/include/SDL2/SDL.h"
#include <vector>
#include <bitset>

template<uint32_t _displayHeight, uint32_t _displayWidth>
class IO
{
public:
	IO(int pixelSize = 12) : displayHeight{ _displayHeight }, displayWidth{ _displayWidth }, displayPixelSize{ pixelSize }, displayMemory{ *(new std::bitset<_displayHeight* _displayWidth>()) }
	{
		displayInit(_displayHeight, _displayWidth, pixelSize);
		displaySetPixel(12, 0, true);
		displaySetPixel(12, 1, true);
		displaySetPixel(12, 2, true);
		displaySetPixel(12, 3, true);
		displaySetPixel(12, 4, true);
		displaySetPixel(12, 5, true);
		displaySetPixel(0, 0, true);
		displaySetPixel(1, 0, true);
		displaySetPixel(2, 0, true);
		displaySetPixel(3, 0, true);
		displaySetPixel(4, 0, true);
		displaySetPixel(63, 31, true);
	}

	~IO(void)
	{
        SDL_DestroyWindow(window);
        SDL_Quit();
	}

	void handleInputEvents()
	{
		while (SDL_PollEvent(&inputEvent) != 0) {
			std::cout << "User input event: " << inputEvent.type << std::endl;
			switch (inputEvent.type) {
				case SDL_QUIT:
					running = false;
					break;
				default:
					break;
			}
		}
	}

	bool displayInit(int displayHeight, int displayWidth, int pixelSize)
	{
		SDL_Init(SDL_INIT_VIDEO);
		window = SDL_CreateWindow("chip8 emulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, pixelSize * displayWidth, pixelSize * displayHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		if (window == nullptr) {
			std::cout << "Could not create SDL Window" << std::endl;
			return false;
		}

		//Get window surface
		auto screenSurface = SDL_GetWindowSurface(window);
		//Fill the surface white
		//SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
		//Update the surface
		SDL_UpdateWindowSurface(window);

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (!renderer) {
			std::cout << "Could not create SDL renderer" << std::endl;
			return false;
		}

		displayClear();

		//std::cout << "Display initialized" << std::endl;
		return true;
	}

	void displayClear()
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
	}
	
	void displayUpdate()
	{
		displayClear();
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);

		for (int heightIndex = 0; heightIndex < displayHeight; ++heightIndex) {
			for (int widthIndex = 0; widthIndex < displayWidth; ++widthIndex) {
				if (displayGetPixel(widthIndex, heightIndex)) {
					SDL_Rect virtualPixel = { widthIndex * displayPixelSize, heightIndex * displayPixelSize, displayPixelSize, displayPixelSize };
					SDL_RenderFillRect(renderer, &virtualPixel);
				}
			}
		}

		SDL_RenderPresent(renderer);
	}

	void displaySetPixel(int positionX, int positionY, bool value)
	{
		displayMemory[positionY * displayWidth + positionX] = value;
	}

	bool displayGetPixel(int positionX, int positionY)
	{
		return displayMemory[positionY * displayWidth + positionX];
	}

	bool isRunning() { return running; }
private:
	SDL_Window* window{ nullptr };
	SDL_Renderer* renderer{ nullptr };

	const int displayHeight{ 32 };
	const int displayWidth{ 64};
	int displayPixelSize{ 8 };
	std::bitset<_displayHeight * _displayWidth> &displayMemory;

	bool running{ true };
	SDL_Event inputEvent;

};

