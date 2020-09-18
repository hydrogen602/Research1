#include "screenState.h"

screenState::screenState(unsigned int h, unsigned int w): height{h}, width{w} {
    data = new pixel[height * width];
    scaleFactor = 1;

    pixel p = {' ', 7};
    for (int i = 0; i < height * width; ++i) {
        data[i] = p;
    }
}

screenState::screenState(const screenState &src) {
    data = new pixel[src.height * src.width];
    height = src.height;
    width = src.width;
    scaleFactor = src.scaleFactor;
    for (int i = 0; i < height * width; ++i) {
        data[i] = src.data[i];
    }
}

// screenState::screenState(screenState &&src) {
//     data = src.data;
//     height = src.height;
//     width = src.width;
//     scaleFactor = src.scaleFactor;

//     src.data = nullptr;
//     src.height = 0;
//     src.width = 0;
//     src.scaleFactor = 0;
// }

screenState::~screenState() {
    delete[] data;
}

void screenState::setScaleFactor(double d) {
    scaleFactor = d;
}

double screenState::getScaleFactor() {
    return scaleFactor;
}

void screenState::shiftPixelsLeft(unsigned int shift) {
    pixel p = {' ', 7};
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            if (col + shift >= width) {
                data[row * width + col] = p;
            }
            else {
                data[row * width + col] = data[row * width + col + shift];
            }
            
        }
    }
}

void screenState::setPixel(unsigned int row, unsigned int col, pixel p) {
    if (row >= height || col >= width) {
        throw ERR_VECTOR_OUT_OF_BOUNDS;
    }
    data[row * width + col] = p;
}

pixel screenState::getPixel(unsigned int row, unsigned int col) const {
    if (row >= height || col >= width) {
        throw ERR_VECTOR_OUT_OF_BOUNDS;
    }
    return data[row * width + col];
}