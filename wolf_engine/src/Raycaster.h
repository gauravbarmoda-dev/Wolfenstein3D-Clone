#ifndef RAYCASTER_H
#define RAYCASTER_H

#include <vector>

class Camera;
class Rasterizer;
class Map;

class Raycaster{
private:
    int scrWidth;
    int scrHeight;

    float* zBuffer;

public:
    Raycaster(int w, int h);
    ~Raycaster();

    void Render(Camera *camera, Map* map, Rasterizer* rasterizer);
};

#endif
