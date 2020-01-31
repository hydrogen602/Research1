#include <iostream>
#include <vector>
#include <cmath>
#include "body.h"

void findAcceleration(std::vector<Body> system) {
    for (int i = 0; i < system.size(); ++i) {
        for (int j = 0; j < system.size(); ++j) {
            if (i != j) {
                double dSq = system[i].distanceSquaredFrom(system[j]);
                // a = g * m / r^2
                // r^2 = d
                // g = 1
                // m = 1 solar mass

                double aScalar = 1.0 / dSq;
                double d = sqrt(dSq);
                
            }
        } 
    }
}

int main(void) {
    std::vector<Body> sys;

    sys.push_back(Body{-1, 0, 0, 0, 0, 0});
    sys.push_back(Body{0, 1, 0, 0, 0, 0});

    std::cout << "N-body simulation\n";
    std::cout << "Number of bodies: " << sys.size() << '\n';

    double d = sys[0].distanceFrom(sys[1]);
    std::cout << "Distance test: " << d << '\n';

    d = sys[0].distanceSquaredFrom(sys[1]);
    std::cout << "Distance squared test: " << d << '\n';

    return 0;
}