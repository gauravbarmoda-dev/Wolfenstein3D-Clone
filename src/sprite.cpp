#include "include.h"

Image Textures[NO_OF_SPRITES];

const char* texturePath[NO_OF_SPRITES] = {
    "Sprites/red_wall.png",
    "Sprites/blue_wall.png",
    "Sprites/green_wall.png",
    "Sprites/brown_wall.png",
    "Sprites/cyan_wall.png",
    "Sprites/pink_wall.png",
    "Sprites/yellow_wall.png",
    "Sprites/lime_wall.png",
    "Sprites/floor.png",
    "Sprites/ceiling.png",
    "Sprites/enemy1.png",
    "Sprites/enemy2.png",
    "Sprites/enemy3.png"
};

void LoadGameSprites(){
    for(int i = 0; i < NO_OF_SPRITES; i++){
        Textures[i] = (LoadImage(texturePath[i]));
        ImageFormat(&Textures[i], PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    }
}

void UnloadGameSprites(){
    for(int i = 0; i < NO_OF_SPRITES; i++){
        UnloadImage(Textures[i]);
    }
}

