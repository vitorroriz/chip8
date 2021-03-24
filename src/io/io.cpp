#include "io.h"

IO::IO(int displayHeight, int displayWidth, int pixelSize)
{
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("chip8 emulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, pixelSize * displayWidth, pixelSize * displayHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		return;
	}
	else {
        //Get window surface
        auto screenSurface = SDL_GetWindowSurface(window);

        //Fill the surface white
        SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

        //Update the surface
        SDL_UpdateWindowSurface(window);

        //Wait two seconds
        SDL_Delay(10000);

        //Destroy window
        SDL_DestroyWindow(window);

        //Quit SDL subsystems
        SDL_Quit();
	}
}

IO::~IO(void)
{
}

void IO::clearScreen()
{
    //todo: integrate window clear from sdl
}

void IO::handleInputEvents()
{
    while (SDL_PollEvent(&inputEvent) != 0) {
        switch (inputEvent.type) {
            std::cout << "Input event: " << inputEvent.type << std::endl;
			case SDL_QUIT:
                running = false;
                break;
            default:
                break;
        }
    }
}

