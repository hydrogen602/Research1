#ifndef VECTOR_H_
#define VECTOR_H_

#include <vector>

class Vector
{
private:
    std::vector<double> data;
public:
    Vector();
    Vector(int i);
    Vector(Vector& src);

    Vector& operator*=(double h);
    Vector& operator+=(const Vector& other);
    double& operator[](int i);
    Vector& operator=(const Vector& other);

    void addBody(double x, double y, double z, double vx, double vy, double vz);

    int size() const;

    void resize(int n, double d);

    void printOut(int i) const;

    void printOut() const;
};

#endif
