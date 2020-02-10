#ifndef kDeltaVector_H_
#define kDeltaVector_H_

#define DEBUG 1
#define DEBUG_COPY 0

class kDeltaVector {
public:
  double dx;
  double dy;
  double dz;
  double dvx;
  double dvy;
  double dvz;

  kDeltaVector(double deltaX, double deltaY, double deltaZ, double deltaVX, double deltaVY, double deltaVZ);

  kDeltaVector operator+(const kDeltaVector &other) const;

  kDeltaVector& operator+=(const kDeltaVector &other);

  kDeltaVector operator*(double d) const;

  void printOut() const;
};
// d is delta, a small step in the simulation

typedef kDeltaVector kDelta;

#endif
