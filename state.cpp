#include <vector>
#include <iostream>
#include <cstdio>
#include <cmath>
#include "state.h"
#include "data/vector3.h"

#define square(x) ((x) * (x))

State::State(double hVal, double maxXArg, double maxYArg): h{hVal}, maxX{maxXArg}, maxY{maxYArg} {
    std::cerr << "maxX = " << maxX << "; maxY = " << maxY << '\n';
}

void State::addBody(double x, double y, double z, double vx, double vy, double vz, double m, double sz) {
  data.addBody(x, y, z, vx, vy, vz);

  masses.push_back(m);

  sizes.push_back(sz);

  if (masses.size() * 6 != data.size() || masses.size() != sizes.size()) {
    throw ERR_VECTOR_SIZE_MISMATCH;
  }
}

unsigned int State::size() const {
  return masses.size();
}

void State::printOut() const {
  std::cout << "[\n";
  for (unsigned int i = 0; i < data.size(); i += 6) {
    printf("  ");
    data.printOut(i);
  }
  std::cout << "]\n";
}

double State::computeKineticEnergy() const {
    //  1/2 m v^2
    double energy = 0;
    
    for (unsigned int i = 0; i < data.size(); i += 6) {
        // v^2 = vx^2 + vy^2 + vz^2

        double vSq = square(data[i + 3]) + square(data[i + 4]) + square(data[i + 5]);
        energy += 0.5 * masses[i / 6] * vSq;
        //printf("KE[%d] = %e\n", i / 6, 0.5 * masses[i / 6] * vSq);
    }

    //printf("K = %e\n", energy);
    return energy;
}

double State::computePotentialEnergy() const {
    // -G (mM) / R
    double energy = 0;

    for (unsigned int i = 0; i < data.size(); i += 6)
    {
        for (unsigned int j = i + 6; j < data.size(); j += 6)
        {
            // compute R
            double dSq = square(data[i] - data[j]) + square(data[i+1] - data[j+1]) + square(data[i+2] - data[j+2]);
            double r = sqrt(dSq);

            // G is 1
            energy += - (masses[i / 6] * masses[j / 6] / r);

            //printf("PE[%d] on [%d] = %e\n", i / 6, j / 6, - (masses[i / 6] * masses[j / 6] / r));
        }
        
    }
    //printf("U = %e\n", energy);
    return energy;
}

double State::computeEnergy() const {
    return computeKineticEnergy() + computePotentialEnergy();
}

void State::derivative(Vector& d) const {
    if (d.size() != data.size()) {
        d.resize(data.size(), 0);
    }

    /*  [ x  ]      [ vx ]
     *  [ y  ]      [ vy ]
     *  [ z  ]  ==> [ vz ]
     *  [ vx ]  ==> [ ax ]
     *  [ vy ]      [ ay ]
     *  [ vz ]      [ az ]
     */

    for (unsigned int i = 0; i < data.size(); i += 6) {
        d[i + 0] = data[i + 3];
        d[i + 1] = data[i + 4];
        d[i + 2] = data[i + 5];

        // find acceleration

        vector3 accVector(0, 0, 0);

        for (unsigned int j = 0; j < data.size(); j += 6) {
            if (i != j) {
                double dSq = square(data[i] - data[j]) + square(data[i+1] - data[j+1]) + square(data[i+2] - data[j+2]);
                // a = g * m / r^2
                // g = 1
                // m = in solar masses

                double accScalar = masses[j / 6] / dSq; // magnitude of a

                // vect3 dirUnitVec = system[i].unitVectTo(system[j]); // dir of a

                double d = sqrt(dSq); // length of vector
                // and distance between objects

                vector3 c(data[j] - data[i], data[j+1] - data[i+1], data[j+2] - data[i+2]);
                // now c is a vector pointing to b from this
                c /= d;
                // c is displacement unit vector

                vector3 acc = c; // make a copy

                // c is now a unit vector pointing to object j

                acc *= accScalar;

                //fprintf(stderr, "<%e, %e, %e>\n", acc.x, acc.y, acc.z);

                accVector += acc;
                // i and j forces get calculated twice

                // deal with collisions
                double deltaX = d - (sizes[j / 6] + sizes[i / 6]);
                if (deltaX < 0) {
                    // intersection!

                    std::cerr << "intersection " << fabs(deltaX / (sizes[j / 6] + sizes[i / 6])) * 100 << "%\n";

                    double dissipative = 1e3;

                    vector3 vI = {data[i+3], data[i+4], data[i+5]};
                    vector3 vJ = {data[j+3], data[j+4], data[j+5]};

                    vector3 rel = vJ - vI;

                    double vMag = rel.dot(c);

                    // in dir -c (away from other object)
                    double a = (-k * -deltaX + dissipative * vMag) / masses[i / 6];
                    

                    accVector += (c * a);

                    //fprintf(stderr, "object %d\n", i);
                    //fprintf(stderr, "deltaX = %e\n", deltaX);
                    //fprintf(stderr, "<%e, %e, %e>\n", c.x, c.y, c.z);
                    //fprintf(stderr, "<%e, %e, %e>\n", accVector.x, accVector.y, accVector.z);
                }
            }
        }

        // accVector is acceleration

        d[i + 3] = accVector.x;
        d[i + 4] = accVector.y;
        d[i + 5] = accVector.z;
    }
}

