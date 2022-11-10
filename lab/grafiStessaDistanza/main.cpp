#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Node{
    int numb;
    vector<int> adj;
};

struct Graph{
    vector<Node> nodes;

    void addNode(vector<int> adjs){
        Node newNode;
        newNode.numb = this->nodes.size();
        for(int i = 0; i < adjs.size(); i++){
            newNode.adj.push_back(adjs[i]);
            this->nodes[adjs[i]].adj.push_back(this->nodes.size());
        }
        this->nodes.push_back(newNode);
    }

    int* BFS(int n){
        int* res = new int[this->nodes.size()];
    
        queue<Node> _queue;

        _queue.push(this->nodes[n]);
        for(int i = 0; i < this->nodes.size(); i++)
            res[i] = INT_MAX;
        res[n] = 0;

        while(_queue.size() != 0){
            Node node = _queue.front();
            _queue.pop();    
            for(int i = 0; i < node.adj.size(); i++)
                if(res[node.adj[i] == INT_MAX]){
                    res[node.adj[i]] = res[node.numb] + 1;
                    _queue.push(this->nodes[node.adj[i]]);
                }
        }

        return res;
    }

    int* nodesWithEqualDistance(int& len, int s1, int s2){
        int* BFSs1 = this->BFS(s1);
        int* BFSs2 = this->BFS(s2);
        vector<int> tmpRes;
        for(int i = 0; i < this->nodes.size(); i++){
            if(BFSs1[i] == BFSs2[i])
                tmpRes.push_back(i);
        }
        delete[] BFSs1;
        delete[] BFSs2;
        len = tmpRes.size();
        int* res = new int[len];

        for(int i = 0; i < tmpRes.size(); i++)
            res[i] = tmpRes[i];

        return res;
    }   
};

int main(){
    Graph g1;
    vector<int> v0;
    g1.addNode(v0);

    vector<int> v1;
    v1.push_back(0);
    g1.addNode(v1);
    
    vector<int> v2;
    v2.push_back(0);
    v2.push_back(1);
    g1.addNode(v2);

    vector<int> v3;
    v3.push_back(2);
    g1.addNode(v3);

    vector<int> v4;
    g1.addNode(v4);

    vector<int> v5;
    v5.push_back(4);
    g1.addNode(v5);


    int len;
    int * res = g1.nodesWithEqualDistance(len, 1, 2);

    for(int i = 0; i < len; i++)
        cout << res[i] << " ";
    cout << endl;

    delete[] res;
    
    return 0;
}
