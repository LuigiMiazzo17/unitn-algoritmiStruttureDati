#include <iostream>

using namespace std;

struct node{
    int value;

    node *left;
    node *right;
};

void alberoLivelloValore(node*, int&, int = 0);
node* generateTree(int);

int main(){

    node* tree = generateTree(100);

    int res = 0;
    alberoLivelloValore(tree, res);
    cout << "Res: " << res << endl;

    return 0;
}

void alberoLivelloValore(node *tree, int& res, int pos){
    if(tree->value == pos)
        res++;

    pos++;

    if(tree->left != nullptr)
        alberoLivelloValore(tree->left, res, pos);
    if(tree->right != nullptr)
        alberoLivelloValore(tree->right, res, pos);

    return;
}

//generate random tree with n elements
node* generateTree(int n){
    node *tree = new node;
    tree->value = rand() % 100;
    tree->left = nullptr;
    tree->right = nullptr;

    for(int i = 0; i < n; i++){
        node *newNode = new node;
        newNode->value = rand() % 100;
        newNode->left = nullptr;
        newNode->right = nullptr;

        node *currentNode = tree;
        while(true){
            if(newNode->value < currentNode->value){
                if(currentNode->left == nullptr){
                    currentNode->left = newNode;
                    break;
                }
                else
                    currentNode = currentNode->left;
            }
            else{
                if(currentNode->right == nullptr){
                    currentNode->right = newNode;
                    break;
                }
                else
                    currentNode = currentNode->right;
            }
        }
    }

    return tree;
}
