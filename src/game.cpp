#include "include.h"

int main(void){

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "DOOM");
    DisableCursor();
    SetTargetFPS(60);

    MAP2D   map2D;
    MAP3D   map3D;
    PLAYER  player;
    SCREEN screen(SCREEN_WIDTH, SCREEN_HEIGHT);

    LoadGameSprites();
    
    while(!WindowShouldClose()){
        
        player.Update(&map2D);

        screen.Clear();

        BeginDrawing();

            ClearBackground(BLACK);

            map3D.Draw(&map2D, &player, &screen);

            screen.Draw();

            player.Draw();

            player.CheckIntersection(&map2D);

            DrawFPS(1, 1);

        EndDrawing();
    }

    UnloadGameSprites();
    CloseWindow();
    return 0;
}

