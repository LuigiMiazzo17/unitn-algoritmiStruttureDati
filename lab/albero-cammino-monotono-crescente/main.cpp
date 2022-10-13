#include <iostream>
#include <climits>

using namespace std;

struct node{
    int value;

    node *left;
    node *right;
};

void alberoCamminoMax(node*, int, int, int*);

node* generateTree(int);

int main(){

    node* tree = generateTree(100);

    int res = 0;
    alberoCamminoMax(tree, INT_MIN, 0, &res);
    cout << "Res: " << res << endl;

    return 0;
}

void alberoCamminoMax(node *tree, int prevValue, int currentStreak, int* maxNow){
    if(tree->value >= prevValue)
        currentStreak++;
    else
        currentStreak = 0;

    if(currentStreak > *maxNow)
        *maxNow = currentStreak;
  
    if(tree->left != nullptr)
        alberoCamminoMax(tree->left, tree->value, currentStreak, maxNow);
    if(tree->right != nullptr)
        alberoCamminoMax(tree->right, tree->value, currentStreak, maxNow);

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