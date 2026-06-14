#include "include.h"

PLAYER::PLAYER(){
    p.x = 22.5f;
    p.y = 22.5f;
    angle = 0.0f;
    rotationSpeed = 0.03f;
    movementSpeed = 0.03f;
    hitbox = 0.1f;
}

void PLAYER::Update(MAP2D *map){

    angle += GetMouseDelta().x * MOUSE_SENS;

    float nextX = p.x;
    float nextY = p.y;
    float nextMvSpd = movementSpeed;

    if(IsKeyDown(KEY_LEFT_SHIFT)){
        nextMvSpd += 0.03;
    }

    if(IsKeyDown(KEY_W)){
        nextX += cos(angle) * nextMvSpd;
        nextY += sin(angle) * nextMvSpd;
    }

    if(IsKeyDown(KEY_S)){
        nextX -= cos(angle) * nextMvSpd;
        nextY -= sin(angle) * nextMvSpd;
    }
    
    if(IsKeyDown(KEY_A)){
        nextX += cos(angle - (PI / 2.0f)) * nextMvSpd;
        nextY += sin(angle - (PI / 2.0f)) * nextMvSpd;
    }

    if(IsKeyDown(KEY_D)){
        nextX += cos(angle + (PI / 2.0f)) * nextMvSpd;
        nextY += sin(angle + (PI / 2.0f)) * nextMvSpd;
    }

    float checkX = (nextX > p.x) ? (nextX + hitbox) : (nextX - hitbox);
    if(map->GetTile((int)checkX, (int)(p.y - hitbox)) == EMPTY && 
       map->GetTile((int)checkX, (int)(p.y + hitbox)) == EMPTY) {
        p.x = nextX;
    }
  
    float checkY = (nextY > p.y) ? (nextY + hitbox) : (nextY - hitbox);
    if(map->GetTile((int)(p.x - hitbox), (int)checkY) == EMPTY && 
       map->GetTile((int)(p.x + hitbox), (int)checkY) == EMPTY) {
        p.y = nextY;
    }
}

void PLAYER::Draw(){
    DrawCircle(SCREEN_WIDTH / 2, SCREEN_HEIGHT /2, 3, YELLOW);
}

void PLAYER::CheckIntersection(MAP2D *map){
    float intersectionDistance = 0.9f;    
    int targetX = (int)(p.x + cos(angle) * intersectionDistance);
    int targetY = (int)(p.y + sin(angle) * intersectionDistance);

    if(map->GetTile(targetX, targetY) == BROWN_WALL){
        DrawText("Interact", (SCREEN_WIDTH / 2) - 25, (SCREEN_HEIGHT / 2) - 25, 16, LIME);

        if(IsKeyPressed(KEY_E)) map->mapData[(targetY * map->mapWidth) + targetX] = EMPTY;
    }
}   
