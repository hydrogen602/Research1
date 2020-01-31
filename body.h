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
    Body(double xArg, double yArg, double zArg, double vxArg, double vyArg, double vzArg);

    double distanceFrom(Body b);

    double distanceSquaredFrom(Body b);

    void integrate(double ax, double ay, double az);

    vect3 unitVectTo(Body b);
};

#endif
