#ifndef MAP2D_H
#define MAP2D_H

#include <vector>

#define BLOCK_SIZE  50

#define EMPTY       0
#define BROWN_WALL  1
#define BLUE_WALL   2
#define GREEN_WALL  3
#define RED_WALL    4
#define PINK_WALL   5
#define YELLOW_WALL 6
#define CYAN_WALL   7
#define LIME_WALL   8                                                                                                                    

class MAP2D{
public:
    int mapWidth;
    int mapHeight;
    std::vector<unsigned char> mapData;

    MAP2D();

    char GetTile(int x, int y);
};                                                                                                                                      
    
#endif
