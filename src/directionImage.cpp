#include "directionImage.h"
#include <iostream>

static const int num = 6;
const std::array<KeyPress, num> allKeyPress = {KeyPress::KEY_PRESS_DEFAULT, KeyPress::KEY_PRESS_UP, KeyPress::KEY_PRESS_DOWN, KeyPress::KEY_PRESS_LEFT, KeyPress::KEY_PRESS_RIGHT, KeyPress::KEY_PRESS_TOTAL};
const std::map<KeyPress, std::string> imgFiles = {{KeyPress::KEY_PRESS_DEFAULT, "img/marriage.png"}, {KeyPress::KEY_PRESS_UP, "img/upper.png"}, {KeyPress::KEY_PRESS_DOWN, "img/lower.png"}, {KeyPress::KEY_PRESS_LEFT, "img/left.png"}, {KeyPress::KEY_PRESS_RIGHT, "right.png"}};

bool directionImage::init() {
    bool success = true;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < -1) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        success = false;
    } else {
        window = SDL_CreateWindow("Pictures", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_SHOWN);
        if (!window) {
            std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            success = false;
        }
    }

    return success;
}

SDL_Surface* directionImage::loadSurface(const std::string& imgFile) {
    SDL_Surface* surface = IMG_Load(imgFile.c_str());
    if (!surface) {
        std::cout << "Unable to load image: " << imgFile
                  << " Image Error: " << IMG_GetError() << std::endl;
    }
    return surface;
}

bool directionImage::loadMedia() {
    bool success = true;

    for (const KeyPress& key : allKeyPress) {
        keyPressSurface[key] = loadSurface(imgFiles.at(key));
        if (!keyPressSurface[key]) {
            std::cout << "Failed to load image: " << imgFiles.at(key) << std::endl;
        }
        success = false;
    }

    return success;
}

void directionImage::close() {
    for (auto& keySufacePair : keyPressSurface) {
        SDL_FreeSurface(keySufacePair.second);
        keySufacePair.second = nullptr;
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    window = nullptr;
}