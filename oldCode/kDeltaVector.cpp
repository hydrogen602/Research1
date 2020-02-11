#include "kDeltaVector.h"
#include <cstdio>

kDeltaVector::kDeltaVector(double deltaX, double deltaY, double deltaZ, double deltaVX, double deltaVY, double deltaVZ):
  dx{deltaX}, dy{deltaY}, dz{deltaZ}, dvx{deltaVX}, dvy{deltaVY}, dvz{deltaVZ} {}

kDeltaVector kDeltaVector::operator+(const kDeltaVector &other) const {
  return kDeltaVector(dx + other.dx, dy + other.dy, dz + other.dz, dvx + other.dvx, dvy + other.dvy, dvz + other.dvz);
}

kDeltaVector kDeltaVector::operator*(double d) const {
  return kDeltaVector(dx * d, dy * d, dz * d, dvx * d, dvy * d, dvz * d);
}

kDeltaVector& kDeltaVector::operator+=(const kDeltaVector &other) {
  dx += other.dx;
  dy += other.dy;
  dz += other.dz;
  dvx += other.dvx;
  dvy += other.dvy;
  dvz += other.dvz;
  return *this;
}

void kDeltaVector::printOut() const {
  #if DEBUG
    printf("dx = <%e, %e, %e> dv = <%e, %e, %e>\n", dx, dy, dz, dvx, dvy, dvz);
  #endif
}