#ifndef SPRITE_H
#define SPRITE_H

#include "raylib.h"

#define NO_OF_SPRITES 13

extern Image Textures[NO_OF_SPRITES];

void LoadGameSprites();

void UnloadGameSprites();

#endif