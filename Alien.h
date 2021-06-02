#ifndef ALIEN_H
#define ALIEN_H

#include "vector"
#include <cstdint>
#include "Spacecraft.h"
#include "Bullet.h"

#define SPEED_ALIEN 5
#define SIZE_X 128
#define SIZE_Y 160

class Alien
{
    private:
        const int COLORS[10] = {ST7735_BLUE, ST7735_LIGHT_GREY, ST7735_DARK_GREY, ST7735_RED, ST7735_GREEN, ST7735_OLIVE, ST7735_CYAN, ST7735_MAGENTA, ST7735_YELLOW, ST7735_WHITE};
        uint32_t start_x;
        uint32_t end_x;
        uint32_t start_y;
        uint32_t end_y;
        uint32_t color;
        uint32_t position;
        bool alive;
        static std::vector<Alien> aliens;
        static std::vector<Bullet> bullets;

    public:
        Alien(uint32_t, uint32_t);
        void destroy();
        uint32_t getStartX();
        uint32_t getEndX();
        uint32_t getY();
        bool isAlive();
        static std::vector<Alien>& getAliens();
        static std::vector<Bullet>& getBullets();
        static bool atLeastOneAlive();
        static bool areInField();
        static bool areTouchingSpacecraft(Spacecraft);
        static void moveAllDown();
        static void moveAllLeft();
        static void moveAllRight();
        static bool canAllMoveLeft();
        static bool canAllMoveRight();
        static void moveAllRandom();
        static void randomBulletRelease();
        static void destroyOutBullets();
        static void drawAllAliens();  
        static void clearAliens();

};

#endif