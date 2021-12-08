#include "directionImage.h"
#include <iostream>

static const int num = 5;
const std::array<KeyPress, num> allKeyPress = {KeyPress::KEY_PRESS_DEFAULT, KeyPress::KEY_PRESS_UP, KeyPress::KEY_PRESS_DOWN, KeyPress::KEY_PRESS_LEFT, KeyPress::KEY_PRESS_RIGHT};
const std::map<KeyPress, std::string> imgFiles = {{KeyPress::KEY_PRESS_DEFAULT, "img/marriage.png"}, {KeyPress::KEY_PRESS_UP, "img/upper.png"}, {KeyPress::KEY_PRESS_DOWN, "img/lower.png"}, {KeyPress::KEY_PRESS_LEFT, "img/left.png"}, {KeyPress::KEY_PRESS_RIGHT, "img/right.png"}};

bool DirectionImage::init() {
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

SDL_Surface* DirectionImage::loadSurface(const std::string& imgFile) {
    SDL_Surface* surface = IMG_Load(imgFile.c_str());
    if (!surface) {
        std::cout << "Unable to load image: " << imgFile
                  << " Image Error: " << IMG_GetError() << std::endl;
    }
    return surface;
}

bool DirectionImage::loadMedia() {
    bool success = true;

    for (const KeyPress& key : allKeyPress) {
        keyPressSurface[key] = loadSurface(imgFiles.at(key));
        if (!keyPressSurface[key]) {
            std::cout << "Failed to load image: " << imgFiles.at(key) << std::endl;
            success = false;
        }
    }

    return success;
}

void DirectionImage::close() {
    for (auto& keySufacePair : keyPressSurface) {
        SDL_FreeSurface(keySufacePair.second);
        keySufacePair.second = nullptr;
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    window = nullptr;
}

bool DirectionImage::run() {
    if (!init()) {
        std::cout << "Init failed" << std::endl;
        return false;
    }

    if (!loadMedia()) {
        std::cout << "Load Media failed" << std::endl;
        return false;
    }

    currentSurface = keyPressSurface[KeyPress::KEY_PRESS_DEFAULT];
    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        currentSurface = keyPressSurface[KeyPress::KEY_PRESS_UP];
                        break;
                    case SDLK_DOWN:
                        currentSurface = keyPressSurface[KeyPress::KEY_PRESS_DOWN];
                        break;
                    case SDLK_LEFT:
                        currentSurface = keyPressSurface[KeyPress::KEY_PRESS_LEFT];
                        break;
                    case SDLK_RIGHT:
                        currentSurface = keyPressSurface[KeyPress::KEY_PRESS_RIGHT];
                        break;
                    default:
                        currentSurface = keyPressSurface[KeyPress::KEY_PRESS_DEFAULT];
                        break;
                }
            }
        }

        SDL_SetWindowSize(window, currentSurface->w, currentSurface->h);
        screenSurface = SDL_GetWindowSurface(window);
        SDL_BlitSurface(currentSurface, NULL, screenSurface, NULL);
        SDL_UpdateWindowSurface(window);
    }

    return true;
}