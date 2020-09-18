#ifndef SCREEN_STATE_H_
#define SCREEN_STATE_H_

#define ERR_VECTOR_OUT_OF_BOUNDS 43

typedef struct pixelState
{
    char character;
    char color;
} pixel;

class screenState
{
private:
    pixel * data;
    unsigned int height;
    unsigned int width;
    double scaleFactor;
public:
    screenState(unsigned int h, unsigned int w);
    screenState(const screenState &src);
    //screenState(screenState &&src);
    ~screenState();

    //void init(unsigned int h, unsigned int w);

    void setScaleFactor(double d);
    double getScaleFactor();

    void shiftPixelsLeft(unsigned int shift);

    void setPixel(unsigned int row, unsigned int col, pixel p);
    pixel getPixel(unsigned int row, unsigned int col) const;
};

#endif
