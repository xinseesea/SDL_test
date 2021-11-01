#pragma once

#include <map>
#include <SDL.h>
#include <SDL_image.h>

enum class KeyPress : uint8_t {
    KEY_PRESS_DEFAULT,
    KEY_PRESS_UP,
    KEY_PRESS_DOWN,
    KEY_PRESS_LEFT,
    KEY_PRESS_RIGHT,
    KEY_PRESS_TOTAL,
};

class directionImage {
    SDL_Window* window = nullptr;
    SDL_Surface* screenSurface = nullptr;
    SDL_Surface* currentSurface = nullptr;

    std::map<KeyPress, SDL_Surface*> keyPressSurface;

    bool init();
    bool loadMedia();
    void close();
    SDL_Surface* loadSurface(std::string path);
};