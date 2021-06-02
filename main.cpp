/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "platform/mbed_thread.h"
#include "Alien.h"
#include "Spacecraft.h"
#include <cstdint>

#define DRAW_TITLE 0
#define WAIT_TITLE 1
#define INIT_GAME 2
#define PLAY_GAME 3
#define DRAW_END 4
#define WAIT_END 5

uint8_t state = DRAW_TITLE;

void SpacecraftManagement();
void SoundManagement();
void AlienManagement();

Thread* rocket_thread;
Thread* alien_thread;
Thread* sound_thread;

IOManager* io;
Spacecraft* rocket;

Alien* alien1;
Alien* alien2;
Alien* alien3;
Alien* alien4;
Alien* alien5;
Alien* alien6;
Alien* alien7;
Alien* alien8;
Alien* alien9;
Alien* alien10;

uint32_t score = 0;
uint32_t sleeper = 100;
uint32_t position_y = 10;
bool isShooting = false;

int main()
{
    io = IOManager::getSingleton();
    io->initDisplay();

    srand(time(NULL));

    sound_thread = new Thread();
    sound_thread->start(SoundManagement);

    thread_sleep_for(50);

    while(1) 
    {
        switch(state)
        {
            case DRAW_TITLE:
            {
                io->refreshDisplay();
                io->drawOnDisplay(TITLE, NULL);
                state = WAIT_TITLE;

                break;
            }

            case WAIT_TITLE:
            {
                if(io->isButtonPressed())
                    state = INIT_GAME;

            break;
            }

            case INIT_GAME:
            {   
                io->refreshDisplay();

                rocket = new Spacecraft(SIZE_X / 2, SIZE_Y - 20);
                alien1 = new Alien(10, position_y);
                alien2 = new Alien(30, position_y);
                alien3 = new Alien(50, position_y);
                alien4 = new Alien(70, position_y);
                alien5 = new Alien(90, position_y);
                alien6 = new Alien(20, position_y + 15);
                alien7 = new Alien(40, position_y + 15);
                alien8 = new Alien(60, position_y + 15);
                alien9 = new Alien(80, position_y + 15);
                alien10 = new Alien(100, position_y + 15);

                io->drawOnDisplay(SCORE, new uint32_t{score});

                rocket_thread = new Thread();
                alien_thread = new Thread();

                rocket_thread->start(SpacecraftManagement);
                alien_thread->start(AlienManagement);

                state = PLAY_GAME;
            break;
            }

            case PLAY_GAME:
            {
                if(rocket_thread->get_state() == Thread::Deleted && alien_thread->get_state() == Thread::Deleted)
                {
                    delete(rocket_thread);
                    delete(alien_thread);

                    delete(alien1);
                    delete(alien2);
                    delete(alien3);
                    delete(alien4);
                    delete(alien5);
                    delete(alien6);
                    delete(alien7);
                    delete(alien8);
                    delete(alien9);
                    delete(alien10);

                    if(rocket->isAlive() && sleeper >= 5)
                    {
                        sleeper -= 5;
                        position_y += 5;
                        state = INIT_GAME;
                        delete(rocket);
                    }

                    else
                        state = DRAW_END;
                }

            break;
            }

            case DRAW_END:
                io->refreshDisplay();

                if(rocket->isAlive())
                    io->drawOnDisplay(WIN, NULL);
                else    
                    io->drawOnDisplay(END, NULL);
                
                delete(rocket);
                state = WAIT_END;
            break;

            case WAIT_END:
                if(io->isButtonPressed())
                {
                    score = 0;
                    position_y = 10;
                    sleeper = 100;
                    state = DRAW_TITLE;
                }

            break;
        }
    }
}

void SpacecraftManagement()
{   
    rocket->drawSpacecraft();

    while(Alien::atLeastOneAlive() && rocket->isAlive())
    {
        io->readJoystick();

        if(io->isPointingRight())
            rocket->moveRight();

        else if(io->isPointingLeft())
            rocket->moveLeft();
        
        if(io->isButtonPressed())
        {
            isShooting = true;
            rocket->releaseBullet();
        }
        
        rocket->destroyOutBullets();

        for(Bullet& bullet : rocket->getBullets())
        {
            bullet.moveBullet();
            
            for(Alien& alien : Alien::getAliens())
                if(alien.isAlive() && bullet.getY() >= alien.getY() - 10 && 
                bullet.getY() <= alien.getY() &&
                bullet.getX() >= alien.getStartX() && 
                bullet.getX() <= alien.getEndX())
                {
                    alien.destroy();
                    bullet.destroyBullet();
                    io->drawOnDisplay(SCORE, new uint32_t{++score});
                    break;
                }
         }

        thread_sleep_for(100);
    }

    Alien::clearAliens();
}

void AlienManagement()
{
    uint32_t wait = sleeper;

    Alien::drawAllAliens();

    while(Alien::atLeastOneAlive() && rocket->isAlive())
    {
        Alien::destroyOutBullets();

        if(wait == 0)
        {
            Alien::moveAllRandom();
            Alien::moveAllDown();
            Alien::randomBulletRelease();

            wait = sleeper;
        }

        if(Alien::areTouchingSpacecraft(*rocket) || !Alien::areInField())
            rocket->destroy();

        else
        {
            for(Bullet& bullet : Alien::getBullets())
            {
                bullet.moveBullet();

                if(bullet.getY() <= rocket->getEndY() && 
                bullet.getY() >= rocket->getStartY() &&
                bullet.getX() >= rocket->getStartX() && 
                bullet.getX() <= rocket->getEndX())
                {
                    rocket->destroy();
                    break;
                }
            }
        }

        thread_sleep_for(100);
        wait--;
    }

    Alien::clearAliens();
}

void SoundManagement()
{
    uint32_t temp_score = 0;

    while(1)
    {
        switch(state)
        {
            case WAIT_TITLE:
                io->emitSoundTitle(state);
            break;

            case PLAY_GAME:
                if(temp_score < score)
                {
                    io->emitSoundDestroy();
                    temp_score = score;
                }

                if(isShooting)
                {
                    io->emitSoundShoot();
                    isShooting = false;
                }

                if(!rocket->isAlive())
                {
                    io->emitSoundDestroy();
                    temp_score = 0;
                }
            break;

            case WAIT_END:
                if(rocket->isAlive())
                    io->emitSoundWin(state);
                else
                    io->emitSoundGameOver(state);

            break;
        }

        thread_sleep_for(100);
    }
}
