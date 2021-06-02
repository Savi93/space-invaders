#include "Bullet.h"
#include <cstdint>

Bullet::Bullet(uint32_t x, uint32_t start_y, char type): x(x), start_y(start_y), end_y(start_y + SIZE_BULLET), type(type), out(false)
{
    if(this->type == 'S')
        this->color = ST7735_YELLOW;
    else 
        this->color = ST7735_CYAN;

    Bullet::drawBullet();
}

void Bullet::drawBullet()
{
    uint32_t* params; 
    params = new uint32_t[]{x, start_y, SIZE_BULLET, color};
    IOManager::getSingleton()->drawOnDisplay(VERTICAL_LINE, params);
}

void Bullet::destroyBullet()
{
     out = true;
     
     uint32_t* params; 
     params = new uint32_t[]{x, start_y, SIZE_BULLET, ST7735_BLACK};
     IOManager::getSingleton()->drawOnDisplay(VERTICAL_LINE, params);
}

void Bullet::moveBullet()
{
    switch(type)
    {
        case 'S':
            if(start_y >= 10)
            {
                uint32_t* params; 
                params = new uint32_t[]{x, start_y, SIZE_BULLET, ST7735_BLACK};
                IOManager::getSingleton()->drawOnDisplay(VERTICAL_LINE, params);

                params = new uint32_t[]{x, start_y - SIZE_BULLET, SIZE_BULLET, color};
                IOManager::getSingleton()->drawOnDisplay(VERTICAL_LINE, params);

                start_y -= SIZE_BULLET;
                end_y -= SIZE_BULLET;
            }
        
            else
            {
                destroyBullet();
                out = true;
            }
            break;

        case 'A':
            if(start_y <= 180 - 10)
            {
                uint32_t* params; 
                params = new uint32_t[]{x, start_y, SIZE_BULLET, ST7735_BLACK};
                IOManager::getSingleton()->drawOnDisplay(VERTICAL_LINE, params);

                params = new uint32_t[]{x, start_y + SIZE_BULLET, SIZE_BULLET, color};
                IOManager::getSingleton()->drawOnDisplay(VERTICAL_LINE, params);

                start_y += SIZE_BULLET;
                end_y += SIZE_BULLET;
            }

            else
            {
                destroyBullet();
                out = true;
            }
            break;
    }
}

bool Bullet::isOutOfScope()
{
    if(out)
        return true;

    return false;
}

uint32_t Bullet::getX()
{
    return x;
}

uint32_t Bullet::getY()
{
    return start_y;
}