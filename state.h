#ifndef STATE_H_
#define STATE_H_
#include <vector>
#include "vector.h"

#define ERR_VECTOR_SIZE_MISMATCH 42
#define ERR_VECTOR_OUT_OF_BOUNDS 43

#define DEBUG 0

const double kDefault = 1e10 * 10;

// deprecated
// 
// typedef struct vector3 { 
//     double x;
//     double y;
//     double z;
// } vect3;

class State
{
private:
    Vector data;
    std::vector<double> masses; // in solar masses
    std::vector<double> sizes;
    const double h;

    const double maxX;
    const double maxY;

    const double k;
    const double drag;

    double computePotentialEnergy() const;

    double computeKineticEnergy() const;

public:
    State(double hVal, double maxXArg, double maxYArg, double kArg, double dragCoeff);

    void addBody(double x, double y, double z, double vx, double vy, double vz, double m, double sz);

    void printOut() const;

    void derivative(Vector& d) const;

    void euler1();

    void kickStep1();

    void rk4();

    vector3 getPosition(int objNum) const;

    vector3 getVelocity(int objNum) const;

    double getSize(int objNum) const;

    double& operator[](unsigned int i);

    State operator+=(Vector delta);

    double computeEnergy() const;

    unsigned int size() const;
};

#endif
