#ifndef ENGINE_H
#define ENGINE_H

#include "Input.h"

struct SDL_Window;
struct SDL_Renderer;

class Engine{
private:
    SDL_Window*   window;
    SDL_Renderer* renderer;

    Input input;

    bool isRunning;

    unsigned int lastFrameTime;
    float deltaTime;

public:
    Engine();
    ~Engine();

    bool Initialize(int width, int height, const char* title);
    void Update();
    void Quit();
};
#endif
