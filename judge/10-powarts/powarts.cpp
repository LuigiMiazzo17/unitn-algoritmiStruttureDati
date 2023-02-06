#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <queue>
#include <stack>
#include <utility>
#include <vector>

#ifndef LOCAL
std::ifstream _in("input.txt");
std::ofstream _out("output.txt");
#define cin _in
#define cout _out
#endif

using namespace std;

struct wNode {
  int v;
  // first = node, second = weight
  vector<pair<int, int>> adj;
};

struct wGraph {
  vector<wNode> nodes;

  void createNode() {
    wNode newNode;
    newNode.v = this->nodes.size();
    this->nodes.push_back(newNode);
  }

  void newEdge(int from, int to, int w) {
    this->nodes[from].adj.push_back(make_pair(to, w));
    this->nodes[to].adj.push_back(make_pair(from, w));
  }

  static void getOrder(vector<vector<int>> &succ, bool *visited, int n,
                       stack<int> &_stack) {
    for (int i = 0; i < succ[n].size(); i++) {
      if (!visited[succ[n][i]]) {
        visited[succ[n][i]] = true;
        getOrder(succ, visited, succ[n][i], _stack);
      }
    }
    _stack.push(n);
  }

  vector<int> wBFS(int n) {
    int *shortestPath = new int[this->nodes.size()];

    vector<vector<int>> prev;

    for (int i = 0; i < this->nodes.size(); i++) {
      vector<int> v;
      prev.push_back(v);
      shortestPath[i] = INT_MAX;
    }

    // first = weight (priority queue comparisons), second = node
    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>
        _pQueue;

    _pQueue.push(make_pair(0, n));
    shortestPath[n] = 0;

    while (!_pQueue.empty()) {
      int currNode = _pQueue.top().second;
      _pQueue.pop();

      for (int i = 0; i < this->nodes[currNode].adj.size(); i++) {
        int testingNode = this->nodes[currNode].adj[i].first;
        int testingNodeWeight = this->nodes[currNode].adj[i].second;
        if (shortestPath[testingNode] >
            shortestPath[currNode] + testingNodeWeight) {
          vector<int> v;
          v.push_back(currNode);
          prev[testingNode] = v;
          shortestPath[testingNode] =
              shortestPath[currNode] + testingNodeWeight;
          _pQueue.push(make_pair(shortestPath[testingNode], testingNode));
        } else if (shortestPath[testingNode] ==
                   shortestPath[currNode] + testingNodeWeight) {
          prev[testingNode].push_back(currNode);
        }
      }
    }

    vector<vector<int>> succ;
    int *accumulator = new int[this->nodes.size()];
    int *commonPath = new int[this->nodes.size()];
    bool *visited = new bool[this->nodes.size()];

    for (int i = 0; i < this->nodes.size(); i++) {
      vector<int> v;
      succ.push_back(v);
      visited[i] = false;
      accumulator[i] = 0;
      commonPath[i] = -1;
    }

    for (int i = 0; i < prev.size(); i++) {
      for (int j = 0; j < prev[i].size(); j++)
        succ[prev[i][j]].push_back(i);
    }

    stack<int> _stack;
    wGraph::getOrder(succ, visited, n, _stack);
    _stack.pop();

    delete[] visited;

    for (int i = 0; i < succ[n].size(); i++) {
      commonPath[succ[n][i]] = succ[n][i];
    }

    while (!_stack.empty()) {
      int currNode = _stack.top();
      _stack.pop();

      for (int i = 0; i < succ[currNode].size(); i++) {
        int testingNode = succ[currNode][i];

        if (commonPath[testingNode] == -1) {
          commonPath[testingNode] = commonPath[currNode];
          accumulator[commonPath[testingNode]]++;
        } else if (commonPath[testingNode] != commonPath[currNode]) {
          accumulator[commonPath[testingNode]]--;
          accumulator[testingNode]++;
          commonPath[testingNode] = testingNode;
        }
      }
    }

    delete[] commonPath;

    pair<int, int> maxNode;
    // first = node, second = n of childs pruned
    maxNode = make_pair(-1, 0);
    for (int i = 0; i < this->nodes.size(); i++) {
      if (maxNode.second < accumulator[i] && i != n)
        maxNode = make_pair(i, accumulator[i]);
    }

    delete[] accumulator;

    int *currentShortestPath = new int[this->nodes.size()];

    for (int i = 0; i < this->nodes.size(); i++)
      currentShortestPath[i] = INT_MAX;

    _pQueue.push(make_pair(0, n));
    currentShortestPath[n] = 0;

    while (!_pQueue.empty()) {
      int currNode = _pQueue.top().second;
      _pQueue.pop();

      for (int i = 0; i < this->nodes[currNode].adj.size(); i++) {
        int testingNode = this->nodes[currNode].adj[i].first;
        int testingNodeWeight = this->nodes[currNode].adj[i].second;
        if (currentShortestPath[testingNode] >
                currentShortestPath[currNode] + testingNodeWeight &&
            testingNode != maxNode.first) {
          currentShortestPath[testingNode] =
              currentShortestPath[currNode] + testingNodeWeight;
          _pQueue.push(
              make_pair(currentShortestPath[testingNode], testingNode));
        }
      }
    }

    vector<int> vRes;
    for (int i = 0; i < this->nodes.size(); i++) {
      if (currentShortestPath[i] != shortestPath[i])
        vRes.push_back(i);
    }

    delete[] shortestPath;
    delete[] currentShortestPath;

    return vRes;
  }
};

int main() {

  int N, M, P;
  cin >> N >> M >> P;

  wGraph _graph;

  for (int i = 0; i < N; i++)
    _graph.createNode();

  for (int i = 0; i < M; i++) {
    int from, to, weight;
    cin >> from >> to >> weight;
    _graph.newEdge(from, to, weight);
  }

  vector<int> r = _graph.wBFS(P);
  sort(r.begin(), r.end());

  cout << r.size() << endl;
  for (int i = 0; i < r.size(); i++)
    cout << r[i] << endl;

  return 0;
}
