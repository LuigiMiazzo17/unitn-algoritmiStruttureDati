#include <climits>
#include <fstream>
#include <iostream>
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
// -1 existing and to be removed
// 0 not existing and not added
// 1 already existing
// 2 not existing and to be added
typedef int8_t edgeId;

struct Graph {
  edgeId **mat;
  nodeId N;
  uint32_t lastSum;

  void setupG(nodeId N) {
    this->N = N;
    this->lastSum = UINT32_MAX;
    this->mat = new edgeId *[N];
    for (nodeId i = 0; i < N; i++) {
      this->mat[i] = new edgeId[N];
    }

    for (nodeId i = 0; i < N; i++)
      for (nodeId j = 0; j < N; j++) {
        this->mat[i][j] = 0;
        this->mat[j][i] = 0;
      }
  }

  void disposeG() {
    for (nodeId i = 0; i < N; i++) {
      delete[] this->mat[i];
    }
    delete[] this->mat;
  }

  void setupEdge(nodeId n1, nodeId n2) {
    this->mat[n1][n2] = 1;
    this->mat[n2][n1] = 1;
  }

  void createEdge(nodeId n1, nodeId n2) {
    this->mat[n1][n2] = 2;
    this->mat[n2][n1] = 2;
  }

  void deleteEdge(nodeId n1, nodeId n2) {
    this->mat[n1][n2] = -1;
    this->mat[n2][n1] = -1;
  }

  nodeId
  checkOfAdjToList(const std::vector<std::vector<nodeId>> &adjsComponents,
                   nodeId n1) {
    for (nodeId i = 0; i < adjsComponents.size(); i++)
      if (this->mat[adjsComponents[i][0]][n1] == 1)
        return i;

    return UINT16_MAX;
  }

  void solve(std::priority_queue<std::pair<uint32_t, nodeId>> &order) {

    // remove useless edges
    while (!order.empty()) {
      nodeId i = order.top().second;
      order.pop();
      std::vector<std::vector<nodeId>> adjsComponents;
      edgeId *adjs = this->mat[i];
      std::pair<nodeId, nodeId> max = std::make_pair(UINT16_MAX, 0);

      for (nodeId j = 0; j < this->N; j++) {
        if (adjs[j] == 1) {
          nodeId res = checkOfAdjToList(adjsComponents, j);

          if (res == UINT16_MAX) {
            std::vector<nodeId> newComponent;
            newComponent.push_back(j);

            if (adjsComponents.size() == 0) {
              max.first = 0;
              max.second = 1;
            }

            adjsComponents.push_back(newComponent);
          } else {
            adjsComponents[res].push_back(j);

            if (adjsComponents[res].size() > max.second) {
              max.first = res;
              max.second = adjsComponents[res].size();
            }
          }
        }
      }

      for (nodeId j = 0; j < adjsComponents.size(); j++) {
        if (j != max.first) {
          for (nodeId k = 0; k < adjsComponents[j].size(); k++) {
            this->deleteEdge(i, adjsComponents[j][k]);
          }
        }
      }
    }

    // fix components
    nodeId lastStart = 0;
    std::vector<bool> visited = std::vector<bool>(this->N, false);

    while (true) {
      std::queue<nodeId> queue;
      std::vector<nodeId> components;

      queue.push(lastStart);
      visited[lastStart] = true;

      while (!queue.empty()) {
        nodeId currNode = queue.front();
        queue.pop();
        components.push_back(currNode);

        for (nodeId i = 0; i < this->N; i++) {
          if (this->mat[currNode][i] == 1 && !visited[i]) {
            queue.push(i);
            visited[i] = true;
          }
        }
      }

      for (nodeId i = 0; i < components.size(); i++)
        for (nodeId j = i + 1; j < components.size(); j++) {
          if (i != j) {
            edgeId edge = this->mat[components[i]][components[j]];
            if (edge == 0)
              this->createEdge(components[i], components[j]);
            else if (edge == -1)
              this->setupEdge(components[i], components[j]);
          }
        }

      // find first unvisited node
      for (; lastStart < this->N; lastStart++)
        if (!visited[lastStart])
          break;

      if (lastStart == this->N)
        break;
    }
  }

