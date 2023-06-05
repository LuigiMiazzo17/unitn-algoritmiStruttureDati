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

struct Node;
struct Graph;

struct Node {
  uint16_t v;
  uint32_t c;
  bool visited;
  bool hasToBeVisited;
  int16_t rider;
  int32_t gain;
  std::vector<uint32_t> adj;
};

struct Graph {
  std::vector<std::shared_ptr<Node>> nodes;
  std::vector<std::vector<std::shared_ptr<Node>>> routes;
  // first: gain, second: node:
  std::priority_queue<std::pair<uint32_t, std::shared_ptr<Node>>>
      possibleRoutes;
  // first: node, second: ticks
  std::vector<std::pair<uint16_t, uint32_t>> riders;

  uint16_t nNodes;
  uint16_t base;
  uint16_t activeR;
  uint64_t totalGain;

  void setupRealG(uint16_t nNodes, uint16_t base, uint16_t activeR) {
    this->nNodes = nNodes;
    this->base = base;
    this->activeR = activeR;
    this->totalGain = 0;
    this->routes = std::vector<std::vector<std::shared_ptr<Node>>>(activeR);
    this->riders = std::vector<std::pair<uint16_t, uint32_t>>(activeR);
    for (uint16_t i = 0; i < activeR; i++) {
      this->riders[i].first = base;
      this->riders[i].second = 0;
    }
  }

  void createNode(uint32_t c) {
    std::shared_ptr<Node> newNode = std::make_shared<Node>();
    newNode->v = this->nodes.size();
    newNode->c = c;
    newNode->visited = false;
    newNode->hasToBeVisited = false;
    newNode->rider = -1;
    newNode->gain = 0;
    newNode->adj = std::vector<uint32_t>(this->nNodes);
    this->nodes.push_back(newNode);
  }

  void newEdge(uint16_t n1, uint16_t n2, uint32_t w) {
    this->nodes[n1]->adj[n2] = w;
    this->nodes[n2]->adj[n1] = w;
  }

  std::shared_ptr<Node> findMax(uint16_t r) {
    uint16_t n = this->riders[r].first;
    std::shared_ptr<Node> riderNode = this->nodes[n];
    uint32_t ticks = this->riders[r].second;

    std::shared_ptr<Node> maxNode = nullptr;
    uint32_t currGain = 0;

    for (uint16_t i = 0; i < this->nNodes; i++) {
      if (i == this->base || i == n)
        continue;

      if (!this->nodes[i]->visited) {
        uint32_t hypGain = this->nodes[i]->c - (ticks + riderNode->adj[i]);

        if (hypGain > currGain) {
          if (!this->nodes[i]->hasToBeVisited) {
            currGain = hypGain;
            maxNode = this->nodes[i];
          } else if (this->nodes[i]->gain < hypGain) {
            currGain = hypGain;

            std::shared_ptr<Node> nextNodeForFirend =
                findMax(this->nodes[i]->rider);
            if (nextNodeForFirend != nullptr)
              this->possibleRoutes.push(
                  std::make_pair(nextNodeForFirend->c, nextNodeForFirend));

            maxNode = this->nodes[i];
          }
        }
      }
    }

    if (maxNode != nullptr) {
      maxNode->hasToBeVisited = true;
      maxNode->rider = r;
      maxNode->gain =
          this->nodes[maxNode->v]->c - (ticks + riderNode->adj[maxNode->v]);
    }
    return maxNode;
  }

  void riderVisit(uint16_t r, std::shared_ptr<Node> currNode,
                  std::shared_ptr<Node> nextNode) {
    this->routes[r].push_back(nextNode);
    this->totalGain +=
        nextNode->c - (this->riders[r].second + currNode->adj[nextNode->v]);
    this->riders[r].first = nextNode->v;
    this->riders[r].second += currNode->adj[nextNode->v];
    nextNode->visited = true;
  }

  void setupStart() {
    for (uint16_t i = 0; i < this->activeR; i++) {
      this->routes[i].push_back(this->nodes[this->base]);
      std::shared_ptr<Node> nextNode = this->findMax(i);
      this->possibleRoutes.push(std::make_pair(nextNode->c, nextNode));
    }
  }

  void solve() {
    this->nodes[this->base]->visited = true;

    this->setupStart();

    while (!possibleRoutes.empty()) {
      std::shared_ptr<Node> nextNode = possibleRoutes.top().second;
      possibleRoutes.pop();
      if (nextNode->visited)
        continue;

      uint16_t r = nextNode->rider;
      riderVisit(r, this->nodes[riders[r].first], nextNode);
      nextNode = findMax(r);
      if (nextNode != nullptr)
        this->possibleRoutes.push(std::make_pair(nextNode->c, nextNode));
    }
  }

  void printSol() {
    cout << this->totalGain << std::endl;
    for (uint16_t i = 0; i < this->activeR; i++) {
      cout << this->routes[i].size() << std::endl;
      for (uint16_t j = 0; j < this->routes[i].size(); j++) {
        cout << this->routes[i][j]->v << " ";
      }
      cout << std::endl;
    }
  }
};

int main(void) {

  uint16_t N, R, S;

  cin >> N >> R >> S;

  Graph g;

  g.setupRealG(N, S, R);

  for (uint16_t i = 0; i < N; i++) {
    uint32_t c;
    cin >> c;
    g.createNode(c);
  }

  for (uint16_t i = 1; i < N; i++) {
    for (uint16_t j = 0; j < N; j++) {
      if (i == j) {
        g.newEdge(i, i, 0);
        break;
      }
      uint32_t w;
      cin >> w;
      g.newEdge(i, j, w);
    }
  }

#ifndef LOCAL
  cin.close();
#endif

  g.solve();

  g.printSol();
  cout << "***";

#ifndef LOCAL
  cout.close();
#endif

  return 0;
}
