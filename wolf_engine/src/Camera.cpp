#include "../include/Camera.h"
#include "../include/Map.h"
#include <iostream>
#include <cmath>

Camera::Camera() : pos(3.5f, 3.5f), dir(1.0f, 0.0f), plane(0.0f, 0.66f) {}

Camera::Camera(Vector2 startPos, Vector2 startDir, float fov) {
    pos = startPos;
    dir = startDir;
    plane = dir.Normal() * fov;
}

void Camera::Rotate(float angleRadius){
    dir = dir.Rotate(angleRadius);
    plane = plane.Rotate(angleRadius);
}

void Camera::MoveForward(float distance, Map* map){
    Vector2 newPos = pos + (dir * distance);
    if(map->GetWorldTile(newPos.x, pos.y) == 0) pos.x = newPos.x;
    if(map->GetWorldTile(pos.x, newPos.y) == 0) pos.y = newPos.y;
}
