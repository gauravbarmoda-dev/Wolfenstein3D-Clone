#include "include.h"

// RayCasting
void MAP3D::Draw(MAP2D *map, PLAYER *player, SCREEN *screen){
    
    if (!lutInit) {
        float pixelPerCol = PLAYER_FOV / (float)SCREEN_WIDTH;
        for (int i = 0; i < SCREEN_WIDTH; i++) {
            float rayAngleOffset = (pixelPerCol * i) - (PLAYER_FOV / 2.0f);
            fisheyeLUT[i] = cosf(rayAngleOffset);
        }
        lutInit = true;
    }

    char tile = EMPTY;

    Color* floorTex = (Color*)Textures[8].data;
    Color* ceilTex  = (Color*)Textures[9].data;

    // WallCasting
    for(int x = 0; x < SCREEN_WIDTH; x++){
        float distance = 0.0f;
        bool collision = false;

        float startAngle  =  player->angle - (PLAYER_FOV / 2.0f);
        float pixelPerCol =  PLAYER_FOV / (float)SCREEN_WIDTH;
        float rayAngle    =  startAngle + (pixelPerCol * x);

        int mapX = (int)player->p.x;
        int mapY = (int)player->p.y;

        Vector2 rayDir    = { cosf(rayAngle), sinf(rayAngle) };
        Vector2 deltaDist = { 
            (rayDir.x == 0) ? 1e30f : std::abs(1.0f / rayDir.x),
            (rayDir.y == 0) ? 1e30f : std::abs(1.0f / rayDir.y)
        };
        Vector2 trackDist;
        Vector2 step;

        bool NorthWall = false;

        if(rayDir.x < 0){
            step.x = -1;
            trackDist.x = (player->p.x - mapX) * deltaDist.x;
        }
        else {
            step.x = 1;
            trackDist.x = (mapX + 1.0f - player->p.x) * deltaDist.x;
        }

        if(rayDir.y < 0){
            step.y = -1;
            trackDist.y = (player->p.y - mapY) * deltaDist.y;
        }
        else{
            step.y = 1;
            trackDist.y = (mapY + 1.0f - player->p.y) * deltaDist.y;
        }   

        while(!collision){
            if(trackDist.x < trackDist.y){
                trackDist.x += deltaDist.x;
                mapX += step.x;
                NorthWall = false;
            }
            else{
                trackDist.y += deltaDist.y;
                mapY += step.y;
                NorthWall = true;
            }
            
            tile = map->GetTile(mapX, mapY);
            if(tile != EMPTY) collision = true;
        }

        (NorthWall == false) ? 
        (distance = trackDist.x - deltaDist.x) : 
        (distance = trackDist.y - deltaDist.y);

        float euclidianDistance = distance;

        distance *= fisheyeLUT[x];       

        float wallHEIGHT = (int)SCREEN_HEIGHT / distance;
        float topOfWall  = (SCREEN_HEIGHT / 2.0f) - (wallHEIGHT / 2.0f);
        float botOfWall  = (SCREEN_HEIGHT / 2.0f) + (wallHEIGHT / 2.0f);

        float wallX;

        (NorthWall == false) ? 
        (wallX = player->p.y + euclidianDistance * rayDir.y) :
        (wallX = player->p.x + euclidianDistance * rayDir.x);

        wallX -= floor(wallX);

        int texID = 0;
        switch(tile){
            case RED_WALL    :   texID = 0; break;
            case BLUE_WALL   :   texID = 1; break;
            case GREEN_WALL  :   texID = 2; break;
            case BROWN_WALL  :   texID = 3; break;
            case CYAN_WALL   :   texID = 4; break;
            case PINK_WALL   :   texID = 5; break;
            case YELLOW_WALL :   texID = 6; break;
            case LIME_WALL   :   texID = 7; break;
            default : break;
        }

        int texX = (int)(wallX * (float)Textures[texID].width);

        if(NorthWall == false && rayDir.x > 0) texX = Textures[texID].width - texX - 1;
        if(NorthWall == true  && rayDir.y < 0) texX = Textures[texID].width - texX - 1;

        if(texX < 0) texX = 0;
        if(texX >= Textures[texID].width) texX = Textures[texID].width - 1;

        int startY = topOfWall;
        int endY   = botOfWall;

        if(startY <= 0) startY = 0;
        if(endY >= SCREEN_HEIGHT) endY = SCREEN_HEIGHT - 1;
        
        Color* texPixel = (Color*)Textures[texID].data;

        int texWidth  = Textures[texID].width;
        int texHeight = Textures[texID].height;

        float maxFogDistance = 11.0f;
        float brightness = 1.0f - (distance / maxFogDistance);
        if (brightness < 0.0f) brightness = 0.0f;
        
        if (brightness > 0.0f) {
            int shadowMask = (int)(brightness * 255.0f);
            
            float texYStep = (float)texHeight / wallHEIGHT;
            float currentTexY = (startY - (SCREEN_HEIGHT / 2.0f) + (wallHEIGHT / 2.0f)) * texYStep;
            
            int pixelIndex = startY * SCREEN_WIDTH + x;

            for(int y = startY; y < endY; y++){
                int texY = (int)currentTexY;
                currentTexY += texYStep;
      
                if(texY < 0) texY = 0;
                if(texY >= texHeight) texY = texHeight - 1;

                Color c = texPixel[texY * texWidth + texX];

                c.r = (c.r * shadowMask) >> 8;
                c.g = (c.g * shadowMask) >> 8;
                c.b = (c.b * shadowMask) >> 8;
      
                screen->pixels[pixelIndex] = c;
                pixelIndex += SCREEN_WIDTH;
            }
        }

        float fisheyeFix = fisheyeLUT[x];

        int startYFloor = botOfWall;
        if(startYFloor <= SCREEN_HEIGHT / 2) startYFloor = (SCREEN_HEIGHT / 2) + 1;

        // FloorCasting
        for(int y = startYFloor; y < SCREEN_HEIGHT; y++){
            int posZ = y - (SCREEN_HEIGHT / 2);
            float distance = (SCREEN_HEIGHT * 0.5f) / posZ;
            
            distance /= fisheyeFix;

            float brightness = 1.0f - (distance / 10.0f);
            
            if (brightness <= 0.0f) continue;
            
            int shadowMask = (int)(brightness * 255.0f); 

            float floorX = player->p.x + distance * rayDir.x;
            float floorY = player->p.y + distance * rayDir.y;

            // 127 in binary is 01111111 
            int texX = (int)(floorX * 128.0f) & 127;
            int texY = (int)(floorY * 128.0f) & 127;

            int ceilingY = SCREEN_HEIGHT - y - 1;

            Color fColor = floorTex[texY * Textures[8].width + texX];
            fColor.r = (fColor.r * shadowMask) >> 8;
            fColor.g = (fColor.g * shadowMask) >> 8;
            fColor.b = (fColor.b * shadowMask) >> 8;
            screen->pixels[y * SCREEN_WIDTH + x] = fColor;

            if(ceilingY >= 0 && ceilingY < SCREEN_HEIGHT) {
                Color cColor = ceilTex[texY * Textures[9].width + texX];
                cColor.r = (cColor.r * shadowMask) >> 8;
                cColor.g = (cColor.g * shadowMask) >> 8;
                cColor.b = (cColor.b * shadowMask) >> 8;
                screen->pixels[ceilingY * SCREEN_WIDTH + x] = cColor;
            } 
        }
    }
}