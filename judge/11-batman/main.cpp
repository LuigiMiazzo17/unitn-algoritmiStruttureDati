#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <iostream>

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

struct Node{
  int v;
  vector<Edge> adj;
};

struct Edge{
  Node* from;
  Node* to;
  bool hasEnemy;
};

struct Graph{
  vector<Node> nodes;

  void createNode(){
    Node newNode;
    newNode.v = this->nodes.size();
    this->nodes.push_back(newNode);
  }

  void newEdge(int from, int to){
    Edge newEdge;
    newEdge.from = &this->nodes[from];
    newEdge.to = &this->nodes[to];
    newEdge.hasEnemy = false;
    this->nodes[from].adj.push_back(newEdge);
  }

  int nPath(int s, int d){
    int* accumulator = new int[this->nodes.size()];
    bool* visited = new bool[this->nodes.size()];
    for(int i = 0; i < this->nodes.size(); i++){
      accumulator[i] = 0;
      visited[i] = false;
    }
    accumulator[s] = 1;

    stack<Node> _stack;
    this->getOrder(&this->nodes[s], visited, _stack);
    delete[] visited;

    while(_stack.size() != 0){
      Node currNode = _stack.top();
      _stack.pop();
      for(int i = 0; i < currNode.adj.size(); i++)
        accumulator[currNode.adj[i].to->v] += accumulator[currNode.v];
    }

    int res = accumulator[d];
    delete[] accumulator;
    return res;
  }

  void getOrder(Node* node, bool* visited, stack<Node>& _stack){
    visited[node->v] = true;
    for(int i = 0; i < node->adj.size(); i++)
      if(!visited[node->adj[i].to->v])
        getOrder(node->adj[i].to, visited, _stack);
    _stack.push(*node);
  }
};

int main(){

  int N, M, S, D;
  cin >> N >> M >> S >> D;
  
  Graph _graph;
  Graph _iGraph;

  for(int i = 0; i < N; i++){
    _graph.createNode();
    _iGraph.createNode();
  }

  for(int i = 0; i < M; i++){
    int from, to;
    cin >> from >> to;
    _graph.newEdge(from, to);
    _iGraph.newEdge(to, from);
  }

  bool* visited = new bool[N];
  for(int i = 0; i < N; i++)
    visited[i] = false;

  stack<Node> _stack, _iStack;
  int index = 0;
  while(_stack.size() != _graph.nodes.size()){
    if(!visited[index])
      _graph.getOrder(&_graph.nodes[index], visited, _stack);
    else{
      for(; index < _graph.nodes.size(); index++)
        if(!visited[index])
          break;
      _graph.getOrder(&_graph.nodes[index], visited, _stack);
    }
  }

  int* dict = new int[N];
  for(int i = 0; i < N; i++){
    visited[i] = false;
    dict[i] = -1;
  }

  Graph componentsGraph;

  while(_stack.size() != 0){
    Node currNode = _stack.top();
    _stack.pop();
    if(!visited[currNode.v]){
      _iGraph.getOrder(&_iGraph.nodes[currNode.v], visited, _iStack);
      componentsGraph.createNode();
      while(_iStack.size() != 0){
        Node n = _iStack.top();
        _iStack.pop();
        dict[n.v] = componentsGraph.nodes.size() - 1;
      }
    }
  }

  for(int i = 0; i < _graph.nodes.size(); i++)
    visited[i] = false;
  
  queue<Node> _queue;
  _queue.push(_graph.nodes[S]);

  while(_queue.size() != 0){
    Node currNode = _queue.front();
    _queue.pop();
    for(int i = 0; i < currNode.adj.size(); i++){
      Edge testingEdge = currNode.adj[i];
      if(dict[testingEdge.from->v] != dict[testingEdge.to->v])
        componentsGraph.newEdge(dict[testingEdge.from->v], dict[testingEdge.to->v]);
      if(!visited[testingEdge.to->v]){
        visited[testingEdge.to->v] = true;
        _queue.push(*testingEdge.to);
      }
    }
  }

  delete[] visited;
  delete[] dict;
  cout << componentsGraph.nPath(dict[S], dict[D]) << endl;
  return 0;
}


