#include <fstream>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

#ifndef LOCAL
std::ifstream _in("input.txt");
std::ofstream _out("output.txt");
#define cin _in
#define cout _out
#endif

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

  void newNotOrientedEdge(int from, int to) {
    this->nodes[from].adj.push_back(to);
    this->nodes[to].adj.push_back(from);
  }

  void newOrientedEdge(int from, int to) {
    this->nodes[from].adj.push_back(to);
  }

  void getOrder(int node, bool *visited, stack<int> &_stack) {
    visited[node] = true;
    for (int i = 0; i < this->nodes[node].adj.size(); i++)
      if (!visited[this->nodes[node].adj[i]])
        getOrder(this->nodes[node].adj[i], visited, _stack);
    _stack.push(node);
  }
};

int main() {

  int N, M;
  cin >> N >> M;

  Graph _graph;

  for (int i = 0; i < N; i++)
    _graph.createNode();

  for (int i = 0; i < M; i++) {
    int from, to;
    cin >> from >> to;
    _graph.newOrientedEdge(from, to);
  }

  bool *visited = new bool[N];
  for (int i = 0; i < N; i++)
    visited[i] = false;

  stack<int> _stack;
  int index = 0;
  while (_stack.size() != _graph.nodes.size()) {
    if (!visited[index])
      _graph.getOrder(index, visited, _stack);
    else {
      for (; index < _graph.nodes.size(); index++)
        if (!visited[index])
          break;
      _graph.getOrder(index, visited, _stack);
    }
  }

  int *len = new int[N];
  for (int i = 0; i < N; i++)
    len[i] = 0;

  while (!_stack.empty()) {
    int currNode = _stack.top();
    _stack.pop();
    for (int i = 0; i < _graph.nodes[currNode].adj.size(); i++) {
      int testingNode = _graph.nodes[currNode].adj[i];
      if (len[testingNode] < len[currNode] + 1)
        len[testingNode] = len[currNode] + 1;
    }
  }

  int max = 0;
  for (int i = 0; i < N; i++)
    if (max < len[i])
      max = len[i];

  delete[] len;
  delete[] visited;

  cout << max;
  return 0;
}
