#pragma once

#include <iostream>
#include "sdl/include/SDL2/SDL.h"
#include <vector>
#include <bitset>
#include <unordered_map>
#include <cassert>

enum class KeyState{
	up = 0,
	down = 1
};

template<uint32_t _displayHeight, uint32_t _displayWidth>
class IO
{
public:
	IO(int pixelSize = 12) : displayHeight{ _displayHeight }, displayWidth{ _displayWidth }, displayPixelSize{ pixelSize }, displayMemory{ *(new std::bitset<_displayHeight* _displayWidth>()) }
	{
		if (!displayInit(_displayHeight, _displayWidth, pixelSize)) {
			running = false;
		}
		/*
		uint8_t data[8] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
		displayLoadData(60, 28, data, 8);
		*/
	}

	~IO(void)
	{
        SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		window = nullptr;
		renderer = nullptr;
        SDL_Quit();
	}

	void pollInputEvents()
	{
		while(SDL_PollEvent(&inputEvent) != 0) {
			switch (inputEvent.type) {
				case SDL_QUIT:
					running = false;
					break;
				case SDL_KEYUP:
				case SDL_KEYDOWN: {
					auto key = keyMap.find(inputEvent.key.keysym.sym);
					if (key != keyMap.end()) {
						keys[key->second] = inputEvent.type == SDL_KEYUP ? KeyState::up : KeyState::down;
					}
				}
					break;
				default:
					break;
			}
		}
	}

	uint8_t waitForInputEvent()
	{
		if (SDL_WaitEvent(&inputEvent)) {
			auto key = keyMap.find(inputEvent.key.keysym.sym);
			if (inputEvent.type == SDL_KEYDOWN && key != keyMap.end()) {
				return key->second;
			}
			return waitForInputEvent();
		}
	}

	bool displayInit(int displayHeight, int displayWidth, int pixelSize)
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0) {

			std::cout << "Could not initialize SDL. SDL Error = " << SDL_GetError() << std::endl;
			return false;
		}
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
		bool collision = oldValue ^ value;
		displayMemory[wrapY(positionY) * displayWidth + wrapX(positionX)] = collision;

		return collision;
	}

	bool displayGetPixel(int positionX, int positionY)
	{
		return displayMemory[wrapY(positionY) * displayWidth + wrapX(positionX)];
	}

	bool displayLoadData(int positionX, int positionY, uint8_t* data, int size)
	{
		bool anyBitErased{ false };

		for (int byte = 0; byte < size; ++byte) {
			anyBitErased |= displayLoadByte(positionX, positionY + byte, data[byte]);
		}

		return anyBitErased; //returns true if any bit was erased
	}

	bool isRunning() { return running; }

	bool isKeyPressed(uint8_t key)
	{
		if (key > 0xF) {
			return false;
		}

		return keys[key] == KeyState::down;
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
		if (!renderer) {
			std::cout << "Invalid ptr to renderer" << std::endl;
			assert(false);
			return;
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
	}

	bool displayLoadByte(int positionX, int positionY, uint8_t data)
	{
		bool anyBitErased{ false };

		for (int bit = 7; bit >= 0; --bit) {
			bool value = data & (1 << bit);
			anyBitErased |= displaySetPixel(positionX + 7 - bit, positionY, value);
		}

		return anyBitErased; //returns true if any bit was erased from memory
	}

	int wrapX(int positionX) {return positionX % displayWidth; };
	int wrapY(int positionY) {return positionY % displayHeight; };
	std::unordered_map<SDL_Keycode, uint8_t> keyMap = {
		{SDLK_1, 0x0}, {SDLK_2, 0x1}, {SDLK_3, 0x2}, {SDLK_4, 0x3},
		{SDLK_q, 0x4}, {SDLK_w, 0x5}, {SDLK_e, 0x6}, {SDLK_r, 0x7},
		{SDLK_a, 0x8}, {SDLK_s, 0x9}, {SDLK_d, 0xA}, {SDLK_f, 0xB},
		{SDLK_z, 0xC}, {SDLK_x, 0xD}, {SDLK_c, 0xE}, {SDLK_v, 0xF} };

	KeyState keys[16] = { KeyState::down }; // all keys in 0 (KeyState.up) state

};


