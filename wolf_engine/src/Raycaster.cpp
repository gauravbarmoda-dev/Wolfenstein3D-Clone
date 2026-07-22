#include "../include/Raycaster.h"
#include "../include/Camera.h"
#include "../include/Map.h"
#include "../include/Renderer.h"

Raycaster::Raycaster(int w, int h) : scrWidth(w), scrHeight(h) {
    zBuffer = new float[scrWidth];
}

Raycaster::~Raycaster(){
    delete[] zbuffer;
}

void Raycaster::Render(Camera* camera, Map* map, Renderer* renderer){
    
}
