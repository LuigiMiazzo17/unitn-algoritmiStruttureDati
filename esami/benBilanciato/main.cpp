#include <iostream>

long countWellBalancedRec(long *DP, int n) {
  if (n == 1)
    return 1;
  if (DP[n] != -1)
    return DP[n];

  if (n % 2 == 0) {
    DP[n] = 2 * countWellBalancedRec(DP, (int)(n / 2)) *
            countWellBalancedRec(DP, (int)(n / 2) - 1);
    return DP[n];
  } else
    return DP[n] = countWellBalancedRec(DP, (int)(n / 2)) *
                   countWellBalancedRec(DP, (int)(n / 2));
}

long countWellBalanced(int n) {
  long *DP = new long[n + 1];
  DP[0] = 1;
  long nextPower = 1;
  for (int i = 2; i < n + 1; i++) {
    if (nextPower == i) {
      nextPower *= 2;
      DP[i] = i;
    } else
      DP[i] = -1;
  }
  long res = countWellBalancedRec(DP, n);
  delete[] DP;
  return res;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " <n>" << std::endl;
    return 1;
  }
  int n = atoi(argv[1]);
  if (n < 1) {
    std::cout << "n must be greater than 0" << std::endl;
    return 1;
  }
  std::cout << countWellBalanced(n) << std::endl;
  return 0;
}
