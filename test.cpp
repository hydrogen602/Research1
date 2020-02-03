#include <iostream>

// test code help
int count = 0;
int failCount = 0;

bool compare(double a, double b) {
  double c = a - b;
  if (c < 0) {
    c = -c;
  };
  return (c < 0.0001);
}

void test(bool comparison) {
  count++;
  if (comparison) {
    std::cout << "Test " << count << " passed\n";
  } else {
    std::cout << "Test " << count << " failed\n";
    failCount++;
  }
}

void printResult() {
  std::cout << count - failCount << " tests out of " << count << " passed\n";
}
// end of test code help
