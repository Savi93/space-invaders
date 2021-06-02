#ifndef IOMANAGER_H
#define IOMANAGER_H

#include "mbed.h"
#include "Adafruit_ST7735.h"
#include <cstdint>
#include "rtos.h"
#include "Sound.h"

#define TRIANGLE 0
#define RECTANGLE 1
#define CIRCLE 2
#define VERTICAL_LINE 3
#define HORIZONTAL_LINE 4
#define SCORE 5
#define HIT 6
#define TITLE 7
#define END 8
#define WIN 9

class IOManager
{
    private:
        IOManager();
        static IOManager* singleton;
        
        AnalogIn x_coord;
        PwmOut buzzer;
        InterruptIn butt;
        Adafruit_ST7735 display;
        Mutex mtx_display;
        Timer time;

        bool left;
        bool right;
        bool butt_pressed;

        const uint32_t JOYSTICK_SPEED = 250;
        const uint32_t JOYSTICK_THRESH_LEFT = 20;
        const uint32_t JOYSTICK_THRESH_RIGHT = 80;

    public:
        ~IOManager();
        void initDisplay();
        void readJoystick();
        bool isPointingLeft();
        bool isPointingRight();
        void buttonPressed();
        void setButton(bool);
        bool isButtonPressed();
        void drawOnDisplay(uint32_t, uint32_t[]);
        void refreshDisplay();
        void emitSoundTitle(uint8_t&);
        void emitSoundShoot();
        void emitSoundDestroy();
        void emitSoundGameOver(uint8_t&);
        void emitSoundWin(uint8_t&);
        void resetSound();

        static IOManager* getSingleton();
};

#endif
