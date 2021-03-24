#include "io.h"

IO::IO(int displayHeight, int displayWidth, int pixelSize)
{
    initDisplay(displayHeight, displayWidth, pixelSize);
}

void IO::updateDisplay()
{
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

bool IO::initDisplay(int displayHeight, int displayWidth, int pixelSize)
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
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
	//Update the surface
	SDL_UpdateWindowSurface(window);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		std::cout << "Could not create SDL renderer" << std::endl;
		return false;
	}
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	std::cout << "Display initialized" << std::endl;
	return true;
}

IO::~IO(void)
{
        //Destroy window
        SDL_DestroyWindow(window);
        //Quit SDL subsystems
        SDL_Quit();
}

void IO::clearScreen()
{
    //todo: integrate window clear from sdl
}

void IO::handleInputEvents()
{
    while (SDL_PollEvent(&inputEvent) != 0) {
		std::cout << "Input event: " << inputEvent.type << std::endl;
        switch (inputEvent.type) {
			case SDL_QUIT:
                running = false;
                break;
            default:
                break;
        }
    }
}

