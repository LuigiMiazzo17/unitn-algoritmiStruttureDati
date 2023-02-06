#include <fstream>
#include <queue>
#include <vector>

using namespace std;

struct Node {
  int v;
  vector<int> adj;
};

struct Graph {
  vector<Node> nodes;

  void createNode() {
    Node newNode;
    newNode.v = this->nodes.size();
    this->nodes.push_back(newNode);
  }

  void newEdge(int from, int to) { this->nodes[from].adj.push_back(to); }
};

int nOfReachableNodes(Graph, int);

int main() {

  ifstream in("input.txt");
  int N, M, S;
  in >> N >> M >> S;

  Graph _graph;

  for (int i = 0; i < N; i++)
    _graph.createNode();

  for (int i = 0; i < M; i++) {
    int from, to;
    in >> from >> to;
    _graph.newEdge(from, to);
  }

  in.close();

  ofstream out("output.txt");
  out << nOfReachableNodes(_graph, S);

  out.close();
  return 0;
}

int nOfReachableNodes(Graph g, int n) {
  bool *visitedArr = new bool[g.nodes.size()];

  queue<int> _queue;
  _queue.push(n);
  visitedArr[n] = true;
  int res = 0;

  while (_queue.size() != 0) {
    int currNode = _queue.front();
    _queue.pop();
    for (int i = 0; i < g.nodes[currNode].adj.size(); i++) {
      int testingNode = g.nodes[currNode].adj[i];
      if (!visitedArr[testingNode]) {
        visitedArr[testingNode] = true;
        _queue.push(testingNode);
      }
    }

    res++;
  }

  delete[] visitedArr;
  return res;
}
