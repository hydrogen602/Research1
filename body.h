#ifndef body_H_
#define body_H_
#include <cmath>

typedef struct vector3 {
    double x;
    double y;
    double z;
} vect3;

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

    double distanceFrom(const Body &b) const;

    double distanceSquaredFrom(const Body &b) const;

    void integrate(const vect3 &acc, double h);

    vect3 unitVectTo(const Body &b) const;

    void printOut() const;
};

#endif
