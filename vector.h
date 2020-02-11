#ifndef VECTOR_H_
#define VECTOR_H_

#include <vector>

class Vector
{
private:
    std::vector<double> data;
public:
    Vector operator*=(double h);
    Vector operator+=(Vector other);

    void addBody(double x, double y, double z, double vx, double vy, double vz);

    int size() const;

    void printOut(int i) const;
};

#endif
