#ifndef VECT3_H_
#define VECT3_H_

class vector3 {
public:
    double x;
    double y;
    double z;
    
    vector3(double arg_x, double arg_y, double arg_z);

    vector3(const vector3& copySrc);

    vector3 operator+(const vector3& other) const;
    vector3& operator+=(const vector3& other);

    vector3 operator-(const vector3& other) const;
    vector3& operator-=(const vector3& other);

    vector3 operator*(const double d) const;
    vector3& operator*=(const double d);

    double dot(const vector3& d) const;

    vector3 operator/(const double d) const;
    vector3& operator/=(const double d);
};

#endif