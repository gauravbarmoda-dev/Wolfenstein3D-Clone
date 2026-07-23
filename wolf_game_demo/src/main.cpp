#include "../../wolf_engine/include/Engine.h"
#include "../../wolf_engine/include/Renderer.h"
#include "../../wolf_engine/include/Raycaster.h"
#include "../../wolf_engine/include/Camera.h"
#include "../../wolf_engine/include/Map.h"
#include <cstdint>
#include <iostream>
#include <SDL2/SDL.h>

#define SCREEN_HEIGHT   480
#define SCREEN_WIDTH    640

const uint32_t GRAY  = 0xFF444444;
const uint32_t BROWN = 0xFF553311;
const uint32_t RED   = 0xFFFF0000;

void HandleInput(Engine& engine, Camera& camera, Map& map){
    float mvSpeed  = 3.0f * engine.GetDeltaTime();
    float rotSpeed = 2.0f * engine.GetDeltaTime();

    auto& input = engine.GetInput();

    if(input.isKeyDown(Keys::W)) camera.Move(mvSpeed, &map); 
    if(input.isKeyDown(Keys::S)) camera.Move(-mvSpeed, &map);    
    if(input.isKeyDown(Keys::A)) camera.Strafe(-mvSpeed, &map);    
    if(input.isKeyDown(Keys::D)) camera.Strafe(mvSpeed, &map);

    if(input.isKeyDown(Keys::Q)) camera.Rotate(-rotSpeed);    
    if(input.isKeyDown(Keys::E)) camera.Rotate(rotSpeed);    
}

int main(){
    Raycaster raycaster(SCREEN_WIDTH, SCREEN_HEIGHT);
    Renderer  renderer;
    Camera    camera;
    Engine    engine;
    Map       map;

    engine.Initialize(SCREEN_WIDTH, SCREEN_HEIGHT, "Test");
    renderer.Initialize(engine.GetRenderer(), SCREEN_WIDTH, SCREEN_HEIGHT);
    
    while(engine.IsRunning()){
        engine.Update();

        HandleInput(engine, camera, map);

        renderer.ClearHorizon(GRAY, BROWN);

        raycaster.Render(&camera, &map, &renderer);

        renderer.Present(engine.GetRenderer());
    }

    return 0;
}
