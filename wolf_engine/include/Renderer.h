#ifndef RENDERER_H
#define RENDERER_H

#include <cstdint>

struct SDL_Renderer;
struct SDL_Texture;

class Renderer{
private:
    int width;
    int height;

    SDL_Texture* texture;
    uint32_t* pixels;

public:
    Renderer();
    ~Renderer();

    bool Initialize(SDL_Renderer* renderer, int scrWidth, int scrHeight);

    void CleanUp();

    void Clear(uint32_t color);
    void ClearHorizon(uint32_t ceil, uint32_t floor);

    void DrawPixel(int x, int y, uint32_t color);
    void DrawVLine(int x, int startY, int endY, uint32_t color);
    void DrawTexturedVLine(int x, int startY, int endY, int texID, int texX);

    void Present(SDL_Renderer* renderer);

    int GetWidth()  {return width;}
    int GetHeight() {return height;}
};

#endif
