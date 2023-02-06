#include <climits>
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

  void newNotOrientedEdge(int from, int to) {
    this->nodes[from].adj.push_back(to);
    this->nodes[to].adj.push_back(from);
  }

  void newOrientedEdge(int from, int to) {
    this->nodes[from].adj.push_back(to);
  }

  int *BFS(int n) {
    int *res = new int[this->nodes.size()];

    for (int i = 0; i < this->nodes.size(); i++)
      res[i] = INT_MAX;

    queue<int> _queue;
    _queue.push(n);
    res[n] = 0;

    while (_queue.size() != 0) {
      int currNode = _queue.front();
      _queue.pop();
      for (int i = 0; i < this->nodes[currNode].adj.size(); i++) {
        int testingNode = this->nodes[currNode].adj[i];
        if (res[testingNode] == INT_MAX) {
          res[testingNode] = res[currNode] + 1;
          _queue.push(testingNode);
        }
      }
    }

    return res;
  }
};

int *solve(Graph, Graph, int, int);

int main() {

  ifstream in("input.txt");
  int N, M, S, T;
  in >> N >> M >> S >> T;

  Graph _graph;
  Graph _invertedGraph;

  for (int i = 0; i < N; i++) {
    _graph.createNode();
    _invertedGraph.createNode();
  }

  for (int i = 0; i < M; i++) {
    int from, to;
    in >> from >> to;
    _graph.newOrientedEdge(from, to);
    _invertedGraph.newOrientedEdge(to, from);
  }

  in.close();

  ofstream out("output.txt");
  int *res = solve(_graph, _invertedGraph, S, T);
  out << res[0] << " " << res[1];

  delete[] res;

  out.close();
  return 0;
}

int *solve(Graph g, Graph iG, int n1, int n2) {
  int *bfsN1 = g.BFS(n1);

  int *res = new int(2);

  res[0] = bfsN1[n2];
  res[1] = 0;

  int *accumulator = new int[iG.nodes.size()];
  for (int i = 0; i < iG.nodes.size(); i++)
    accumulator[i] = -1;
  accumulator[n2] = 1;

  queue<int> _queue;
  _queue.push(n2);

  while (_queue.size() != 0) {
    int currNode = _queue.front();
    _queue.pop();
    for (int i = 0; i < iG.nodes[currNode].adj.size(); i++) {
      int testingNode = iG.nodes[currNode].adj[i];
      if (testingNode == n1) {
        res[1] += accumulator[currNode];
        continue;
      }
      if (bfsN1[testingNode] == bfsN1[currNode] - 1) {
        if (accumulator[testingNode] == -1) {
          accumulator[testingNode] = accumulator[currNode];
          _queue.push(testingNode);
        } else
          accumulator[testingNode] += accumulator[currNode];
      }
    }
  }

  delete[] bfsN1;
  delete[] accumulator;

  return res;
}
