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

  bool existsPath(Node from, Node to){
    bool* visited = new bool[this->nodes.size()];
    
    for(int i = 0; i < this->nodes.size(); i++)
      visited[i] = false;

    queue<Node> _queue;
    _queue.push(from);
    visited[from.v] = true;

    while(_queue.size() != 0){
      Node currNode = _queue.front();
      _queue.pop();
      for(int i = 0; i < currNode.adj.size(); i++){
        Edge testingEdge = currNode.adj[i];
        if(to.v == testingEdge.to->v){
          delete[] visited;
          return true;
        }
        if(!visited[testingEdge.to->v]){
          visited[testingEdge.to->v] = true;
          _queue.push(*testingEdge.to);
        }
      }
    }

    delete[] visited;
    return false;
  }

  void putEnemy(){
    for(int i = 0; i < this->nodes.size(); i++)
      for(int j = 0; j < this->nodes[i].adj.size(); j++)
        if(!this->existsPath(*this->nodes[i].adj[j].to, this->nodes[i]))
          this->nodes[i].adj[j].hasEnemy = true;
  }  

  int solve(int s, int d){
    int res = 0;

    vector<Edge> chosingEdge = level(this->nodes[s], d); 
    res += chosingEdge.size();
    
    queue<Node> _queue;
    
    for(int i = 0; i < chosingEdge.size(); i++)
      _queue.push(*chosingEdge[i].to);

    while(_queue.size() != 0){
      Node currNode = _queue.front();
      _queue.pop();
      chosingEdge = level(currNode, d);
      
      if(chosingEdge.size() > 0)
        res += chosingEdge.size() - 1;

      for(int i = 0; i < chosingEdge.size(); i++)
        _queue.push(*chosingEdge[i].to);
    }

    return res;
  }
  
  vector<Edge> level(Node node, int d){
    vector<Edge> chosingEdge;
    bool* visited = new bool[this->nodes.size()];
    for(int i = 0; i < this->nodes.size(); i++)
      visited[i] = false;

    queue<Node> _queue;
    _queue.push(node);
    
    while(_queue.size() != 0){
      Node currNode = _queue.front();
      _queue.pop();
      for(int i = 0; i < currNode.adj.size(); i++){
        Edge testingEdge = currNode.adj[i];
        if(testingEdge.hasEnemy)
          chosingEdge.push_back(testingEdge);
        else if(!visited[testingEdge.to->v] && testingEdge.to->v != d){
          visited[testingEdge.to->v] = true;
          _queue.push(*testingEdge.to);
        }
      }
    }
    delete[] visited;
    return chosingEdge;
  }

};

int main(){

  int N, M, S, D;
  cin >> N >> M >> S >> D;
  
  Graph _graph;

  for(int i = 0; i < N; i++)
    _graph.createNode();

  for(int i = 0; i < M; i++){
    int from, to;
    cin >> from >> to;
    _graph.newEdge(from, to);
  }

  _graph.putEnemy();

  cout << _graph.solve(S, D) << endl;

  return 0;
}
