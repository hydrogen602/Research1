#include <cmath>
#include <iostream>
#include "body.h"

#define square(x) ((x) * (x))

Body::Body(double xArg, double yArg, double zArg, double vxArg, double vyArg, double vzArg) {
    x = xArg;
    y = yArg;
    z = zArg;
    vx = vxArg;
    vy = vyArg;
    vz = vzArg;
}

double Body::distanceFrom(Body b) {
    // std::cout << square(b.x - x) << ' ';
    // std::cout << square(b.y - y) << ' ';
    // std::cout << square(b.z - z) << '\n';

    return sqrt(square(b.x - x) + square(b.y - y) + square(b.z - z));
}

double Body::distanceSquaredFrom(Body b) {
    return square(b.x - x) + square(b.y - y) + square(b.z - z);
}

void Body::integrate(double ax, double ay, double az) {
    // euler for now
    double h = 0.1;

    // deltaV = a * h 

    vx += ax * h;
    vy += ay * h;
    vz += az * h;
}

vect3 Body::unitVectTo(Body b) {
    vect3 c;
    v.x = b
}