void State::euler1() {
    // y_n+1 = y_n + k
    // k = h * F(x, y)

    Vector k;
    derivative(k);
    k *= h;

    // advance
    (*this) += k;
}

void State::kickStep1() {
    // first integrate acc to vel, then vel to position
    
    Vector k;
    derivative(k);
    
    // kick
    for (unsigned int i = 0; i < data.size(); i += 6) {
        k[i + 0] += k[i + 3] * h;
        k[i + 1] += k[i + 4] * h;
        k[i + 2] += k[i + 5] * h;
    }

    // step
    k *= h;
    (*this) += k;
}

void State::rk4() {
    /*
     * Runge-Kutta
     * 
     * y' = F(x, y)
     * 
     * y_n+1 = y_n + 1/6 * (k1 + 2k2 + 2k3 + k4) + O(h^5)
     * 
     * k1 = hF(xn, yn)
     * k2 = hF(xn + h/2, yn + k1/2)
     * k3 = hF(xn + h/2, yn + k2/2)
     * k4 = hF(xn + h, yn + k3)
     * 
     * y is position & velocity
     * y' is velocity & acceleration
     * 
     * idk what to do with x for now
     */

    Vector oldState(data);

    // k1 = hF(xn, yn)
    Vector k1;
    derivative(k1);
    k1 *= h;

    // k2 = hF(xn + h/2, yn + k1/2)
    (*this) += k1 / 2;

    Vector k2;
    derivative(k2);
    k2 *= h;

    data = oldState;
    // k3 = hF(xn + h/2, yn + k2/2)
    
    (*this) += k2 / 2;

    Vector k3;
    derivative(k3);
    k3 *= h;

    data = oldState;
    // k4 = hF(xn + h, yn + k3)

    (*this) += k3;

    Vector k4;
    derivative(k4);
    k4 *= h;

    data = oldState;
    // 1/6 * (k1 + 2k2 + 2k3 + k4)

    Vector K(data.size());

    K += k1;

    k2 *= 2;
    K += k2;

    k3 *= 2;
    K += k3;

    K += k4;

    K *= 1.0/6;

    (*this) += K;

}

double& State::operator[](unsigned int i) {
    return data[i];
}

State State::operator+=(Vector delta) {
    if (data.size() != delta.size()) {
        throw ERR_VECTOR_SIZE_MISMATCH;
    }

    // boundary conditions!

    for (unsigned int i = 0; i < data.size(); i += 6) {
        data[i] += delta[i];
        data[i + 1] += delta[i + 1];
        data[i + 2] += delta[i + 2];
        data[i + 3] += delta[i + 3];
        data[i + 4] += delta[i + 4];
        data[i + 5] += delta[i + 5];

        // if (data[i] < -maxX || data[i] > maxX) {
        //     data[i] *= -1;
        //     std::cerr << "flipped\n";
        // }

        // if (data[i + 1] < -maxY || data[i + 1] > maxY) {
        //     data[i + 1] *= -1;
        // }
    }

    return *this;
}
