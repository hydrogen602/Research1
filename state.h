#ifndef STATE_H_
#define STATE_H_
#include <vector>
#include "vector.h"

#define ERR_VECTOR_SIZE_MISMATCH 42

#define DEBUG 1

class State
{
private:
    Vector data;
    std::vector<double> masses; // in solar masses
    const double h;

public:    
    State(double hVal);

    ~State();

    void addBody(double x, double y, double z, double vx, double vy, double vz, double m);

    int size() const;

    void printOut() const;

    void rk4();
};

#endif
