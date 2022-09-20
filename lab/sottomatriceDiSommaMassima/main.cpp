#include <fstream>
#include <climits>

using namespace std;

int maxSumMat(int **, int, int);
int maxSum4(int *, int);

int main(){
    int R, C;
    ifstream in("input.txt");
    in >> R >> C;
    int ** mat = new int*[R];

    for(int i = 0; i < R; i++){
        mat[i] = new int[C];
        for(int j = 0; j < C; j++)
            in >> mat[i][j];
    } 

    ofstream out("output.txt");
    out<< maxSumMat(mat, R, C) <<endl;
    
    for(int i = 0; i < R; i++)
        delete[] mat[i];

    return 0;
}

int maxSumMat(int ** A, int r, int c) {

    //metodo risolutivo gentilmente offerto da https://www.geeksforgeeks.org/maximum-sum-submatrix/
    
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (j != 0)
                A[i][j] += A[i][j - 1];
        }
    }

    int maxSum = INT_MIN;

    for (int i = 0; i < c; i++) {

        for (int j = i; j < c; j++) {

            int *arr = new int[r];

            for (int k = 0; k < r; k++) {
                if (i == 0)
                    arr[k] = A[k][j];
                else
                    arr[k] = A[k][j] - A[k][i - 1];
            }
            maxSum = max(maxSum, maxSum4(arr, r));
            delete[] arr;
        }
    }

    return maxSum;
}

int maxSum4(int A[], int n) {
    int maxSoFar = 0;
    int maxHere = 0;
    for (int i=0; i < n; i++) {
        maxHere = max(maxHere+A[i], 0);
        maxSoFar = max(maxSoFar,maxHere);
    }
    return maxSoFar;
}
