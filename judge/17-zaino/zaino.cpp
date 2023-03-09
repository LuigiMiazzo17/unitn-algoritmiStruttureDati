#include <climits>
#include <fstream>
#include <iostream>
#include <utility>
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

  int C, N;
  cin >> C >> N;

  std::vector<std::pair<int, __uint16_t>> weights;
  std::vector<__uint16_t> prevRow;
  std::vector<__uint16_t> currRow;
  for (int i = 0; i < N; i++) {
    int w;
    __uint16_t v;
    cin >> w >> v;
    weights.push_back(std::make_pair(w, v));
  }

  for (int i = 0; i <= C; i++) {
    prevRow.push_back(0);
    currRow.push_back(0);
  }

#ifndef LOCAL
  cin.close();
#endif

  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= C; j++) {
      if (weights[i - 1].first <= j) {
        __int16_t a = prevRow[j - weights[i - 1].first] + weights[i - 1].second;
        __int16_t b = prevRow[j];
        if (a > b)
          currRow[j] = a;
        else
          currRow[j] = b;
      } else
        currRow[j] = prevRow[j];
    }
    prevRow = currRow;
  }
  cout << currRow[C];

#ifndef LOCAL
  cout.close();
#endif

  return 0;
}
