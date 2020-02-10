#include <cmath>
#include <cstdio>
#include "body.h"
#include "kDeltaVector.h"

#define square(x) ((x) * (x))

Body::Body(vect3 &position, vect3 &velocity, double m): mass{m}, pos{position}, vel{velocity} {}

Body::Body(const Body& src): mass{src.mass}, pos{src.pos}, vel{src.vel} {
    #if DEBUG_COPY
        printf("copy\n");
    #endif
}

Body::Body(double xArg, double yArg, double zArg, double vxArg, double vyArg, double vzArg, double m): 
    mass{m}, pos{vect3{xArg, yArg, zArg}}, vel{vect3{vxArg, vyArg, vzArg}} {}

double Body::distanceFrom(const Body &b) const {
    // std::cout << square(b.x - x) << ' ';
    // std::cout << square(b.y - y) << ' ';
    // std::cout << square(b.z - z) << '\n';

    return sqrt(square(b.pos.x - pos.x) + square(b.pos.y - pos.y) + square(b.pos.z - pos.z));
}

double Body::distanceSquaredFrom(const Body &b) const {
    return square(b.pos.x - pos.x) + square(b.pos.y - pos.y) + square(b.pos.z - pos.z);
}

void Body::integrate(const vect3 &acc, double h) {
    // euler for now
    // deltaV = a * h 

    // printf("accVector = <%e, %e, %e> %e\n", acc.x, acc.y, acc.z, h);

    vel.x += acc.x * h;
    vel.y += acc.y * h;
    vel.z += acc.z * h;

    pos.x += vel.x * h;
    pos.y += vel.y * h;
    pos.z += vel.z * h;
}

void Body::integrate(const kDelta &k, double factor) {
    // factor is dimensionless - use only with rk4

    vel.x += k.dvx * factor;
    vel.y += k.dvy * factor;
    vel.z += k.dvz * factor;

    pos.x += k.dx * factor;
    pos.y += k.dy * factor;
    pos.z += k.dz * factor;
}

vect3 Body::getIntegratedPosition(const vect3 &dv, double h) const {
    return vect3{(vel.x + dv.x) * h, (vel.y + dv.y) * h, (vel.z + dv.z) * h};
}

vect3 Body::unitVectTo(const Body &b) const {
    double d = distanceFrom(b); // length of vector

    vect3 c;
    c.x = b.pos.x - pos.x;
    c.y = b.pos.y - pos.y;
    c.z = b.pos.z - pos.z;
    // now c is a vector pointing to b from this
    c.x /= d;
    c.y /= d;
    c.z /= d;
    return c;
}

void Body::printOut() const {
    printf("pos = <%e, %e, %e> v = <%e, %e, %e>\n", pos.x, pos.y, pos.z, vel.x, vel.y, vel.z);
}
