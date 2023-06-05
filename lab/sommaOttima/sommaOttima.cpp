#include <iostream>
#include <vector>

int solve(const std::vector<int> &V, const std::vector<int> &x, int index,
          int W) {
  if (index == V.size())
    return 0;
  int a = 0;
  if (V[index] * x[index] < W) {
    std::vector<int> x_copy(x);
    ++x_copy[index];
    a = V[index] + solve(V, x_copy, index, W - V[index]);
  }
  int b = solve(V, x, index + 1, W);
  return std::max(a, b);
}

int main() {
  std::vector<int> V = {18, 3, 21, 9, 12, 24};
  std::vector<int> x(V.size(), 0);
  std::cout << solve(V, x, 0, 17) << std::endl;

  return 0;
}
