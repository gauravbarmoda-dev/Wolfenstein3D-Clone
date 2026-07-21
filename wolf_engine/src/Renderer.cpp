#include "../include/Renderer.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <iostream>

Renderer::Renderer() : width(0), height(0), texture(nullptr), pixels(nullptr) {}

Renderer::~Renderer(){}

bool Renderer::Initialize(SDL_Renderer* renderer, int scrWidth, int scrHeight){
    width  = scrWidth;
    height = scrHeight;

    pixels = new uint32_t[width * height];

    texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        width, height
    );

    if(!texture){
        std::cerr << "Failed to create Texture: " << SDL_GetError() << "\n";
        return false;
    }

    return true;
}

void Renderer::CleanUp(){
    if(pixels != nullptr){
        delete[] pixels;
        pixels = nullptr;
    }
    if(texture != nullptr){
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
    return;
}

void Renderer::Clear(uint32_t color){
    int size = width * height;
    for(int i = 0; i < size; i++){
        pixels[i] = color;
    }
    return;
}

void Renderer::ClearHorizon(uint32_t ceil, uint32_t floor){
    int totalPixels = width & height;
    int halfPixels  = totalPixels >> 1;

    for(int i = 0; i < halfPixels; i++){
        pixels[i] = ceil;
    }
    
    for(int i = halfPixels; i < totalPixels; i++){
        pixels[i] = floor;
    }
}

void Renderer::DrawPixel(int x, int y, uint32_t color){
    if(x >= 0 && x < width && y >= 0 && y < height){
        pixels[y * width + x] = color;
    }
}

void Renderer::DrawVLine(int x, int startY, int endY, uint32_t color){
    if(x < 0 || x >= width) return ;
    if(startY < 0) startY = 0;
    if(endY >= height) endY = height;

    int pixIndex = startY * width + x;
    for(int y = startY; y < endY; y++){
        pixels[pixIndex] = color;
        pixIndex += width;
    } 
}
void Renderer::DrawTexturedVLine(int x, int startY, int endY, int texID, int texX){
    return ;    
}

void Renderer::Present(SDL_Renderer* renderer){
    SDL_UpdateTexture(texture, nullptr, pixels, width * sizeof(uint32_t));
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}
