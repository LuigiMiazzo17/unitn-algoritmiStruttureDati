#include <fstream>

using namespace std;

int *mergeSort(int *, int, int);
int *merge(int *, int *, int, int, int);

int main() {

  ifstream in("input.txt");
  int L;
  in >> L;
  int *a = new int[L];
  for (int i = 0; i < L; i++)
    in >> a[i];
  in.close();

  a = mergeSort(a, 0, L);

  ofstream out("output.txt");

  for (int i = 0; i < L; i++)
    out << a[i] << " ";

  delete[] a;
  out.close();
  return 0;
}

int *mergeSort(int *a, int s, int f) {

  int l = f - s;
  int f1 = s + l / 2;

  if (l == 2) {
    int *r = new int[2];
    if (a[s] < a[s + 1]) {
      r[0] = a[s];
      r[1] = a[s + 1];
    } else {
      r[0] = a[s + 1];
      r[1] = a[s];
    }
    return r;
  } else if (l == 1) {
    int *r = new int[1];
    r[0] = a[s];
    return r;
  }
  int *a1 = mergeSort(a, s, f1);
  int *a2 = mergeSort(a, f1, f);
  return merge(a1, a2, f1 - s, f - f1, l);
}

int *merge(int *a1, int *a2, int a1l, int a2l, int l) {
  int j = 0;
  int k = 0;
  int *r = new int[l];
  for (int i = 0; i < l; i++) {
    if (j == a1l) {
      r[i] = a2[k++];
      continue;
    } else if (k == a2l) {
      r[i] = a1[j++];
      continue;
    }
    r[i] = a1[j] < a2[k] ? a1[j++] : a2[k++];
  }
  delete[] a1;
  delete[] a2;
  return r;
}
