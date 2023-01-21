#include <fstream>
#include <memory>
#include <vector>
#include <climits>
#include <queue>
#include <stack>
#include <iostream>
#include <utility>

#ifndef LOCAL
std::ifstream _in("input.txt");
std::ofstream _out("output.txt");
#define cin _in
#define cout _out
#else
#define cin std::cin
#define cout std::cout
#endif

struct Edge;
struct Node;
struct Graph;

struct Node{
  int v;
  std::vector<std::shared_ptr<Edge> > simpleAdj;
  std::vector<std::shared_ptr<Edge> > ventAdj;
};

struct Edge{
  std::shared_ptr<Node> from;
  std::shared_ptr<Node> to;
  bool isVent;
  int w;
  int wMin;
  int wMax;

  void setMax(){
    this->w = this->wMax;
  }

  void setMin(){
    this->w = this->wMin;
  }
};

struct Graph{
  std::vector<std::shared_ptr<Node> > nodes;

  void createNode(){
    std::shared_ptr<Node> newNode = std::make_shared<Node>();
    newNode->v = this->nodes.size();
    this->nodes.push_back(newNode);
  }

  void newSimpleEdge(int from, int to, int w){
    std::shared_ptr<Edge> newEdge = std::make_shared<Edge>();
    newEdge->from = this->nodes[from];
    newEdge->to = this->nodes[to];
    newEdge->w = w;
    newEdge->isVent = false;
    this->nodes[from]->simpleAdj.push_back(newEdge);
  }

  void newVentEdge(int from, int to, int wMin, int wMax, std::vector<std::shared_ptr<Edge> >& v){
    std::shared_ptr<Edge> newEdge = std::make_shared<Edge>();
    v.push_back(newEdge);
    newEdge->from = this->nodes[from];
    newEdge->to = this->nodes[to];
    newEdge->w = 0;
    newEdge->wMin = wMin;
    newEdge->wMax = wMax;
    newEdge->isVent = true;
    this->nodes[from]->ventAdj.push_back(newEdge);
  }

  std::pair<int, int> solve(int m, int s, int f, std::stack<std::shared_ptr<Node> >& _stack){
    int* shortestPathStud = new int[this->nodes.size()];
    int* shortestPathMontry = new int[this->nodes.size()];

    std::vector<std::shared_ptr<Edge> > prevEdge;

    for(int i = 0; i < this->nodes.size(); i++){
      prevEdge.push_back(nullptr);
      shortestPathStud[i] = INT_MAX;
      shortestPathMontry[i] = INT_MAX;
    }
  
    //first = weight (pQueue comparisons), second = node
    std::priority_queue<
      std::pair<int, std::pair<std::shared_ptr<Node>, bool> >, 
      std::vector<std::pair<int, std::pair<std::shared_ptr<Node>, bool> > >, 
      std::greater<std::pair<int, std::pair<std::shared_ptr<Node>, bool> > > > _pQueue;
    
    _pQueue.push(std::make_pair(0, std::make_pair(this->nodes[s], false)));
    _pQueue.push(std::make_pair(0, std::make_pair(this->nodes[m], true)));
    shortestPathStud[s] = 0;
    shortestPathMontry[m] = 0;

    while(!_pQueue.empty()){
      std::shared_ptr<Node> currNode = _pQueue.top().second.first;
      bool isSus = _pQueue.top().second.second;
      _pQueue.pop();
      int* myShortestPath = isSus ? shortestPathMontry : shortestPathStud;
     
      //for not vented Edges
      for(int i = 0; i < currNode->simpleAdj.size(); i++){
        std::shared_ptr<Node> testingNode = currNode->simpleAdj[i]->to;
        int testingNodeWeight = currNode->simpleAdj[i]->w;
        if(myShortestPath[testingNode->v] > myShortestPath[currNode->v] + testingNodeWeight){
          if(isSus)
            prevEdge[testingNode->v] = currNode->simpleAdj[i]; 
          myShortestPath[testingNode->v] = myShortestPath[currNode->v] + testingNodeWeight;
          _pQueue.push(std::make_pair(myShortestPath[testingNode->v], std::make_pair(testingNode, isSus)));
        } 
      }
      
      //for vented Edges
      for(int i = 0; i < currNode->ventAdj.size(); i++){
        std::shared_ptr<Node> testingNode = currNode->ventAdj[i]->to;
        if(currNode->ventAdj[i]->w == 0)
          isSus ? currNode->ventAdj[i]->setMin() : currNode->ventAdj[i]->setMax();
        int testingNodeWeight = currNode->ventAdj[i]->w;
        if(myShortestPath[testingNode->v] > myShortestPath[currNode->v] + testingNodeWeight){
          if(isSus)
            prevEdge[testingNode->v] = currNode->ventAdj[i]; 
          myShortestPath[testingNode->v] = myShortestPath[currNode->v] + testingNodeWeight;
          _pQueue.push(std::make_pair(myShortestPath[testingNode->v], std::make_pair(testingNode, isSus)));
        }
      } 
    }

    int i = f;
    while(i != m){
      _stack.push(this->nodes[i]);
      i = prevEdge[i]->from->v;
    } 
    _stack.push(this->nodes[i]);
    std::pair<int, int> res = std::make_pair(shortestPathMontry[f], shortestPathStud[f]);
    delete[] shortestPathStud;
    delete[] shortestPathMontry;
    return res;
  }

};

int main(){

  int N, M, K, I, S, F;
  cin >> N >> M >> K;     //stanze >> corridoi normali >> corridoi ventolati
  cin >> I >> S >> F;     //MontreSuS >> Studenti >> FabLab

  Graph _graph;

  for(int i = 0; i < N; i++)
    _graph.createNode();

  for(int i = 0; i < M; i++){
    int from, to, w;
    cin >> from >> to >> w;
    _graph.newSimpleEdge(from, to, w);
  }

  std::vector<std::shared_ptr<Edge> > ventEdges;

  for(int i = 0; i < K; i++){
    int from, to, wMin, wMax;
    cin >> from >> to >> wMin >> wMax;
    _graph.newVentEdge(from, to, wMin, wMax, ventEdges);
  }
  
  std::stack<std::shared_ptr<Node> > _stack;
  std::pair<int, int> res = _graph.solve(I, S, F, _stack);

  int pMontreSus = res.first; 
  int pStudents = res.second; 

  if(pMontreSus == pStudents)
    cout << 0 << std::endl;
  else if(pMontreSus < pStudents)
    cout << 1 << std::endl;
  else
    cout << 2 << std::endl;
  
  cout << pMontreSus << " " << pStudents << std::endl;
  
  for(int i = 0; i < ventEdges.size(); i++)
    cout << ventEdges[i]->w << " ";
  cout << std::endl;

  cout << _stack.size() << std::endl;
  
  while(!_stack.empty()){
    cout << _stack.top()->v << " ";
    _stack.pop();
  }
 
  return 0;
}
