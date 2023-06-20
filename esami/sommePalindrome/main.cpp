#include <iostream>

int countSumEven(int n) {
  int *DP = new int[n + 1];
  DP[0] = 1;
  for (int i = 2; i <= n; i += 2) {
    DP[i] = 0;
    for (int j = 1; j <= (i / 2); j++)
      DP[i] = DP[i] + DP[i - 2 * j];
  }
  int res = DP[n];
  delete[] DP;
  return res;
}

int main(int argc, char const **argv) {
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " <n>" << std::endl;
    return 1;
  }
  int n = atoi(argv[1]);
  if (n < 0 || n % 2 == 1) {
    std::cout << "n must be positive and even" << std::endl;
    return 1;
  }
  std::cout << countSumEven(n) << std::endl;
  return 0;
}
