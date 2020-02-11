#ifndef STATE_H_
#define STATE_H_
#include <vector>

#define ERR_VECTOR_SIZE_MISMATCH 42

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

class Vector
{
private:
    std::vector<double> data;
public:
    Vector operator*=(double h);
    Vector operator+=(Vector other);

    void addBody(double x, double y, double z, double vx, double vy, double vz);

    int size() const;

    void printOut(int i) const;
};

#endif
