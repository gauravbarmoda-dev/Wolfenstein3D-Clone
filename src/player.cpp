#include "include.h"

class WEAPON;

PLAYER::PLAYER(float x, float y, float a, float rs, float ms, float hb, int cw){
    p.x = x;
    p.y = y;
    angle = a;
    rotationSpeed = rs;
    movementSpeed = ms;
    hitbox = hb;
    curWeapon = cw;
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
    if(map->GetTile((int)std::floor(checkX), (int)std::floor(p.y - hitbox)) == EMPTY && 
       map->GetTile((int)std::floor(checkX), (int)std::floor(p.y + hitbox)) == EMPTY) {
        p.x = nextX;
    }
  
    float checkY = (nextY > p.y) ? (nextY + hitbox) : (nextY - hitbox);
    if(map->GetTile((int)std::floor(p.x - hitbox), (int)std::floor(checkY)) == EMPTY && 
       map->GetTile((int)std::floor(p.x + hitbox), (int)std::floor(checkY)) == EMPTY) {
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

        if(IsKeyPressed(KEY_E)){
            if(targetX > 0 || targetX <= map->mapWidth || targetY > 0 || targetY <= map->mapHeight){
                map->mapData[(targetY * map->mapWidth) + targetX] = EMPTY;
            }
        }    
    }
}

void PLAYER::Shoot(MAP2D *map){
    int   maxDistance   = globalWeapons[curWeapon].range;
    float deltaDistance = 0.4f;

    if(IsKeyPressed(KEY_Q)){
        (curWeapon == NO_OF_WEAPONS - 1) ? (curWeapon = 0) : (curWeapon++);
    }

    if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
        float currDistance = hitbox;

        while(currDistance < maxDistance){
            int targetX = (int)(p.x + cos(angle) * currDistance);
            int targetY = (int)(p.y + sin(angle) * currDistance);

            if(targetX <= 0 || targetX >= map->mapWidth - 1 || targetY <= 0 || targetY >= map->mapHeight - 1) return;

            if(map->GetTile(targetX, targetY) != EMPTY){
                // bullet hit logic...
                map->mapData[(targetY * map->mapWidth) + targetX] = EMPTY;
                break;
            }
            currDistance += deltaDistance;
        }
    }
}
