#include <cstdio>
#include "vector.h"
#include "state.h"

Vector Vector::operator*=(double h) {
    for (int i = 0; i < data.size(); ++i) {
        data[i] *= h;
    }
    return *this;
}

Vector Vector::operator+=(Vector other) {
    if (data.size() != other.data.size()) {
        throw ERR_VECTOR_SIZE_MISMATCH;
    }
    for (int i = 0; i < data.size(); ++i) {
        data[i] += other.data[i];
    }
    return *this;
}

void Vector::addBody(double x, double y, double z, double vx, double vy, double vz) {
    data.push_back(x);
    data.push_back(y);
    data.push_back(z);
    data.push_back(vx);
    data.push_back(vy);
    data.push_back(vz);
}

int Vector::size() const {
    return data.size();
}

void Vector::printOut(int i) const {
    printf("  <%e, %e, %e, %e, %e, %e>\n", data[i], data[i+1], data[i+2], data[i+3], data[i+4], data[i+5]);
}