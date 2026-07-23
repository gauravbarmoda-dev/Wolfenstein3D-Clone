#include "../include/Input.h"
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_events.h>

Input::Input(){
    sdlKey = SDL_GetKeyboardState(&numKey);
    if(sdlKey != nullptr){
        previousKeyState.resize(numKey, 0);
    }
}

void Input::Update(){
    if(sdlKey != nullptr){
        previousKeyState.assign(sdlKey, sdlKey + numKey);
    }
    SDL_PumpEvents();
}

static SDL_Scancode GetSDLScanCode(Keys key){
    switch (key){
        case Keys::W : return SDL_SCANCODE_W;
        case Keys::A : return SDL_SCANCODE_A;
        case Keys::S : return SDL_SCANCODE_S;
        case Keys::D : return SDL_SCANCODE_D;
        case Keys::E : return SDL_SCANCODE_E;        
        case Keys::Q : return SDL_SCANCODE_Q;        

        default :     return SDL_SCANCODE_UNKNOWN;
    }
}

bool Input::isKeyDown(Keys key){
    SDL_Scancode keyCode = GetSDLScanCode(key);
    if(keyCode == SDL_SCANCODE_UNKNOWN || sdlKey == nullptr) return false;

    return sdlKey[keyCode];
}

bool Input::isKeyPressed(Keys key){
    SDL_Scancode keyCode = GetSDLScanCode(key);
    if(keyCode == SDL_SCANCODE_UNKNOWN || sdlKey == nullptr) return false;

    bool isDown  = sdlKey[keyCode] != 0;
    bool wasDown = previousKeyState[keyCode] != 0;

    return isDown && !wasDown;
}
