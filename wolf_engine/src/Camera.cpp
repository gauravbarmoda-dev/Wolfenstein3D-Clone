#include "Camera.h"
#include "Map.h"
#include <iostream>
#include <cmath>

Camera::Camera() : pos(1.5f, 1.5f), dir(1.0f, 0.0f), plane(0.0f, 0.66f) {}

Camera::Camera(Vector2 startPos, Vector2 startDir, float fov) {
    pos = startPos;
    dir = startDir;
    plane = dir.Normal() * fov;
}

void Camera::Rotate(float angleRadius){
    dir = dir.Rotate(angleRadius);
    plane = plane.Rotate(angleRadius);
}

void Camera::Move(float distance, Map* map){
    Vector2 newPos = pos + (dir * distance);
    if(map->GetWorldTile(newPos.x, pos.y) == 0) pos.x = newPos.x;
    if(map->GetWorldTile(pos.x, newPos.y) == 0) pos.y = newPos.y;
}

void Camera::Strafe(float distance, Map* map){
    float newX = pos.x + (-dir.y * distance);
    float newY = pos.y + (dir.x * distance);
    
    if(map->GetWorldTile(newX, pos.y) == 0) pos.x = newX;
    if(map->GetWorldTile(pos.x, newY) == 0) pos.y = newY;
}
