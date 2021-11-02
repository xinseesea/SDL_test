#pragma once

#include <string>
#include <SDL.h>
#include <SDL_image.h>

class ShowImage
{
    std::string imageFile;
    SDL_Window *gWindow = nullptr;
    SDL_Surface *gScreenSurface = nullptr;
    SDL_Surface *gHellowWorld = nullptr;

    bool init();
    bool loadMedia();
    void close();

public:
    ShowImage(std::string file = "") : imageFile(file) {};
    bool run();
};