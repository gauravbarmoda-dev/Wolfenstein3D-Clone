#ifndef WEAPONS_H
#define WEAPONS_H

#define NO_OF_WEAPONS   5 

class WEAPON {
public:
    int range, damage, fireRate, reloadSpeed, magSize, weaponScope;
    bool isScope;

    WEAPON() {}

    WEAPON(int r, int d, int fr, int rs, int ms, int ws, bool sc) {
        range = r;
        damage = d;
        fireRate = fr;
        reloadSpeed = rs;
        magSize = ms;
        weaponScope = ws;
        isScope = sc;
    }
};

extern WEAPON globalWeapons[NO_OF_WEAPONS];

void InitWeapons();

#endif