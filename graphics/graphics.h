#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include "screenState.h"
#include <vector>

#define RED_ON_BLACK 1
#define GREEN_ON_BLACK 2
#define YELLOW_ON_BLACK 3
#define BLUE_ON_BLACK 4
#define CYAN_ON_BLACK 5
#define MAGENTA_ON_BLACK 6
#define WHITE_ON_BLACK 7

#define BLACK_ON_RED 8
#define BLACK_ON_GREEN 9
#define BLACK_ON_YELLOW 10
#define BLACK_ON_BLUE 11
#define BLACK_ON_CYAN 12
#define BLACK_ON_MAGENTA 13
#define BLACK_ON_WHITE 14

// first 6 digits are first 2 digits of filename
#define ERR_INVALID_COLOR 103114000

class graphics {
public:
    typedef struct screen_size_container {
            int max_x;
            int max_y;
    } screen_size;
private:
    //double scale_factor;
    screen_size screenSize;
    
    int currentScreen;
    char currentColor;

    std::vector<screenState> screens;

    void drawPoint(int x, int y, char c);
public:
    graphics();

    void newScreenState();

    screen_size init();

    void initColor();

    void setColor(char c);

    void sleep(unsigned int t);

    int sleepInterruptible(unsigned int t);

    void refreshDisplay();

    void end();

    void setScaleFactor(double d, int screen);

    void drawPoint(double x, double y, char c, int screen);

    void setScreenRelNoThrow(int i);

    void setScreen(int i);

    void shiftPixelsLeft(int shift, int screen);

    int countScreens();

    int getCurrentScreen();

};

#endif