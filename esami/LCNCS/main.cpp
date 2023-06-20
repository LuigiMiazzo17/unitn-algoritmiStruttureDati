#include <iostream>

int lcncs(const char *s1, const char *s2, int m, int n) {
  int **DP = new int *[m + 2];
  for (int i = 0; i < m + 2; i++)
    DP[i] = new int[n + 2];

  for (int i = 0; i < m; i++) {
    DP[i][0] = 0;
    DP[i][1] = 0;
  }
  for (int j = 0; j < n; j++) {
    DP[0][j] = 0;
    DP[1][j] = 0;
  }

  for (int i = 2; i < m + 2; i++) {
    for (int j = 2; j < n + 2; j++) {
      if (s1[i - 2] == s2[j - 2]) {
        DP[i][j] = 1 + DP[i - 2][j - 2];
      } else {
        DP[i][j] = std::max(DP[i - 1][j], DP[i][j - 1]);
      }
    }
  }

  int res = DP[m + 1][n + 1];
  for (int i = 0; i <= m + 2; i++)
    delete[] DP[i];
  delete[] DP;
  return res;
}

int main(int argc, char **argv) {
  if (argc != 3) {
    std::cout << "Usage: " << argv[0] << " <arg1> <arg2>" << std::endl;
    return 1;
  }
  std::cout << lcncs(argv[1], argv[2], strlen(argv[1]), strlen(argv[2]))
            << std::endl;
  return 0;
}
