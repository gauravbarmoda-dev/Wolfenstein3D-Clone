#include "include.h"

WEAPON globalWeapons[NO_OF_WEAPONS];

void InitWeapons() {
    // Pistol
    globalWeapons[0] = WEAPON(8, 20, 50, 80, 15, 2, false);
    
    // AR
    globalWeapons[1] = WEAPON(8, 30, 30, 100, 40, 4, false);
    
    // Shotgun
    globalWeapons[2] = WEAPON(3, 50, 90, 220, 5, 2, false);
    
    // SMG
    globalWeapons[3] = WEAPON(6, 10, 20, 60, 25, 2, false);
    
    // Sniper
    globalWeapons[4] = WEAPON(12, 50, 90, 320, 5, 8, true);
}
