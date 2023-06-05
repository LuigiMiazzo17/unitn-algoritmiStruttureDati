#include <fstream>
#include <iostream>
#include <stack>

using namespace std;

int NODE;
int **graph;

int min(int a, int b) { return (a < b) ? a : b; }

void findComponent(int u, int disc[], int low[], stack<int> &stk,
                   bool stkItem[]) {
  static int time = 0;
  disc[u] = low[u] = ++time; // inilially discovery time and low value is 1
  stk.push(u);
  stkItem[u] = true; // flag as u in the stack

  for (int v = 0; v < NODE; v++) {
    if (graph[u][v]) {
      if (disc[v] == -1) { // when v is not visited
        findComponent(v, disc, low, stk, stkItem);
        low[u] = min(low[u], low[v]);
      } else if (stkItem[v]) // when v is in the stack, update low for u
        low[u] = min(low[u], disc[v]);
    }
  }

  int poppedItem = 0;
  if (low[u] == disc[u]) {
    while (stk.top() != u) {
      poppedItem = stk.top();
      cout << poppedItem << " ";
      stkItem[poppedItem] = false; // mark as item is popped
      stk.pop();
    }
    poppedItem = stk.top();
    cout << poppedItem << endl;
    stkItem[poppedItem] = false;
    stk.pop();
  }
}

void strongConComponent() {
  int disc[NODE], low[NODE];
  bool stkItem[NODE];
  stack<int> stk;

  for (int i = 0; i < NODE; i++) { // initialize all elements
    disc[i] = low[i] = -1;
    stkItem[i] = false;
  }

  for (int i = 0; i < NODE; i++) // initialize all elements
    if (disc[i] == -1)
      findComponent(i, disc, low, stk, stkItem);
}

int main() {
  ifstream in("input.txt");
  in >> NODE;
  int E;
  in >> E;
  graph = new int *[NODE];
  for (int i = 0; i < NODE; i++)
    graph[i] = new int[NODE];
  for (int i = 0; i < NODE; i++)
    for (int j = 0; j < NODE; j++)
      graph[i][j] = 0;
  for (int i = 0; i < E; i++) {
    int u, v;
    in >> u >> v;
    graph[u][v] = 1;
  }
  strongConComponent();
}
