#include "screen.h"
#include <cstring>

SCREEN::SCREEN(int w, int h){
    width  = w;
    height = h;
    pixels.resize(w * h);

    Image blankImage = GenImageColor(w, h, BLANK);
    texture = LoadTextureFromImage(blankImage);
    UnloadImage(blankImage);
}

SCREEN::~SCREEN(){
    UnloadTexture(texture);
}

void SCREEN::Clear(){
    memset(pixels.data(), 0, width * height * sizeof(Color));
}

void SCREEN::Draw(){
    UpdateTexture(texture, pixels.data());
    DrawTexture(texture, 0, 0, WHITE);
}