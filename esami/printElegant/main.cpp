#include <iostream>
#include <vector>

void printSol(const int *arr, const int n) {
  for (int i = 0; i < n; i++)
    std::cout << arr[i] << " ";
  std::cout << std::endl;
}

void printElegantRec(const int n, const int i, int *arr,
                     std::vector<int> available) {
  if (n == i) {
    printSol(arr, n);
    return;
  }
  for (int j = 0; j < available.size(); j++) {
    if (available[j] % (i + 1) == 0 || (i + 1) % available[j] == 0) {
      std::vector<int> newAvailable = available;
      newAvailable.erase(newAvailable.begin() + j);
      arr[i] = available[j];
      printElegantRec(n, i + 1, arr, newAvailable);
    }
  }
}

void printElegant(int n) {
  if (n == 0)
    return;
  int *arr = new int[n];
  std::vector<int> available;
  for (int i = 0; i < n; i++)
    available.push_back(i + 1);

  printElegantRec(n, 0, arr, available);

  delete[] arr;
  return;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " <n>" << std::endl;
    return 1;
  }
  int n = atoi(argv[1]);
  if (n <= 0) {
    std::cout << "n must be positive" << std::endl;
    return 1;
  }
  printElegant(n);
  return 0;
}
