#ifndef RAYCASTER_H
#define RAYCASTER_H

#include <vector>

class Camera;
class Renderer;
class Map;

class Raycaster{
private:
    int scrWidth;
    int scrHeight;

    float* zBuffer;

public:
    Raycaster();
    ~Raycaster();

    void Render(Camera *camera, Map* map, Renderer* renderer);
};

#endif
