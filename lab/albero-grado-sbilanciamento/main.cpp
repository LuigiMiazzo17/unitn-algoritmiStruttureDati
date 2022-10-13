#include <iostream>
#include <stdlib.h>

using namespace std;

struct node{
    int value;

    node *left;
    node *right;
};

int alberoSbilanciamento(node*);

node* generateTree(int);

int main(){

    node* tree = generateTree(100);

    cout << "Res: " << alberoSbilanciamento(tree) << endl;

    return 0;
}

int alberoSbilanciamento(node *tree){
    if(tree->left == nullptr && tree->right == nullptr)
        return 0;

    if(tree->left != nullptr && tree->right != nullptr)
        return 0 + abs(alberoSbilanciamento(tree->left) - alberoSbilanciamento(tree->right));

    if(tree->left == nullptr){
        return 1 + alberoSbilanciamento(tree->right);
    }
    if(tree->right == nullptr){
        return 1 + alberoSbilanciamento(tree->left);
    }
    return 0;
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
