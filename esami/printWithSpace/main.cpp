#include <iostream>

void printSol(const char *str, const char *spaces, const int n) {
  for (int i = 0; i < n - 1; i++) {
    std::cout << str[i] << spaces[i];
  }
  std::cout << str[n - 1] << std::endl;
}

void printWithSpaceRec(const char *str, char *spaces, const int i,
                       const int n) {
  if (i + 1 == n) {
    printSol(str, spaces, n);
    return;
  }
  spaces[i] = 0;
  printWithSpaceRec(str, spaces, i + 1, n);
  spaces[i] = ' ';
  printWithSpaceRec(str, spaces, i + 1, n);
  return;
}

void printWithSpace(const char *str, const int n) {
  char *spaces = new char[n - 1];
  printWithSpaceRec(str, spaces, 0, n);
  delete[] spaces;
}

int main(int argc, char const **argv) {
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " <string>" << std::endl;
    return 1;
  }
  const char *str = argv[1];
  printWithSpace(str, strlen(str));
  return 0;
}
