#ifndef MAP_H
#define MAP_H

#include <vector>

class Map{
private:
    int mapHeight;
    int mapWidth;
    std::vector <unsigned char> mapData;

public:    
    Map();
    ~Map();

    char GetTile(int x, int y);
    
    void SetTile(int x, int y, char tileID);

    char GetWorldTile(float x, float y);

    int GetWidth()  const {return mapWidth;}
    
    int GetHeight() const {return mapHeight;}
};

#endif
