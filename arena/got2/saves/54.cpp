#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <queue>
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

typedef uint16_t nodeId;

struct Node;
struct Graph;

struct Node {
  nodeId v;
  std::vector<nodeId> adj;

  nodeId findIndexOfNode(nodeId n) {
    for (nodeId i = 0; i < this->adj.size(); i++)
      if (this->adj[i] == n)
        return i;

    return -1;
  }
};

struct Graph {
  std::vector<std::shared_ptr<Node>> nodes;
  std::vector<std::pair<nodeId, nodeId>> edges;
  std::vector<std::pair<nodeId, nodeId>> createdEdges;
  std::vector<std::pair<nodeId, nodeId>> deletedEdges;

  void createNode(nodeId c) {
    std::shared_ptr<Node> newNode = std::make_shared<Node>();
    newNode->v = this->nodes.size();
    newNode->adj = std::vector<nodeId>();
    this->nodes.push_back(newNode);
  }

  void setupG(nodeId N, uint32_t E) {
    for (nodeId i = 0; i < N; i++) {
      this->createNode(i);
    }
    createdEdges = std::vector<std::pair<nodeId, nodeId>>();
    deletedEdges = std::vector<std::pair<nodeId, nodeId>>();
  }

  void newEdge(nodeId n1, nodeId n2) {
    this->edges.push_back(std::make_pair(n1, n2));
    this->nodes[n1]->adj.push_back(n2);
    this->nodes[n2]->adj.push_back(n1);
  }

  void deleteEdge(nodeId n1, nodeId n2) {
    this->nodes[n1]->adj.erase(this->nodes[n1]->adj.begin() +
                               this->nodes[n1]->findIndexOfNode(n2));
    this->nodes[n2]->adj.erase(this->nodes[n2]->adj.begin() +
                               this->nodes[n2]->findIndexOfNode(n1));
  }

  bool isBridge(std::vector<nodeId> const &inVectorA,
                std::vector<nodeId> const &nVectorB) {
    return std::find_first_of(inVectorA.begin(), inVectorA.end(),
                              nVectorB.begin(),
                              nVectorB.end()) != inVectorA.end();
  }

  void solve() {

    for (uint32_t i = 0; i < this->edges.size(); i++) {
      if (!isBridge(this->nodes[this->edges[i].first]->adj,
                    this->nodes[this->edges[i].second]->adj)) {
        this->deletedEdges.push_back(this->edges[i]);
        this->deleteEdge(this->edges[i].first, this->edges[i].second);
      }
    }

    std::vector<bool> visited = std::vector<bool>(this->nodes.size(), false);
    nodeId lastStart = 0;

    while (true) {
      std::queue<nodeId> _queue;
      std::vector<nodeId> _components = std::vector<nodeId>();

      _queue.push(lastStart);
      visited[lastStart] = true;

      // find all connected nodes
      while (!_queue.empty()) {
        nodeId currNode = _queue.front();
        _queue.pop();
        _components.push_back(currNode);

        for (nodeId i = 0; i < this->nodes[currNode]->adj.size(); i++) {
          nodeId n = this->nodes[currNode]->adj[i];

          if (!visited[n]) {
            visited[n] = true;
            _queue.push(n);
          }
        }
      }

      std::vector<std::vector<bool>> _connected =
          std::vector<std::vector<bool>>(
              _components.size(), std::vector<bool>(_components.size(), false));

      // add all edges between connected nodes
      for (nodeId i = 0; i < _components.size(); i++) {
        for (nodeId j = 0; j < this->nodes[_components[i]]->adj.size(); j++) {
          nodeId n = this->nodes[_components[i]]->adj[j];

          // find index of n in _components
          nodeId index = std::find(_components.begin(), _components.end(), n) -
                         _components.begin();
          _connected[i][index] = true;
        }
      }

      // find missing edges
      for (nodeId i = 0; i < _components.size(); i++)
        for (nodeId j = i + 1; j < _components.size(); j++)
          if (!_connected[i][j])
            this->createdEdges.push_back(
                std::make_pair(_components[i], _components[j]));

      // find first unvisited node
      for (; lastStart < visited.size(); lastStart++)
        if (!visited[lastStart])
          break;

      // if all nodes are visited, break
      if (lastStart == visited.size())
        break;
    }
  }

  void printSolution() {
    cout << this->createdEdges.size() << " " << this->deletedEdges.size()
         << std::endl;
    for (std::pair<nodeId, nodeId> p : this->createdEdges)
      cout << "+ " << p.first << " " << p.second << std::endl;
    for (std::pair<nodeId, nodeId> p : this->deletedEdges)
      cout << "- " << p.first << " " << p.second << std::endl;
    cout << "***" << std::endl;
  }
};

int main(void) {

  uint16_t N;
  uint32_t E;

  cin >> N >> E;

  Graph g;
  g.setupG(N, E);

  for (uint32_t i = 0; i < E; i++) {
    nodeId n1, n2;
    cin >> n1 >> n2;
    g.newEdge(n1, n2);
  }

#ifndef LOCAL
  cin.close();
#endif

  g.solve();
  g.printSolution();

#ifndef LOCAL
  cout.close();
#endif

  return 0;
}
