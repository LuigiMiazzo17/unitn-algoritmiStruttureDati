#include <cmath>
#include <iostream>

int mathWays(const int n, const int k) {
  int *DP = new int[n - k + 1];
  DP[0] = 1;
  int lastRoot = k;
  int squareTrigger = k * k;
  for (int i = k + 1; i <= n; i++) {
    DP[i - k] = DP[i - k - 1];
    int halfs = (int)(i / 2);
    bool isEven = i % 2 == 0;
    if (isEven && halfs >= k)
      DP[i - k] += DP[halfs - k];

    if (squareTrigger == i) {
      DP[i - k] += DP[lastRoot - k];
      lastRoot++;
      squareTrigger = lastRoot * lastRoot;
    }
  }
  int res = DP[n - k];
  delete[] DP;
  return res;
}

int main(int argc, char **argv) {
  if (argc != 3) {
    std::cout << "Usage: " << argv[0] << " <n> <k>" << std::endl;
    return 1;
  }
  int n = atoi(argv[1]);
  int k = atoi(argv[2]);
  if (n < 1 || k < 0 || k > n) {
    std::cout << "Invalid input" << std::endl;
    return 1;
  }
  std::cout << mathWays(n, k) << std::endl;
  return 0;
}
