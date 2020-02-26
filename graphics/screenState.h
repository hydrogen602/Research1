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
    pixel ** data; // each points to a row of pixels
    unsigned int height;
    unsigned int width;
public:
    screenState(unsigned int h, unsigned int w);
    ~screenState();

    void setPixel(unsigned int row, unsigned int col, pixel p);
    pixel getPixel(unsigned int row, unsigned int col) const;
};

#endif
