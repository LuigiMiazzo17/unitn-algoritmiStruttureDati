#include <iostream>
#include <vector>

typedef std::vector<int> iv;
typedef std::vector<std::vector<int>> matrix;

int main() {
  const matrix M = {
      {6, 7, 4, 7, 8}, {7, 6, 1, 1, 4}, {3, 5, 7, 8, 2},
      {2, 6, 7, 0, 2}, {7, 3, 5, 6, 1},
  };
  int r = M.size();
  int c = M[0].size();
  matrix DP;

  for (int i = 0; i < r; i++) {
    iv dprow(c);
    DP.push_back(dprow);
    DP[0][i] = M[0][i];
  }

  for (int i = 1; i < r; i++) {
    for (int j = 0; j < c; j++) {
      DP[i][j] =
          M[i][j] +
          std::max(DP[i - 1][j], std::max((j == 0 ? 0 : DP[i - 1][j - 1]),
                                          (j == c - 1 ? 0 : DP[i - 1][j + 1])));
    }
  }

  int max = 0;
  for (int i = 0; i < c; i++)
    max = std::max(max, DP[r - 1][i]);

  std::cout << max << std::endl;
  return 0;
}
