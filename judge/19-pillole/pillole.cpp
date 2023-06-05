#include <fstream>
#include <iostream>
#include <vector>

#ifndef LOCAL
std::ifstream _in("input.txt");
std::ofstream _out("output.txt");
#define cin _in
#define cout _out
#else
#define cin std::cin
#define cout std::cout
#endif

int main() {

  int16_t N;
  cin >> N;

#ifndef LOCAL
  cin.close();
#endif

  std::vector<std::vector<uint64_t>> DP;

  for (uint8_t i = 0; i <= N; i++) {
    std::vector<uint64_t> tmp;
    for (int8_t j = 0; j <= N; j++)
      tmp.push_back(0);
    DP.push_back(tmp);
  }

  for (int8_t i = 1; i <= N; i++)
    DP[0][i] = 1;

  int8_t m = N;
  for (int8_t k = 1; k <= N; k++) {
    DP[k][0] = DP[k - 1][1];

    for (int8_t j = 1; j < m; j++)
      DP[k][j] = DP[k][j - 1] + DP[k - 1][j + 1];
    m--;
  }

  cout << DP[N][0];

#ifndef LOCAL
  cout.close();
#endif

  return 0;
}
