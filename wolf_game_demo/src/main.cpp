#include "../../wolf_engine/include/Engine.h"
#include "../../wolf_engine/include/Renderer.h"
#include <cstdint>

#define SCREEN_HEIGHT   480
#define SCREEN_WIDTH    640

const uint32_t GRAY  = 0xFF444444;
const uint32_t BROWN = 0xFF553311;
const uint32_t RED   = 0xFFFF0000;

int main(){
    Engine   engine;
    Renderer renderer;

    engine.Initialize(SCREEN_WIDTH, SCREEN_HEIGHT, "Test");
    renderer.Initialize(engine.GetRenderer(), SCREEN_WIDTH, SCREEN_HEIGHT);

    while(engine.IsRunning()){
        engine.Update();
        
        renderer.ClearHorizon(GRAY, BROWN);

        renderer.DrawRectangle(100, 100, 200, 100, 0, RED);

        renderer.Present(engine.GetRenderer());
    }

    renderer.CleanUp();

    return 0;
}

