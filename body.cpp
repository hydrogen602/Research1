#include <cmath>
#include <cstdio>
#include "body.h"

#define square(x) ((x) * (x))

Body::Body(double xArg, double yArg, double zArg, double vxArg, double vyArg, double vzArg, double m): mass{m} {
    x = xArg;
    y = yArg;
    z = zArg;
    vx = vxArg;
    vy = vyArg;
    vz = vzArg;
}

double Body::distanceFrom(const Body &b) const {
    // std::cout << square(b.x - x) << ' ';
    // std::cout << square(b.y - y) << ' ';
    // std::cout << square(b.z - z) << '\n';

    return sqrt(square(b.x - x) + square(b.y - y) + square(b.z - z));
}

double Body::distanceSquaredFrom(const Body &b) const {
    return square(b.x - x) + square(b.y - y) + square(b.z - z);
}

void Body::integrate(const vect3 &acc, double h) {
    // euler for now
    // deltaV = a * h 

    printf("accVector = <%e, %e, %e> %e\n", acc.x, acc.y, acc.z, h);

    vx += acc.x * h;
    vy += acc.y * h;
    vz += acc.z * h;

    x += vx * h;
    y += vy * h;
    z += vz * h;
}

vect3 Body::unitVectTo(const Body &b) const {
    double d = distanceFrom(b); // length of vector

    vect3 c;
    c.x = b.x - x;
    c.y = b.y - y;
    c.z = b.z - z;
    // now c is a vector pointing to b from this
    c.x /= d;
    c.y /= d;
    c.z /= d;
    return c;
}

void Body::printOut() const {
    printf("pos = <%e, %e, %e> v = <%e, %e, %e>\n", x, y, z, vx, vy, vz);
}
