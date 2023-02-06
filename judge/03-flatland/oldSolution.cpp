#include <fstream>
#include <iterator>
#include <list>

using namespace std;

struct tri {
  short n;
  // true if left, otherwise right
  bool dir;
};

list<tri> resolve(tri *, int L);

int main() {
  int L;
  ifstream in("input.txt");
  in >> L;

  char *buffer = new char[L];
  in >> buffer;

  in.close();

  tri *tList = new tri[L];
  for (int i = 0; i < L; i++) {
    tri nTri;
    nTri.n = i;
    nTri.dir = buffer[i] == 's';
    tList[i] = nTri;
  }

  delete[] buffer;

  list<tri> resList = resolve(tList, L);

  delete[] tList;

  ofstream out("output.txt");
  out << resList.size() << "\n";
  list<tri>::iterator it;
  for (it = resList.begin(); it != resList.end(); ++it)
    out << it->n << " ";

  out.close();

  return 0;
}

bool check_right(tri *tList, int p, int L) {
  if (!tList[p + 1].dir)
    return true;
  for (int j = p + 1; j < L; j += 2)
    if (!tList[j].dir && tList[j - 1].dir)
      return true;
  return false;
}

bool check_left(tri *tList, int p) {
  if (tList[p - 1].dir)
    return true;
  for (int j = p - 1; j >= 0; j -= 2)
    if (tList[j].dir && !tList[j + 1].dir)
      return true;
  return false;
}

list<tri> resolve(tri *tList, int L) {
  list<tri> resList;

  if (check_right(tList, 0, L))
    resList.push_back(tList[0]);

  if (check_left(tList, L - 1))
    resList.push_back(tList[L - 1]);

  for (int i = 2; i < L - 1; i += 2) {
    if (check_right(tList, i, L) && check_left(tList, i))
      resList.push_back(tList[i]);
  }
  return resList;
}
