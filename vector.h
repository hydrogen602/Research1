#ifndef VECTOR_H_
#define VECTOR_H_

#include <vector>
#include "header.h"

class Vector
{
private:
    std::vector<double> data;
public:
    Vector();
    Vector(int i);
    Vector(const Vector& src);

    Vector& operator*=(double h);
    Vector& operator+=(const Vector& other);
    double& operator[](unsigned int i);
    const double& operator[](unsigned int i) const;
    Vector& operator=(const Vector& other);
    Vector operator/(double h) const;

    void addBody(double x, double y, double z, double vx, double vy, double vz);

    unsigned int size() const;

    void resize(int n, double d);

    void printOut(unsigned int i) const;

    void printOut() const;
};

#endif
