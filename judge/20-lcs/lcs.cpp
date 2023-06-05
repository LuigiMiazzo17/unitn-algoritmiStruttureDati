#include <climits>
#include <cstring>
#include <fstream>
#include <iostream>

#ifndef LOCAL
std::ifstream _in("input.txt");
std::ofstream _out("output.txt");
#define cin _in
#define cout _out
#else
#define cin std::cin
#define cout std::cout
#endif

uint16_t **DP;
uint16_t l1, l2;

uint16_t fun(const char *s1, const char *s2, uint16_t i, uint16_t j) {
  if (i >= l1 || j >= l2)
    return 0;

  if (DP[i][j] != UINT16_MAX)
    return DP[i][j];

  uint16_t tmp = 0;
  for (uint16_t k = j; k < l2; k++) {
    if (s1[i] == s2[k]) {
      tmp = fun(s1, s2, i + 1, k + 1) + 1;
      break;
    }
  }

  return DP[i][j] = std::max(tmp, fun(s1, s2, i + 1, j));
}

int main(void) {

  char s1[1000];
  char s2[1000];

  cin >> s1 >> s2;

#ifndef LOCAL
  cin.close();
#endif

  l1 = std::strlen(s1);
  l2 = std::strlen(s2);

  DP = new uint16_t *[l1];

  for (int i = 0; i < l1; i++) {
    uint16_t *tmp = new uint16_t[l2];
    for (int j = 0; j < l2; j++)
      tmp[j] = UINT16_MAX;
    DP[i] = tmp;
  }

  cout << fun(s1, s2, 0, 0);

#ifndef LOCAL
  cout.close();
#endif

  for (uint16_t i = 0; i < l1; i++)
    free(DP[i]);
  free(DP);

  return 0;
}
