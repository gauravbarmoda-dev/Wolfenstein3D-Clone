#ifndef ENEMY_H
#define ENEMY_H

class ENEMY {
public:
    int Id;
    int curWeapon;
    float x, y;
    float health;
    float hitbox;

    ENEMY(float startX, float startY, float startHealth, float h, int startWeapon) {
        x = startX;
        y = startY;
        health = startHealth;
        curWeapon = startWeapon;
        hitbox = h;
    }

    void Draw(PLAYER *player, float *zBuffer, SCREEN *screen);
};

#endif