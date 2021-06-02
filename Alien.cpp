#include "Alien.h"
#include <cstdint>

std::vector<Alien> Alien::aliens;
std::vector<Bullet> Alien::bullets;

Alien::Alien(uint32_t start_x, uint32_t start_y) : start_x(start_x), start_y(start_y), end_x(start_x + 10), end_y(start_y + 10), alive(true)
{
    this->color = COLORS[rand() % 10];

    aliens.push_back(*this);
}

void Alien::destroy()
{ 
    alive = false;

    uint32_t* params = new uint32_t[]{start_x, start_y, end_x - start_x, end_y - start_y, ST7735_BLACK};
    IOManager::getSingleton()->drawOnDisplay(RECTANGLE, params);

    params = new uint32_t[]{start_x, start_y, color};
    IOManager::getSingleton()->drawOnDisplay(HIT, params);

    thread_sleep_for(150);

    params = new uint32_t[]{start_x, start_y, 20, end_y - start_y, ST7735_BLACK};
    IOManager::getSingleton()->drawOnDisplay(RECTANGLE, params);
}

uint32_t Alien::getStartX()
{
    return start_x;
}

uint32_t Alien::getEndX()
{
    return end_x;
}

uint32_t Alien::getY()
{
    return end_y;
}

bool Alien::isAlive()
{
    return alive;
}

bool Alien::atLeastOneAlive()
{
    for(Alien& alien : aliens)
       if(alien.alive)
            return true;

    return false;
}

bool Alien::areInField()
{
    bool are = true;

    for(Alien& alien : aliens)
        if(alien.alive && alien.end_y >= SIZE_Y - 5)
        {
            are = false;
            break;
        }

    return are;
}

bool Alien::areTouchingSpacecraft(Spacecraft rocket)
{
    bool are = false;

    for(Alien& alien : aliens)
        if(alien.isAlive() && 
        (alien.getStartX() >= rocket.getStartX() && 
        alien.getStartX() <= rocket.getEndX() || 
        alien.getEndX() >= rocket.getStartX() && 
        alien.getEndX() <= rocket.getEndX()) &&
        alien.getY() >= rocket.getStartY() && 
        alien.getY() <= rocket.getEndY())
        {
            are = true;
            break;
        }

    return are;
}

void Alien::moveAllLeft()
{
    for(Alien& alien : aliens)
        if(alien.alive)
        {
            uint32_t* params; 

            for(int j = 0; j <= 5; j++)
            {
                params = new uint32_t[]{alien.end_x - j, alien.start_y, alien.end_y - alien.start_y, ST7735_BLACK};
                IOManager::getSingleton()->drawOnDisplay(VERTICAL_LINE, params);
            }
            
            alien.start_x -= SPEED_ALIEN;
            alien.end_x -= SPEED_ALIEN;
        }
    
    drawAllAliens();
}

void Alien::moveAllRight()
{
    for(Alien& alien : aliens)
        if(alien.alive)
        {
            uint32_t* params; 

            for(int j = 0; j <= 5; j++)
            {
                params = new uint32_t[]{alien.start_x + j, alien.start_y, alien.end_y - alien.start_y, ST7735_BLACK};
                IOManager::getSingleton()->drawOnDisplay(VERTICAL_LINE, params);
            }

            alien.start_x += SPEED_ALIEN;
            alien.end_x += SPEED_ALIEN;
        }

        drawAllAliens();
}

void Alien::moveAllDown()
{
    for(Alien& alien : aliens)
        if(alien.alive)
        {
             uint32_t* params; 

            for(int j = 0; j <= 5; j++)
            {
                params = new uint32_t[]{alien.start_x, alien.start_y + j, alien.end_x - alien.start_x, ST7735_BLACK};
                IOManager::getSingleton()->drawOnDisplay(HORIZONTAL_LINE, params);
            }
                alien.start_y += SPEED_ALIEN;
                alien.end_y += SPEED_ALIEN;
        }

        drawAllAliens();
}

void Alien::randomBulletRelease()
{
    for(Alien& alien : aliens)
        if(alien.alive && rand() % 2 == 1)
            Alien::getBullets().push_back(Bullet((alien.end_x + alien.start_x) / 2, alien.end_y + 2, 'A'));
}

void Alien::moveAllRandom()
{
    uint32_t val = rand() % 2;

    switch(val)
    {
        case 0:
        if(canAllMoveRight())
            moveAllRight();
        break;
        
        case 1:
        if(canAllMoveLeft())
            moveAllLeft();
        break;   
    }
}

bool Alien::canAllMoveLeft()
{
    bool can = true;

    for(Alien& alien : aliens)
        if(alien.alive && alien.getStartX() <= 10)
        {
            can = false;
            break;
        }
    
    return can;
}

bool Alien::canAllMoveRight()
{
    bool can = true;

    for(Alien& alien : aliens)
        if(alien.alive && alien.getEndX() >= SIZE_X - 10)
        {
            can = false;
            break;
        }
    
    return can;
}

void Alien::drawAllAliens()
{
    for(Alien& alien : aliens)
        if(alien.alive)
        {
            uint32_t* params = new uint32_t[]{alien.start_x, alien.start_y, alien.end_x - alien.start_x, 10, alien.color};
            IOManager::getSingleton()->drawOnDisplay(RECTANGLE, params);

            params = new uint32_t[]{alien.start_x + 2, alien.start_y, 2, ST7735_WHITE};
            IOManager::getSingleton()->drawOnDisplay(VERTICAL_LINE, params);

            params = new uint32_t[]{alien.end_x - 3, alien.start_y, 2, ST7735_WHITE};
            IOManager::getSingleton()->drawOnDisplay(VERTICAL_LINE, params);

            params = new uint32_t[]{alien.start_x + 2, (alien.start_y + alien.end_y) / 2, 1, ST7735_BLACK};
            IOManager::getSingleton()->drawOnDisplay(HORIZONTAL_LINE, params);

            params = new uint32_t[]{alien.end_x - 3, (alien.start_y + alien.end_y) / 2, 1, ST7735_BLACK};
            IOManager::getSingleton()->drawOnDisplay(HORIZONTAL_LINE, params);
        }
}

void Alien::clearAliens()
{
    aliens.clear();
    bullets.clear();
}

void Alien::destroyOutBullets()
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

std::vector<Alien>& Alien::getAliens()
{
    return aliens;
}

std::vector<Bullet>& Alien::getBullets()
{
    return bullets;
}


