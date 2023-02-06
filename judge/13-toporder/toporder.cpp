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

struct Edge;
struct Node;
struct Graph;

struct Node {
  int v;
  vector<Edge> adj;
};

struct Edge {
  Node *from;
  Node *to;
  bool hasEnemy;
};

struct Graph {
  vector<Node> nodes;

  void createNode() {
    Node newNode;
    newNode.v = this->nodes.size();
    this->nodes.push_back(newNode);
  }

  void newEdge(int from, int to) {
    Edge newEdge;
    newEdge.from = &this->nodes[from];
    newEdge.to = &this->nodes[to];
    newEdge.hasEnemy = false;
    this->nodes[from].adj.push_back(newEdge);
  }

  void getOrder(Node *node, bool *visited, stack<Node> &_stack) {
    visited[node->v] = true;
    for (int i = 0; i < node->adj.size(); i++)
      if (!visited[node->adj[i].to->v])
        getOrder(node->adj[i].to, visited, _stack);
    _stack.push(*node);
  }
};

int main() {

  int N, M;
  cin >> N >> M;

  Graph _graph;

  for (int i = 0; i < N; i++) {
    _graph.createNode();
  }

  for (int i = 0; i < M; i++) {
    int from, to;
    cin >> from >> to;
    _graph.newEdge(from, to);
  }

  bool *visited = new bool[N];
  for (int i = 0; i < N; i++)
    visited[i] = false;

  stack<Node> _stack;
  int index = 0;
  while (_stack.size() != _graph.nodes.size()) {
    if (!visited[index])
      _graph.getOrder(&_graph.nodes[index], visited, _stack);
    else {
      for (; index < _graph.nodes.size(); index++)
        if (!visited[index])
          break;
      _graph.getOrder(&_graph.nodes[index], visited, _stack);
    }
  }

  while (_stack.size() != 0) {
    Node currNode = _stack.top();
    _stack.pop();
    cout << currNode.v << " ";
  }

  delete[] visited;

  return 0;
}
