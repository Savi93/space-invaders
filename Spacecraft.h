#ifndef SPACECRAFT_H
#define SPACECRAFT_H

#include <cstdint>
#include "Bullet.h"
#include <vector>

#define SPEED_SPACECRAFT 5
#define SIZE_X 128
#define SIZE_Y 160

class Spacecraft
{
    private:
        uint32_t start_x;
        uint32_t end_x;
        uint32_t start_y;
        uint32_t end_y;
        bool alive;
        std::vector<Bullet> bullets;

    public:
        Spacecraft(uint32_t, uint32_t);
        void drawSpacecraft();
        void moveLeft();
        void moveRight();
        void releaseBullet();
        void destroy();
        bool isAlive();
        uint32_t getStartY();
        uint32_t getEndY();
        uint32_t getStartX();
        uint32_t getEndX();
        void destroyOutBullets();
        std::vector<Bullet>& getBullets();
};

#endif