#include <iostream>

int discordVille(int *D, const int *N, const int n) {
  for (int i = 1; i < n; i++) {
    if (i - N[i] - 1 >= 0)
      D[i] = std::max(D[i - 1], D[i - N[i] - 1] + D[i]);
    else
      D[i] = std::max(D[i - 1], D[i]);
  }
  return D[n - 1];
}

int main(void) {
  int n = 5;
  int D[] = {3, 4, 5, 7, 1};
  int N[] = {0, 1, 1, 3, 1};
  std::cout << discordVille(D, N, n) << std::endl;
}
