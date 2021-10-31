#include <iostream>
#include "showImage.h"

bool ShowImage::init() {
	bool success = true;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < -1) {
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		success = false;
	} else {
        gWindow = SDL_CreateWindow("Fighter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_SHOWN);
        if (!gWindow) {
            std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            success = false;
        }
	}
    return success;
}

bool ShowImage::loadMedia() {
    bool success = true;

    gHellowWorld = IMG_Load(imageFile.c_str());
    if (!gHellowWorld) {
        std::cout << "Unable to load image " << imageFile << std::endl
                  << "IMG_error: " << IMG_GetError() << std::endl;
        success = false;
    }
    return success;
}

void ShowImage::close() {
    SDL_FreeSurface(gHellowWorld);
    SDL_DestroyWindow(gWindow);

    gHellowWorld = nullptr;
    gWindow = nullptr;

    SDL_Quit();
}

void ShowImage::loadImage() {
    if (!init()) {
        std::cout << "Failed to init" << std::endl;
    } else {
        if (!loadMedia()) {
            std::cout << "Failed to load media" << std::endl;
        }
        else
        {
            int w = gHellowWorld->w;
            int h = gHellowWorld->h;
            SDL_SetWindowSize(gWindow, w, h);
            gScreenSurface = SDL_GetWindowSurface(gWindow);

            bool isRunning = true;
            SDL_Event event;
            while (isRunning) {
                while (SDL_PollEvent(&event))
                {
                    switch (event.type)
                    {
                    case SDL_QUIT:
                        isRunning = false;
                        break;
                    case SDL_KEYDOWN:
                        if (event.key.keysym.sym == SDLK_ESCAPE)
                        {
                            isRunning = false;
                        }
                        break;
                    }
                }
                SDL_BlitSurface(gHellowWorld, NULL, gScreenSurface, NULL);
                SDL_UpdateWindowSurface(gWindow);
            }
        }
    }

    close();
}