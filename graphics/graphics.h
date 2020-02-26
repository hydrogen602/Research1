#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include "screenState.h"

// first 6 digits are first 2 digits of filename
#define ERR_INVALID_COLOR 103114000

class graphics {
public:
    typedef struct screen_size_container {
            int max_x;
            int max_y;
    } screen_size;
private:
    double scale_factor;
    screen_size screenSize;
    int currentScreen;

public:
    graphics();

    screen_size init();

    void initColor();

    void setColor(unsigned int c);

    void sleep(unsigned int t);

    void refreshDisplay();

    void end();

    void setScaleFactor(double d);

    void drawPoint(double x, double y, char c);

};

#endif