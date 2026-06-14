#include "include.h"                                                                                                                     
#include <fstream>                                                                                                                       
#include <iostream>                                                                                                                      
                                                                                                                                             
MAP2D::MAP2D() {                                                                                                                         
    std::ifstream in("../MapMaker/level.map");                                                                                           
                                                                                                                                             
    if (in.is_open()) {                                                                                                                  
        in >> mapWidth >> mapHeight;                                                                                                     
        mapData.resize(mapWidth * mapHeight, 0);                                                                                         
                                                                                                                                             
        for (int y = 0; y < mapHeight; y++) {                                                                                            
            for (int x = 0; x < mapWidth; x++) {                                                                                         
                int val;                                                                                                                 
                in >> val;                                                                                                               
                mapData[(y * mapWidth) + x] = (unsigned char)val;                                                                        
                                                                                                                                             
                while (in.peek() == ' ' || in.peek() == '\n' || in.peek() == '\r') in.ignore();
                if (in.peek() == ',') in.ignore();
            }
        }
        
        std::cout << "SUCCESS: Loaded level.map! Size: " << mapWidth << "x" << mapHeight << std::endl;
    } 
    else {
        std::cout << "WARNING: Could not find ../MapMaker/level.map! Generating default 24x24 box." << std::endl;
        mapWidth = 24;
        mapHeight = 24;
        mapData.resize(mapWidth * mapHeight, 0);
            
        for (int y = 0; y < mapHeight; y++) {
            for (int x = 0; x < mapWidth; x++) {
                if (x == 0 || x == mapWidth - 1 || y == 0 || y == mapHeight - 1) {
            mapData[(y * mapWidth) + x] = BROWN_WALL;
                }
            }
        }
    }
}
  
char MAP2D::GetTile(int x, int y) {
    if (x < 0 || x >= mapWidth || y < 0 || y >= mapHeight) return 1; 
    return mapData[(y * mapWidth) + x];
}