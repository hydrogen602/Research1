#include <vector>
#include <iostream>
#include <cstdio>
#include "state.h"

State::State(double hVal): h{hVal} {}

State::~State() {}

void State::addBody(double x, double y, double z, double vx, double vy, double vz, double m) {
  data.addBody(x, y, z, vx, vy, vz);

  masses.push_back(m);

  if (masses.size() * 6 != data.size()) {
    throw ERR_VECTOR_SIZE_MISMATCH;
  }
}

int State::size() const {
  return masses.size();
}

void State::printOut() const {
  std::cout << "[\n";
  for (int i = 0; i < data.size(); i += 6) {
    printf("  ");
    data.printOut(i);
  }
  std::cout << "]\n";
}

void State::rk4() {
    /*
     * Runge-Kutta
     * 
     * y' = F(x, y)
     * 
     * y_n+1 = y_n + 1/6 * (k1 + 2k2 + 3k3 + k4) + O(h^5)
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

    Vector k1;
}

void testGroup1() {
    double h = 1e-3;
    State sys(h);

    sys.addBody(0, 0, 0, 0, 0, 0, 1);
    sys.addBody(1, 0, 0, 0, 1, 0, 1e-8);

    sys.printOut();
}

void testGroup3_RK4() {
    double h = 1e-3;
    State sys(h);

    sys.addBody(0, 0, 0, 0, 0, 0, 1);
    sys.addBody(1, 0, 0, 0, 1, 0, 1e-8);

    std::cerr << "N-body simulation\n";
    std::cerr << "Number of bodies: " << sys.size() << '\n';

    for (double i = 0; i < 3.141592653589793; i += h) {
        #if DEBUG
        std::cout << "i = " << i << "\n";
        #endif

        sys.rk4();


        #if DEBUG
        sys.printOut();
        #endif
    }

    std::cout << "Final Result:\n";
    sys.printOut();
}

int main() {
  std::cerr << "Starting...\n";
  testGroup1();
  std::cerr << "Done\n";
  return 0;
}
