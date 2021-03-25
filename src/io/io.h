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
		uint8_t data[8] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
		displayLoadData(60, 28, data, 8);
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
		auto screenSurface = SDL_GetWindowSurface(window);
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

	void displayClearMemory()
	{
		displayMemory.reset();
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

	bool displaySetPixel(int positionX, int positionY, bool value)
	{
		bool oldValue = displayGetPixel(positionX, positionY);
		displayMemory[wrapY(positionY) * displayWidth + wrapX(positionX)] = value;

		return !value && oldValue; //returns true if bit was erased
	}

	bool displayGetPixel(int positionX, int positionY)
	{
		return displayMemory[wrapY(positionY) * displayWidth + wrapX(positionX)];
	}

	bool isRunning() { return running; }

	bool displayLoadData(int positionX, int positionY, uint8_t* data, int size)
	{
		bool anyBitErased{ false };

		for (int byte = 0; byte < size; ++byte) {
			anyBitErased |= displayLoadByte(positionX, positionY + byte, data[byte]);
		}

		return anyBitErased; //returns true if any bit was erased
	}

private:
	SDL_Window* window{ nullptr };
	SDL_Renderer* renderer{ nullptr };

	const int displayHeight{ 32 };
	const int displayWidth{ 64};
	int displayPixelSize{ 8 };
	std::bitset<_displayHeight * _displayWidth> &displayMemory;

	bool running{ true };
	SDL_Event inputEvent;

	void displayClear()
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
	}

	bool displayLoadByte(int positionX, int positionY, uint8_t data)
	{
		bool anyBitErased{ false };

		for (int bit = 0; bit < 8; ++bit) {
			bool value = data & (1 << bit);
			anyBitErased |= displaySetPixel(wrapX(positionX + bit), wrapY(positionY), value);
		}

		return anyBitErased; //returns true if any bit was erased from memory
	}

	int wrapX(int positionX) {return positionX % displayWidth; };
	int wrapY(int positionY) {return positionY % displayHeight; };
};

