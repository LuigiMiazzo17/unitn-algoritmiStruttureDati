#include <iostream>

void printSol(const int *sol, int n) {
  for (int i = 0; i < n; i++) {
    std::cout << sol[i];
  }
  std::cout << std::endl;
}

void printOctalsRec(int *sol, int n, int j) {
  if (j == n) {
    printSol(sol, n);
    return;
  }
  for (int i = 0; i < 8; i++) {
    if (sol[j - 1] != i) {
      sol[j] = i;
      printOctalsRec(sol, n, j + 1);
    }
  }
}

void printOctals(int n) {
  int *sol = new int[n];
  for (int i = 0; i < 8; i++) {
    sol[0] = i;
    printOctalsRec(sol, n, 1);
  }
  delete[] sol;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " <n>" << std::endl;
    return 1;
  }
  int n = atoi(argv[1]);
  if (n < 1) {
    std::cout << "n must be greater than 0" << std::endl;
    return 1;
  }
  printOctals(n);
  return 0;
}
