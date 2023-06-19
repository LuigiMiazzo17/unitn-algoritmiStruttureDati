#include <iostream>

int countSRec(int **DP, int i, int j, int m) {
  if (i == 0 && j <= m)
    return 1;
  if (i < 0)
    return 0;
  if (DP[i][j] != -1)
    return DP[i][j];
  int sum = 0;
  int k = 0;
  while (j * 2 + k <= m) {
    sum += countSRec(DP, i - 1, j * 2 + k, m);
    k++;
  }
  DP[i][j] = sum;
  return sum;
}

int countSequences(const int n, const int m) {
  int **DP = new int *[n];

  for (int i = 0; i < n; i++) {
    DP[i] = new int[m];
    for (int j = 0; j < m; j++)
      DP[i][j] = -1;
  }

  int res = countSRec(DP, n - 1, 1, m);

  for (int i = 0; i < n; i++)
    delete[] DP[i];
  delete[] DP;
  return res;
}

int main(int argc, char **argv) {
  if (argc != 3) {
    std::cout << "Usage: " << argv[0] << " <n> <m>" << std::endl;
    return 1;
  }
  int n = atoi(argv[1]);
  int m = atoi(argv[2]);
  if (n < 0 || m < 0) {
    std::cout << "n and m must be positive" << std::endl;
    return 1;
  }
  std::cout << countSequences(n, m) << std::endl;
  return 0;
}
