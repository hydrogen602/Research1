#ifndef body_H_
#define body_H_
#include <cmath>
#include "kDeltaVector.h"

#define ERR_VECTOR_SIZE_MISMATCH 42

typedef struct vector3 {
    double x;
    double y;
    double z;
} vect3;

class Body
{
private:
    vect3 pos;
    vect3 vel;

public:
    const double mass; // in solar masses
    
    Body(vect3 &position, vect3 &velocity, double m);

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
