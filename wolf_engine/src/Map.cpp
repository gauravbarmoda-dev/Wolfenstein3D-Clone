#include "Map.h"
#include <cmath>
#include <iostream>
#include <fstream>

Map::Map(){
    std::ifstream in("wolf_engine/maps/level.map");                                                                                           
                                                                                                                                             
    if (in.is_open()) {                                                                                                                  
        in >> mapWidth >> mapHeight;                                                                                                     
        mapData.resize(mapWidth * mapHeight, 0);                                                                                         
                                                                                                                                             
        for (int y = 0; y < mapHeight; y++) {                                                                                            
            for (int x = 0; x < mapWidth; x++) {                                                                                         
                int val;                                                                                                                 
                in >> val;                                                                                                               
                SetTile(x, y, (unsigned char)val);                                                                        
                                                                                                                                             
                while (in.peek() == ' ' || in.peek() == '\n' || in.peek() == '\r') in.ignore();
                if (in.peek() == ',') in.ignore();
            }
        }
        
        std::cout << "SUCCESS: Loaded level.map, Size: " << mapWidth << "x" << mapHeight << std::endl;
    } 
    else {
        std::cout << "Could not find the Map File. Generating default 8 x 8 box." << std::endl;
        mapWidth = 8;
        mapHeight = 8;
        mapData.resize(mapWidth * mapHeight, 0);
            
        for(int y = 0; y < mapHeight; y++){
            for(int x = 0; x < mapWidth; x++){
                if (x == 0 || x == mapWidth - 1 || y == 0 || y == mapHeight - 1) {
                    SetTile(x, y, 1);
                }
            }
        }
    }
}

Map::~Map() {}

char Map::GetTile(int x, int y){
    if (x < 0 || x >= mapWidth || y < 0 || y >= mapHeight) return 1;
    return mapData[(y * mapWidth) + x];
}

void Map::SetTile(int x, int y, char tileID){
    mapData[(y * mapWidth) + x] = tileID;
}

char Map::GetWorldTile(float x, float y){
    int Gx = std::floor(x);
    int Gy = std::floor(y);
    return GetTile(Gx, Gy);
}
