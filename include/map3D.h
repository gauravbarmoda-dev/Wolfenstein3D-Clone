#ifndef MAP3D_H
#define MAP3D_H

#define SCREEN_WIDTH    1920
#define SCREEN_HEIGHT   1080
#define PLAYER_FOV      1.047f

class MAP3D {
private:
    float fisheyeLUT[SCREEN_WIDTH];
    bool lutInit = false;
public:
    void Draw(MAP2D* map, PLAYER* player, SCREEN* screen);
};
  
#endif