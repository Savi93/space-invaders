#include "Spacecraft.h"

Spacecraft::Spacecraft(uint32_t start_x, uint32_t start_y) : start_x(start_x), start_y(start_y), end_x(start_x + 10), end_y(start_y + 15), alive(true)
{
    
}

void Spacecraft::drawSpacecraft()
{
    uint32_t* params = new uint32_t[]{start_x, start_y, end_x - start_x, 3, ST7735_RED};
    IOManager::getSingleton()->drawOnDisplay(RECTANGLE, params);

    params = new uint32_t[]{start_x, start_y + 3, end_x - start_x, 6, ST7735_LIGHT_GREY};
    IOManager::getSingleton()->drawOnDisplay(RECTANGLE, params);

    params = new uint32_t[]{start_x, start_y + 9, end_x - start_x, 3, ST7735_DARK_GREY};
    IOManager::getSingleton()->drawOnDisplay(RECTANGLE, params);

    for(uint32_t x = 0; x < end_x - start_x; x++)
    {
        if(x % 2 == 0)
            params = new uint32_t[]{start_x + x, start_y + 12, 3, ST7735_RED};
        else
            params = new uint32_t[]{ start_x + x, start_y + 12, 2, ST7735_YELLOW};
        
        IOManager::getSingleton()->drawOnDisplay(VERTICAL_LINE, params);
    }
}

void Spacecraft::moveRight()
{
    uint32_t* params; 

    for(uint32_t j = 0; j <= SPEED_SPACECRAFT; j++)
    {
        params = new uint32_t[]{start_x + j, start_y, end_y - start_y, ST7735_BLACK};
        IOManager::getSingleton()->drawOnDisplay(VERTICAL_LINE, params);
    }

    if(end_x < SIZE_X - 10)
    {
        start_x += SPEED_SPACECRAFT;
        end_x += SPEED_SPACECRAFT;
    }

    drawSpacecraft();
}

void Spacecraft::moveLeft()
{
    uint32_t* params; 

     for(int j = 0; j <= SPEED_SPACECRAFT; j++)
     {
        params = new uint32_t[]{end_x - j, start_y, end_y - start_y, ST7735_BLACK};
        IOManager::getSingleton()->drawOnDisplay(VERTICAL_LINE, params);
     }

    if(start_x > 10)
    {
        start_x -= SPEED_SPACECRAFT;
        end_x -= SPEED_SPACECRAFT;
    }
    
    drawSpacecraft();
}

void Spacecraft::releaseBullet()
{
    bullets.push_back(Bullet((end_x + start_x) / 2, start_y - 2, 'S'));
}

uint32_t Spacecraft::getStartX()
{
    return start_x;
}

uint32_t Spacecraft::getEndX()
{
    return end_x;
}

uint32_t Spacecraft::getStartY()
{
    return start_y;
}

uint32_t Spacecraft::getEndY()
{
    return end_y;
}

void Spacecraft::destroy()
{
    alive = false;

    uint32_t* params = new uint32_t[]{start_x, start_y, end_x - start_x, end_y - start_y, ST7735_BLACK};
    IOManager::getSingleton()->drawOnDisplay(RECTANGLE, params);

    params = new uint32_t[]{start_x, start_y, ST7735_RED};
    IOManager::getSingleton()->drawOnDisplay(HIT, params);
}

void Spacecraft::destroyOutBullets()
{
    uint32_t count = 0;

    for(Bullet& bullet : bullets)
    {
        if(bullet.isOutOfScope())
            bullets.erase(bullets.begin() + count);

        else
            count++;
    }
}

bool Spacecraft::isAlive()
{
    return alive;
}

std::vector<Bullet>& Spacecraft::getBullets()
{
    return bullets;
}
