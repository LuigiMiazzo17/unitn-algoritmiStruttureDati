#include <iostream>

void printSol(const char *str, const int n) {
  for (int i = 0; i < n; i++) {
    std::cout << str[i];
  }
  std::cout << std::endl;
}

void binaryRec(char *str, const int n, int i, const int n0, int s0,
               const int n1, int s1) {
  if (i == n) {
    printSol(str, n);
    return;
  }
  if (s0 < n0) {
    str[i] = '0';
    binaryRec(str, n, i + 1, n0, s0 + 1, n1, 0);
  }
  if (s1 < n1) {
    str[i] = '1';
    binaryRec(str, n, i + 1, n0, 0, n1, s1 + 1);
  }
}

void binary(const int n, const int n0, const int n1) {
  char *str = new char[n];
  binaryRec(str, n, 0, n0, 0, n1, 0);
  delete[] str;
}

int main(int argc, char **argv) {
  if (argc != 4) {
    std::cerr << "Usage: <n> <n0> <n1>" << argv[0] << std::endl;
    return 1;
  }
  int n = atoi(argv[1]);
  int n0 = atoi(argv[2]);
  int n1 = atoi(argv[3]);

  binary(n, n0, n1);
  return 0;
}
