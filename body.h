#ifndef body_H_
#define body_H_
#include <cmath>

#define ERR_VECTOR_SIZE_MISMATCH 42

typedef struct vector3 {
    double x;
    double y;
    double z;
} vect3;

typedef struct kDeltaVector {
    double dx;
    double dy;
    double dz;
    double dvx;
    double dvy;
    double dvz;
} kDelta; // d is delta, a small step in the simulation

class Body
{
private:

    double x;
    double y;
    double z;

    double vx;
    double vy;
    double vz;

public:
    const double mass; // in solar masses
    
    Body(double xArg, double yArg, double zArg, double vxArg, double vyArg, double vzArg, double m);

    Body(const Body& src);

    double distanceFrom(const Body &b) const;

    double distanceSquaredFrom(const Body &b) const;

    void integrate(const vect3 &acc, double h);

    void integrate(const kDelta &k, double factor);
    // factor is NOT h, it is something to multiply k by
    // as rk4 asks for things like yn + k1/2
    //  - here 1/2 is the factor

    vect3 getIntegratedVelocity(const vect3 &acc, double h) const;

    vect3 unitVectTo(const Body &b) const;

    void printOut() const;
};

#endif
