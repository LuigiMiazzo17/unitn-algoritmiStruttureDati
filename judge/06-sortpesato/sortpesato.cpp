#include <climits>
#include <fstream>

using namespace std;

int *solve(const int *, int);

int main() {

  int L;
  ifstream in("input.txt");
  in >> L;
  int *arr = new int[L];
  for (int i = 0; i < L; i++)
    in >> arr[i];
  in.close();

  int *res = solve(arr, L);

  ofstream out("output.txt");
  out << res[0] << " " << res[1];
  out.close();
  delete[] res;

  return 0;
}

int *solve(const int *arr, int alen) {
  int *res = new int[2];
  res[0] = 0;
  res[1] = 0;

  bool *visited = new bool[alen];

  for (int i = 0; i < alen; i++)
    visited[i] = false;

  for (int i = 0; i < alen; i++) {
    if (arr[i] == i || visited[i])
      continue;
    int j = i;
    int len = 0;
    int sum = 0;
    int min = INT_MAX;
    while (!visited[j]) {
      len++;
      sum += arr[j];
      if (arr[j] < min)
        min = arr[j];
      visited[j] = true;
      j = arr[j] - 1;
    }
    if (len == 1)
      continue;
    res[0] += len - 1;

    int tmp = min * (len - 2) + sum;
    if (min == 1) {
      res[1] += tmp;
      continue;
    }
    int tmp2 = min + len + sum + 1;
    if (tmp < tmp2)
      res[1] += tmp;
    else
      res[1] += tmp2;
  }

  delete[] visited;
  return res;
}
