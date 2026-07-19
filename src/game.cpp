#include "include.h"

int main(void){

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "DOOM");
    DisableCursor();
    SetTargetFPS(60);

    MAP2D   map2D;
    MAP3D   map3D;
    PLAYER  player  (22.5f, 22.5f, 0.0f, 0.1f, 0.1f, 0.1f, 0);
    ENEMY   enemy   (20.5f, 20.5f, 100.0f, 0.2f, 1);
    SCREEN  screen  (SCREEN_WIDTH, SCREEN_HEIGHT);

    InitWeapons();
    LoadGameSprites();
    
    while(!WindowShouldClose()){
        
        player.Update(&map2D);

        player.Shoot(&map2D);

        screen.Clear();

        BeginDrawing();

            ClearBackground(BLACK);

            map3D.Draw(&map2D, &player, &screen);

            enemy.Draw(&player, map3D.zBuffer, &screen);

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

