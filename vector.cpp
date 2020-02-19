#include <cstdio>
#include "vector.h"
#include "state.h"

Vector::Vector() {
}

Vector::Vector(int n) {
    data.resize(n, 0.0);
}

Vector::Vector(const Vector& src) {
    data.resize(src.data.size(), 0);
    for (unsigned int i = 0; i < src.data.size(); ++i) {
        data[i] = src.data[i];
    }
}

Vector& Vector::operator=(const Vector& other) {
    data.resize(other.data.size(), 0);
    for (unsigned int i = 0; i < other.data.size(); ++i) {
        data[i] = other.data[i];
    }
    return *this;
}

Vector& Vector::operator*=(double h) {
    for (unsigned int i = 0; i < data.size(); ++i) {
        data[i] *= h;
    }
    return *this;
}

Vector& Vector::operator+=(const Vector& other) {
    if (data.size() != other.data.size()) {
        throw ERR_VECTOR_SIZE_MISMATCH;
    }
    for (unsigned int i = 0; i < data.size(); ++i) {
        data[i] += other.data[i];
    }
    return *this;
}

double& Vector::operator[](unsigned int i) {
    if (i >= data.size()) {
        throw ERR_VECTOR_OUT_OF_BOUNDS;
    }
    return data[i];
}

const double& Vector::operator[](unsigned int i) const {
    if (i >= data.size()) {
        throw ERR_VECTOR_OUT_OF_BOUNDS;
    }
    return data[i];
}

Vector Vector::operator/(double m) const {
    Vector v(*this);
    for (unsigned int i = 0; i < data.size(); ++i) {
        v[i] = data[i] / m;
    }
    return v;
}

void Vector::resize(int n, double d) {
    data.resize(n, d);
}

void Vector::addBody(double x, double y, double z, double vx, double vy, double vz) {
    data.push_back(x);
    data.push_back(y);
    data.push_back(z);
    data.push_back(vx);
    data.push_back(vy);
    data.push_back(vz);
}

unsigned int Vector::size() const {
    return data.size();
}

void Vector::printOut(unsigned int i) const {
    printf("  <%e, %e, %e, %e, %e, %e>\n", data[i], data[i+1], data[i+2], data[i+3], data[i+4], data[i+5]);
}

void Vector::printOut() const {
    printf("[\n");
    for (unsigned int i = 0; i < data.size(); i += 6) {
        printf("  <%e, %e, %e, %e, %e, %e>\n", data[i], data[i+1], data[i+2], data[i+3], data[i+4], data[i+5]);
    }
    printf("]\n");
}