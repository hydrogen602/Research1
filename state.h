#ifndef STATE_H_
#define STATE_H_
#include <vector>
#include "vector.h"

#define ERR_VECTOR_SIZE_MISMATCH 42
#define ERR_VECTOR_OUT_OF_BOUNDS 43

#define DEBUG 0

typedef struct vector3 {
    double x;
    double y;
    double z;
} vect3;

class State
{
private:
    Vector data;
    std::vector<double> masses; // in solar masses
    const double h;

    double computePotentialEnergy() const;

    double computeKineticEnergy() const;

public:    
    State(double hVal);

    void addBody(double x, double y, double z, double vx, double vy, double vz, double m);

    int size() const;

    void printOut() const;

    void derivative(Vector& d) const;

    void euler1();

    void kickStep1();

    void rk4();

    State operator+=(Vector delta);

    double computeEnergy() const;
};

#endif
