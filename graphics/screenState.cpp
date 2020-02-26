#include "screenState.h"

screenState::screenState(unsigned int h, unsigned int w): height{h}, width{w} {
    data = new pixel * [height];
    for (unsigned int row = 0; row < height; ++row) {
        data[row] = new pixel [width];
    }
}

screenState::~screenState() {
    for (unsigned int row = 0; row < height; ++row) {
        delete[] data[row];
    }
    delete[] data;
}

void screenState::setPixel(unsigned int row, unsigned int col, pixel p) {
    if (row >= height || col >= width) {
        throw ERR_VECTOR_OUT_OF_BOUNDS;
    }
    data[row][col] = p;
}

pixel screenState::getPixel(unsigned int row, unsigned int col) const {
    if (row >= height || col >= width) {
        throw ERR_VECTOR_OUT_OF_BOUNDS;
    }
    return data[row][col];
}