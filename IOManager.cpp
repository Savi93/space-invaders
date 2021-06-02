#include "IOManager.h"
#include <cstdint>

IOManager* IOManager::singleton = NULL;

IOManager::IOManager() : x_coord(PA_0), butt(PA_8), display(PA_7, PA_6, PA_5, PB_6, PC_7, PA_9), buzzer(PB_4)
{
    butt.mode(PullUp);
    butt.fall(callback(this, &IOManager::buttonPressed));
    time.start();

    initDisplay();
}

IOManager* IOManager::getSingleton()
{
    if(singleton == NULL)
        singleton = new IOManager();
    
    return singleton;
}

IOManager::~IOManager()
{
    singleton = NULL;
}

void IOManager::readJoystick()
{
    uint32_t perc = x_coord.read() * 100;
    
    if(perc >= JOYSTICK_THRESH_RIGHT)
        right = true;
    else if(perc <= JOYSTICK_THRESH_LEFT)
        left = true;
    else
    {
        right = false;
        left = false;
    }
}

void IOManager::buttonPressed()
{
    if(time.read_ms() > 1500)
    {
        butt_pressed = true;
        time.reset();
    }
}

void IOManager::setButton(bool status)
{
    butt_pressed = status;
}

bool IOManager::isButtonPressed()
{   
    if(butt_pressed)
    {
        butt_pressed = false;
        return true;
    }

    return butt_pressed;
}

bool IOManager::isPointingLeft()
{
    return left;
}

bool IOManager::isPointingRight()
{
    return right;
}

void IOManager::initDisplay()
{
    display.initR(INITR_BLACKTAB);
    display.fillScreen(ST7735_BLACK); 
    display.setRotation(2);
}

void IOManager::refreshDisplay()
{
    mtx_display.lock();
    display.fillScreen(ST7735_BLACK);
    mtx_display.unlock();
}

void IOManager::drawOnDisplay(uint32_t type, uint32_t params[])
{
    mtx_display.lock();

    switch(type)
    {
        case TRIANGLE:
            display.fillTriangle(params[0], params[1], params[2], params[3], params[4], params[5], params[6]);
        break;
        case RECTANGLE:
            display.fillRect(params[0], params[1], params[2], params[3], params[4]);
        break;
        case CIRCLE:
            display.fillCircle(params[0], params[1], params[2], params[3]);
        break;
        case HORIZONTAL_LINE:
            display.drawFastHLine(params[0], params[1], params[2], params[3]);
        break;
        case VERTICAL_LINE:
            display.drawFastVLine(params[0], params[1], params[2], params[3]);
        break;
        case SCORE:
            display.fillRect(1, 1, 120, 10, ST7735_BLACK);
            display.setTextSize(1);
            display.setCursor(1, 1);
            display.setTextColor(ST7735_GREEN);
            display.printf("SCORE: %d", params[0]);
        break;
        case HIT:
            display.setTextSize(1);
            display.setCursor(params[0], params[1]);
            display.setTextColor(params[2]);
            display.printf("HIT");
        break;
        case TITLE:
            display.setCursor(1, 30);
            display.setTextSize(2);
            display.setTextColor(ST7735_GREEN);
            display.printf("SPACE");
            display.setCursor(1, 50);
            display.printf("INVADERS");
            display.setTextSize(1);
            display.setCursor(1, 100);
            display.printf("Press button to start the game ..");
        break;
        case END:
            display.setTextSize(2);
            display.setCursor(10, 50);
            display.setTextColor(ST7735_GREEN);
            display.printf("GAME OVER");
            display.setCursor(1, 100);
            display.setTextSize(1);
            display.printf("Press button to restart the game ..");
        break;
        case WIN:
            display.setTextSize(2);
            display.setCursor(15, 50);
            display.setTextColor(ST7735_GREEN);
            display.printf("YOU WIN!");
            display.setCursor(1, 100);
            display.setTextSize(1);
            display.printf("Press button to restart the game ..");

    }

    delete[] params;

    mtx_display.unlock();
}

void IOManager::emitSoundTitle(uint8_t& state)
{
    uint32_t j = 0;

    while(state == 1)
    {
        if(j == (sizeof(star_wars_notes) / sizeof(double)))
            j = 0;

        if(star_wars_notes[j] == NULL)
        {
            resetSound();
            thread_sleep_for(star_wars_time[j]);
        }

        else 
        {
            buzzer.period(star_wars_notes[j]);
            buzzer.write(0.3f);
            thread_sleep_for(star_wars_time[j]);
        }

        j++;
    }

    resetSound();
}

void IOManager::emitSoundShoot()
{
    uint32_t j = 0;

    while(j < (sizeof(shoot_notes) / sizeof(double)))
    {       
        buzzer.period(shoot_notes[j]);
        buzzer.write(0.3f);
        thread_sleep_for(shoot_time[j]);

        j++;
    }

    resetSound();
}

void IOManager::emitSoundDestroy()
{
    uint32_t j = 0;

    while(j < (sizeof(explosion_notes) / sizeof(double)))
    {       
        buzzer.period(explosion_notes[j]);
        buzzer.write(0.3f);
        thread_sleep_for(explosion_time[j]);

        j++;
    }

    resetSound();
}

void IOManager::emitSoundGameOver(uint8_t& state)
{
    uint32_t j = 0;

    while(state == 5)
    {
        if(j == (sizeof(game_over_notes) / sizeof(double)))
            j = 0;

        if(game_over_notes[j] == NULL)
        {
            resetSound();
            thread_sleep_for(game_over_time[j]);
        }

        else 
        {
            buzzer.period(game_over_notes[j]);
            buzzer.write(0.3f);
            thread_sleep_for(game_over_time[j]);
        }

        j++;
    }

    resetSound();
}

void IOManager::emitSoundWin(uint8_t& state)
{
    uint32_t j = 0;

    while(state == 5)
    {
        if(j == (sizeof(win_notes) / sizeof(double)))
            j = 0;

        if(win_notes[j] == NULL)
        {
            resetSound();
            thread_sleep_for(win_time[j]);
        }

        else 
        {
            buzzer.period(win_notes[j]);
            buzzer.write(0.3f);
            thread_sleep_for(win_time[j]);
        }

        j++;
    }

    resetSound();
}

void IOManager::resetSound()
{
    buzzer.write(0.0f);
}

