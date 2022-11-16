#include <fstream>
#include <vector>
#include <queue>

using namespace std;

struct Node{
    int v;
    vector<int> adj;
};

struct Graph{
    vector<Node> nodes;

    void createNode(){
        Node newNode;
        newNode.v = this->nodes.size();
        this->nodes.push_back(newNode);
    }

    void newNotOrientedEdge(int from, int to){
        this->nodes[from].adj.push_back(to);
        this->nodes[to].adj.push_back(from);
    }
    
    void newOrientedEdge(int from, int to){
        this->nodes[from].adj.push_back(to);
    }

    int* BFS(int n){
        int* res = new int[this->nodes.size()];
        
        for(int i = 0; i < this->nodes.size(); i++)
            res[i] = -1;

        queue<int> _queue;
        _queue.push(n);
        res[n] = 0;

        while(_queue.size() != 0){
            int currNode = _queue.front();
            _queue.pop();
            for(int i = 0; i < this->nodes[currNode].adj.size(); i++){
                int testingNode = this->nodes[currNode].adj[i];
                if(res[testingNode] == -1){
                    res[testingNode] = res[currNode] + 1;
                    _queue.push(testingNode);
                }
            }
        }

        return res;
    }
};

int diametro(Graph);

int main(){

    ifstream in("input.txt");
    int N, M;
    in >> N >> M;
    
    Graph _graph;

    for(int i = 0; i < N; i++)
        _graph.createNode();

    for(int i = 0; i < M; i++){
        int from, to;
        in >> from >> to;
        _graph.newNotOrientedEdge(from, to);
    }

    in.close();

    ofstream out("output.txt");
    out << diametro(_graph);

    out.close();
    return 0;
}

int max(int* arr, int l){
    int res = 0;
    for(int i = 0; i < l; i++)
        if(res < arr[i])
            res = arr[i];
    return res;
}

int diametro(Graph g){
    int* maxBFSs = new int[g.nodes.size()];
    
    for(int i = 0; i < g.nodes.size(); i++){
        int* res =  g.BFS(i);
        maxBFSs[i] = max(res, g.nodes.size());
        delete[] res;
    }
    int res = max(maxBFSs, g.nodes.size());
    delete[] maxBFSs;
    return res;
}
