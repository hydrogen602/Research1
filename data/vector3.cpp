#include "vector3.h"

vector3::vector3(double arg_x, double arg_y, double arg_z): x{arg_x}, y{arg_y}, z{arg_z} {}

vector3::vector3(const vector3& copySrc): x{copySrc.x}, y{copySrc.y}, z{copySrc.z} {}

vector3 vector3::operator+(const vector3& other) const {
    return vector3(x + other.x, y + other.y, z + other.z);
}

vector3& vector3::operator+=(const vector3& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *(this);
}

vector3 vector3::operator-(const vector3& other) const {
    return vector3(x - other.x, y - other.y, z - other.z);
}

vector3& vector3::operator-=(const vector3& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *(this);
}

vector3 vector3::operator*(const double d) const {
    return vector3(x * d, y * d, z * d);
}

vector3& vector3::operator*=(const double d) {
    x *= d;
    y *= d;
    z *= d;
    return *(this);
}

double vector3::dot(const vector3& d) const {
    return x * d.x + y * d.y + z * d.z;
}

vector3 vector3::operator/(const double d) const {
    return vector3(x / d, y / d, z / d);
}

vector3& vector3::operator/=(const double d) {
    x /= d;
    y /= d;
    z /= d;
    return *(this);
}