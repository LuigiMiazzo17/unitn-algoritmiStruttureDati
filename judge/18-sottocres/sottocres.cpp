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

typedef uint32_t SumType;
typedef uint32_t ValueType;
typedef uint16_t IndexType;
typedef std::pair<SumType, ValueType> PairType;

class SortedArray {
private:
  std::vector<PairType> array;

public:
  void insert(const PairType &element) {
    auto it = array.begin();
    while (it != array.end() && element.first < it->first) {
      ++it;
    }
    array.insert(it, element);
  }

  SumType getMax(ValueType n) {
    IndexType i = 0;
    while (i < array.size()) {
      if (array[i].second >= n)
        return array[i].first;
      i++;
    }
    return 0;
  }

  SumType getAnswer() { return array[0].first; }
};

int main(void) {

  IndexType N;
  cin >> N;

  std::vector<ValueType> arr(N, 0);

  for (IndexType i = 0; i < N; i++)
    cin >> arr[i];

#ifndef LOCAL
  cin.close();
#endif

  SortedArray sa = SortedArray();

  for (int32_t i = N - 1; i >= 0; i--) {
    SumType c = arr[i];
    c += sa.getMax(arr[i]);
    sa.insert(std::make_pair(c, arr[i]));
  }

  cout << sa.getAnswer();

#ifndef LOCAL
  cout.close();
#endif

  return 0;
}
