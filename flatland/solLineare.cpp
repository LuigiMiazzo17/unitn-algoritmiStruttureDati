#include <fstream>
#include <list>
#include <iterator>

using namespace std;

struct tri {
    short n;
    //true if left, otherwise right
    bool dir;
};

list<tri> resolve(tri *, int L);

int main(){
    int L;
    ifstream in("input.txt");
    in >> L;

    char *buffer= new char[L];
    in >> buffer;
    
    in.close();

    tri *tList = new tri[L];
    for(int i = 0; i < L; i++){
        tri nTri;
        nTri.n = i;
        nTri.dir = buffer[i] == 's';
        tList[i] = nTri;
    }

    delete[] buffer;

    list<tri> resList = resolve(tList, L);
    
    delete[] tList;

    ofstream out("output.txt");
    out << resList.size() << "\n";
    list<tri>::iterator it;
    for(it = resList.begin(); it != resList.end(); ++it)
        out << it->n << " ";

    out.close();

    return 0;
}

list<tri> resolve(tri *tList, int L){
    list<tri> resList;

    int leftMarker = L - 1;
    int rightMarker = 0;

    for(int i = L - 3; i >= 2; i -= 2)
        if(tList[i].dir && !tList[i + 1].dir){
            rightMarker = i;
            break;
        }

    for(int i = 2; i <= L - 1; i += 2)
        if(!tList[i].dir && tList[i - 1].dir){
            leftMarker = i;
            break;
        }

    if(!tList[1].dir || rightMarker > 0)
        resList.push_back(tList[0]);

    if(tList[L - 2].dir || leftMarker < L - 1)
        resList.push_back(tList[L - 1]);

    for(int i = leftMarker; i <= rightMarker; i += 2)
        resList.push_back(tList[i]);
    
    int j;
    for(j = 2; j < leftMarker; j += 2)
        if((j <= rightMarker || !tList[j + 1].dir) && tList[j - 1].dir)
            resList.push_back(tList[j]);
    
    for(int i = L - 3; i > rightMarker && i >= j; i -= 2)
        if((i >= leftMarker || tList[i - 1].dir) && !tList[i + 1].dir)
           resList.push_back(tList[i]);

    return resList;
}