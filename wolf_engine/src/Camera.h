#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>

class Map;

struct Vector2 {
    float x, y;

    Vector2() : x(0.0f), y(0.0f) {}
    Vector2(float a, float b) : x(a), y(b) {}

    Vector2 operator+(Vector2 other) {
        return Vector2(x + other.x, y + other.y);
    }
    Vector2 operator-(Vector2 other) {
        return Vector2(x - other.x, y - other.y);
    }
    Vector2 operator*(float scaler) {
        return Vector2(x * scaler, y * scaler);
    }
    Vector2 operator/(float scaler) {
        return (scaler != 0.0f) ? Vector2(x / scaler, y / scaler) : Vector2(0.0f, 0.0f);
    }

    float Dot(Vector2 other) {
        return x * other.x + y * other.y;
    }
    Vector2 Normal() {
        return Vector2(-y, x);
    }
    Vector2 Rotate(float angleRadius) {
        float Rx = x * cosf(angleRadius) - y * sinf(angleRadius);
        float Ry = x * sinf(angleRadius) + y * cosf(angleRadius);
        return Vector2(Rx, Ry);
    }
};

class Camera{
public:
    Vector2 pos;
    Vector2 dir;
    Vector2 plane;

    Camera();
    Camera(Vector2 startPos, Vector2 startDir, float fov = 0.66f);
    ~Camera() = default;

    void Rotate         (float angleRadius);
    void Move           (float distance, Map* map);
    void Strafe         (float distance, Map* map);
}; 

#endif
