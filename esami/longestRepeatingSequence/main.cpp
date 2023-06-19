#include <iostream>

int lrs(const char *str, int n) {
  int **DP = new int *[n];
  DP[0] = new int[n];
  DP[0][0] = 0;
  for (int i = 1; i < n; i++) {
    DP[i] = new int[n];
    DP[0][i] = 0;
    if (str[i] == str[0]) {
      DP[0][i] = 1;
    }
  }

  for (int i = 1; i < n; i++) {
    for (int j = i; j < n; j++) {
      if (str[i] == str[j] && i != j) {
        DP[i][j] = DP[i - 1][j - 1] + 1;
      } else {
        DP[i][j] = std::max(DP[i - 1][j], DP[i][j - 1]);
      }
    }
  }

  int res = DP[n - 1][n - 1];
  for (int i = 0; i < n; i++)
    delete[] DP[i];
  delete[] DP;
  return res;
}

int main(int atgc, char **argv) {
  if (atgc != 2) {
    std::cout << "Usage: " << argv[0] << " <string>" << std::endl;
    return 1;
  }
  std::cout << lrs(argv[1], strlen(argv[1])) << std::endl;
  return 0;
}
