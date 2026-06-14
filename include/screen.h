#ifndef SCREEN_H
#define SCREEN_H

#include <vector>
#include "raylib.h"

class SCREEN{
public:
    std::vector<Color> pixels;
    Texture2D texture;
    
    int width, height;

    SCREEN(int w, int h);
    ~SCREEN();

    void Clear();

    void Draw();
};
                                                                                            
#endif