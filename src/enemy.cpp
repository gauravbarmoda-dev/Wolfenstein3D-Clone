#include "include.h"

void ENEMY::Draw(PLAYER *player, float *zBuffer, SCREEN *screen){
    float spriteX = x - player->p.x;
    float spriteY = y - player->p.y;

    float maxDistance = 11.0f;    

    if(spriteX * spriteX + spriteY * spriteY > (maxDistance * maxDistance)) return;

    Vector2 dir = { 
        cosf(player->angle), 
        sinf(player->angle) 
    };
    
    float fovMultiplier = tanf(PLAYER_FOV / 2.0f);
    Vector2 plane = { 
        (-dir.y * fovMultiplier), 
        (dir.x * fovMultiplier) 
    };

    float invDet = 1.0f / (dir.y * plane.x - dir.x * plane.y);
    Vector2 transform = { 
        invDet * (dir.y * spriteX - dir.x * spriteY), 
        invDet * (plane.x * spriteY - plane.y * spriteX) 
    };

    if(transform.y > 0.1f && transform.y < maxDistance){
        int spriteScreenX = (int)((SCREEN_WIDTH / 2.0f) * (1.0f + transform.x / transform.y));
        int spriteHeight  = abs((int)(SCREEN_HEIGHT / transform.y));
        int spriteWidth = spriteHeight;
        
        int drawStartY = (SCREEN_HEIGHT / 2) - (spriteHeight / 2);
        int drawEndY   = (SCREEN_HEIGHT / 2) + (spriteHeight / 2);
        int drawStartX = spriteScreenX - (spriteWidth / 2);
        int drawEndX   = spriteScreenX + (spriteWidth / 2);

        if (drawStartY < 0) drawStartY = 0;
        if (drawEndY >= SCREEN_HEIGHT) drawEndY = SCREEN_HEIGHT - 1;

        int texID = 12;
        Color* texPixel = (Color*)Textures[texID].data;
        
        int texWidth = Textures[texID].width;
        int texHeight = Textures[texID].height;

        for(int stripe = drawStartX; stripe < drawEndX; stripe++){
            if((stripe >= 0) && (stripe < SCREEN_WIDTH) && (transform.y < zBuffer[stripe])){
                int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;

                for(int y = drawStartY; y < drawEndY; y++){
                    int d = (y) * 256 - SCREEN_HEIGHT * 128 + spriteHeight * 128;
                    int texY = ((d * texHeight) / spriteHeight) / 256;

                    Color c = texPixel[texY * texWidth + texX];

                    if(c.a > 128){
                        screen->pixels[y * SCREEN_WIDTH + stripe] = c;
                    }
                }
            }
        }
    }
}
