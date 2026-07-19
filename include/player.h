#ifndef PLAYER_H
#define PLAYER_H

#define MOUSE_SENS 0.002f
#define PLAYER_FOV 1.047f

class MAP2D;

class PLAYER{
public:
    Vector2 p;  
    int curWeapon;
    float angle;
    float rotationSpeed; 
    float movementSpeed;
    float hitbox;

    PLAYER(float x, float y, float a, float rs, float ms, float hb, int cw);

    void Update(MAP2D *map);

    void Draw();

    void CheckIntersection(MAP2D *map);

    void Shoot(MAP2D *map);
};

#endif
