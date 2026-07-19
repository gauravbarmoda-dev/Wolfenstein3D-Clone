#ifndef MAP3D_H
#define MAP3D_H

#define SCREEN_WIDTH    1920
#define SCREEN_HEIGHT   1080
#define PLAYER_FOV      1.047f

class MAP3D {
private:
    float fisheyeLUT[SCREEN_WIDTH];
    bool lutInit = false;

    void InitLUT();
    void RenderWall(int x, float distance, bool NorthWall, char tile, float wallX, Vector2 rayDir, SCREEN* screen);
    void RenderFloor(int x, int botOfWall, float fisheyeFix, Vector2 rayDir, PLAYER* player, SCREEN* screen);

public:
    float zBuffer[SCREEN_WIDTH];

    void Draw(MAP2D* map, PLAYER* player, SCREEN* screen);
};
  
#endif