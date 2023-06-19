#include <climits>
#include <iostream>

int minProduct(const int *A, const int n) {
  int res = 1;
  int min = INT_MAX;
  int maxNegN = INT_MIN;

  for (int i = 0; i < n; i++) {
    if (A[i] < min)
      min = A[i];
    if (A[i] < 0 && A[i] > maxNegN)
      maxNegN = A[i];
    if (A[i] != 0)
      res *= A[i];
  }

  if (res > 0) {
    if (maxNegN != INT_MIN)
      return (int)(res / maxNegN);
    return min;
  }
  return res;
}

int main(void) {
  int a[] = {1, 2, -2, 3, -4, 0, 4, 5};
  int n = sizeof(a) / sizeof(a[0]);
  std::cout << minProduct(a, n) << std::endl;
  return 0;
}
