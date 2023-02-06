#include <climits>
#include <fstream>
#include <iostream>
#include <memory>
#include <queue>
#include <stack>
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

struct Edge;
struct Node;
struct Graph;

struct Node {
  int v;
  std::vector<std::shared_ptr<Edge>> adj;
};

struct Edge {
  std::shared_ptr<Node> n1;
  std::shared_ptr<Node> n2;
  __uint8_t w;
  int firstOff;
  int tOff;
  int tOn;
};

struct Graph {
  std::vector<std::shared_ptr<Node>> nodes;

  void createNode() {
    std::shared_ptr<Node> newNode = std::make_shared<Node>();
    newNode->v = this->nodes.size();
    this->nodes.push_back(newNode);
  }

  void newEdge(int s, int t, int w, int f, int y, int n) {
    std::shared_ptr<Edge> newEdge = std::make_shared<Edge>();
    newEdge->n1 = this->nodes[s];
    newEdge->n2 = this->nodes[t];
    newEdge->w = w;
    newEdge->firstOff = f;
    newEdge->tOff = y;
    newEdge->tOn = n;
    this->nodes[s]->adj.push_back(newEdge);
    this->nodes[t]->adj.push_back(newEdge);
  }

  int solve(std::stack<std::shared_ptr<Node>> &_stack) {
    int *shortestPath = new int[this->nodes.size()];

    std::vector<std::shared_ptr<Edge>> prevEdge;

    for (int i = 0; i < this->nodes.size(); i++) {
      prevEdge.push_back(nullptr);
      shortestPath[i] = INT_MAX;
    }

    // first = weight (pQueue comparisons), second = node
    std::priority_queue<std::pair<int, std::shared_ptr<Node>>,
                        std::vector<std::pair<int, std::shared_ptr<Node>>>,
                        std::greater<std::pair<int, std::shared_ptr<Node>>>>
        _pQueue;

    _pQueue.push(std::make_pair(0, this->nodes[0]));
    shortestPath[0] = 0;

    while (!_pQueue.empty()) {
      std::shared_ptr<Node> currNode = _pQueue.top().second;
      _pQueue.pop();
      for (int i = 0; i < currNode->adj.size(); i++) {
        std::shared_ptr<Edge> testingEdge = currNode->adj[i];
        std::shared_ptr<Node> testingNode =
            (testingEdge->n1 == currNode) ? testingEdge->n2 : testingEdge->n1;
        int testingNodeWeight = testingEdge->w;
        int timeToHere = shortestPath[currNode->v];
        int tCycle = testingEdge->tOff + testingEdge->tOn;
        int normalizedTimeToHere = 0;
        if (timeToHere - testingEdge->firstOff < 0)
          timeToHere = testingEdge->firstOff;
        else
          normalizedTimeToHere = timeToHere - testingEdge->firstOff;
        if ((normalizedTimeToHere % tCycle) >= testingEdge->tOff ||
            ((normalizedTimeToHere + testingNodeWeight) % tCycle) >
                testingEdge->tOff)
          timeToHere += tCycle - (normalizedTimeToHere % tCycle);

        if (shortestPath[testingNode->v] > timeToHere + testingNodeWeight) {
          prevEdge[testingNode->v] = testingEdge;
          shortestPath[testingNode->v] = timeToHere + testingNodeWeight;
          if (shortestPath[testingNode->v] <= 1000000)
            _pQueue.push(
                std::make_pair(shortestPath[testingNode->v], testingNode));
        }
      }
    }

    int res = shortestPath[this->nodes.size() - 1];
    if (res != INT_MAX) {
      int i = this->nodes[this->nodes.size() - 1]->v;
      while (i != 0) {
        _stack.push(this->nodes[i]);
        i = (prevEdge[i]->n1->v == i) ? prevEdge[i]->n2->v : prevEdge[i]->n1->v;
      }
      _stack.push(this->nodes[i]);
    } else
      res = -1;
    delete[] shortestPath;
    return res;
  }
};

int main() {

  int N, M;
  cin >> N >> M;

  Graph _graph;

  for (int i = 0; i < N; i++)
    _graph.createNode();

  for (int i = 0; i < M; i++) {
    int s, t, w, f, y, n;
    cin >> s >> t >> w >> f >> y >> n;
    if (w <= y)
      _graph.newEdge(s, t, w, f, y, n);
  }

#ifndef LOCAL
  cin.close();
#endif

  std::stack<std::shared_ptr<Node>> _stack;
  cout << _graph.solve(_stack) << std::endl;

  while (!_stack.empty()) {
    cout << _stack.top()->v << std::endl;
    _stack.pop();
  }

#ifndef LOCAL
  cout.close();
#endif

  return 0;
}