  void solveByAdd() {
    nodeId lastStart = 0;
    std::vector<bool> visited = std::vector<bool>(this->N, false);

    while (true) {
      std::queue<nodeId> queue;
      std::vector<nodeId> components;

      queue.push(lastStart);
      visited[lastStart] = true;

      while (!queue.empty()) {
        nodeId currNode = queue.front();
        queue.pop();
        components.push_back(currNode);

        for (nodeId i = 0; i < this->N; i++) {
          if (this->mat[currNode][i] == 1 && !visited[i]) {
            queue.push(i);
            visited[i] = true;
          }
        }
      }

      for (nodeId i = 0; i < components.size(); i++)
        for (nodeId j = i + 1; j < components.size(); j++) {
          if (i != j) {
            edgeId edge = this->mat[components[i]][components[j]];
            if (edge == 0)
              this->createEdge(components[i], components[j]);
            else if (edge == -1)
              this->setupEdge(components[i], components[j]);
          }
        }

      // find first unvisited node
      for (; lastStart < this->N; lastStart++)
        if (!visited[lastStart])
          break;

      if (lastStart == this->N)
        break;
    }
  }

  void resetMat() {
    for (nodeId i = 0; i < this->N; i++)
      for (nodeId j = 0; j < this->N; j++) {
        if (this->mat[i][j] == 2)
          this->mat[i][j] = 0;
        else if (this->mat[i][j] == -1)
          this->mat[i][j] = 1;
      }
  }

  void printSolution() {
    std::vector<std::pair<nodeId, nodeId>> createdEdges =
        std::vector<std::pair<nodeId, nodeId>>();
    std::vector<std::pair<nodeId, nodeId>> deletedEdges =
        std::vector<std::pair<nodeId, nodeId>>();

    // find new and deleted edges
    for (nodeId i = 0; i < this->N; i++) {
      for (nodeId j = i + 1; j < this->N; j++) {
        if (this->mat[i][j] == -1) {
          deletedEdges.push_back(std::make_pair(i, j));
        } else if (this->mat[i][j] == 2) {
          createdEdges.push_back(std::make_pair(i, j));
        }
      }
    }

    if (createdEdges.size() + deletedEdges.size() > this->lastSum)
      return;

    // print solution
    cout << createdEdges.size() << " " << deletedEdges.size() << std::endl;
    for (uint32_t i = 0; i < createdEdges.size(); i++)
      cout << "+ " << createdEdges[i].first << " " << createdEdges[i].second
           << std::endl;

    for (uint32_t i = 0; i < deletedEdges.size(); i++)
      cout << "- " << deletedEdges[i].first << " " << deletedEdges[i].second
           << std::endl;

    cout << "***" << std::endl;
    this->lastSum = createdEdges.size() + deletedEdges.size();
    return;
  }
};

int main(void) {

  nodeId N;
  uint32_t E;

  cin >> N >> E;

  Graph g;
  g.setupG(N);

  std::vector<uint32_t> degrees = std::vector<uint32_t>(N, 0);
  for (uint32_t i = 0; i < E; i++) {
    nodeId n1, n2;
    cin >> n1 >> n2;
    degrees[n1]++;
    degrees[n2]++;
    g.setupEdge(n1, n2);
  }
  std::priority_queue<std::pair<uint32_t, nodeId>> queue;

  for (nodeId i = 0; i < N; i++)
    queue.push(std::make_pair(degrees[i], i));

#ifndef LOCAL
  cin.close();
#endif

  g.solve(queue);
  g.printSolution();
  if (g.N < 3000) {
    g.resetMat();
    g.solveByAdd();
    g.printSolution();
  }
#ifndef LOCAL
  cout.close();
#endif
  g.disposeG();

  return 0;
}
