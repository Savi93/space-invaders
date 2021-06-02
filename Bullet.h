#ifndef BULLET_H
#define BULLET_H

#include <vector>
#include "mbed.h"
#include "IOManager.h"
#include <cstdint>

#define SIZE_BULLET 2
#define SPEED_BULLET 2

class Bullet
{
    private:
        uint32_t x;
        uint32_t start_y;
        uint32_t end_y;
        uint32_t color;
        char type;
        bool out;
    
    public:
        Bullet(uint32_t, uint32_t, char);
        void drawBullet();
        void moveBullet();
        bool isOutOfScope();
        uint32_t getX();
        uint32_t getY();
        void destroyBullet();
};

#endif