#include <iostream>

void printSol(const int *operazioni, const int m) {
  for (int i = 0; i < m - 1; i++)
    std::cout << operazioni[i] << "->";
  std::cout << operazioni[m - 1] << std::endl;
}

void mathWaysRec(int *operazioni, const int n, int k, int i) {
  if (n == k) {
    printSol(operazioni, i + 1);
    return;
  } else if (k > n) {
    return;
  }
  operazioni[i + 1] = k + 1;
  mathWaysRec(operazioni, n, k + 1, i + 1);
  operazioni[i + 1] = k * 2;
  mathWaysRec(operazioni, n, k * 2, i + 1);
  operazioni[i + 1] = k * k;
  mathWaysRec(operazioni, n, k * k, i + 1);
  return;
}

void mathWays(int n, int k) {
  int *operazioni = new int[n - k + 1];
  operazioni[0] = k;
  mathWaysRec(operazioni, n, k, 0);
  delete[] operazioni;
}

int main(int argc, char **argv) {
  if (argc != 3) {
    std::cout << "Usage: " << argv[0] << " <n> <k>" << std::endl;
    return 1;
  }
  int n = atoi(argv[1]);
  int k = atoi(argv[2]);
  if (n < 3 || k < 3) {
    std::cout << "n and k have to be >= 3" << std::endl;
    return 1;
  }
  if (n <= k) {
    std::cout << "n has to be >= k" << std::endl;
    return 1;
  }

  mathWays(n, k);
  return 0;
}
