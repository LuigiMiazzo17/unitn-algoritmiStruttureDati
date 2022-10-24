#include <fstream>

using namespace std;

struct interval{
    long long s;
    long long f;
};

long long* resolve(interval*, int);
void intervalCP(interval&, interval&);
interval* mergeSort(interval*, int, int);
interval* merge(interval*, interval*, int, int);
void resolve(int*, interval*, int);

int main(){
    
    ifstream in("input.txt");
    int L;
    in >> L;
    interval* list = new interval[L];
    for(int i = 0; i < L; i++){
        in >> list[i].s;
        in >> list[i].f;
    }
    in.close();

    long long* res = resolve(list, L);

    ofstream out("output.txt");
    if(res[0] == 0)
        out << 0;
    else
        out << res[0] << " " << res[1];
    out.close();
    delete[] res;
    return 0;
}

long long* resolve(interval* list, int len){

    interval* sortedList = mergeSort(list, 0, len);
    delete[] list;
    long long* res = new long long[2];
    res[0] = 0;
    res[1] = 0;
    
    int newLen = 0;
    interval* cleenList = new interval[len];
    intervalCP(cleenList[newLen++], sortedList[0]);
    for(int i = 1; i < len; i++){
        if(cleenList[newLen - 1].f < sortedList[i].s)
            intervalCP(cleenList[newLen++], sortedList[i]);
        else if(cleenList[newLen - 1].f < sortedList[i].f){
            cleenList[newLen - 1].f = sortedList[i].f;
        }
    }

    delete[] sortedList;
    
    for(int i = 0; i < newLen - 1; i++){
        if(cleenList[i + 1].s - cleenList[i].f > res[1] - res[0]){
            res[1] = cleenList[i + 1].s;
            res[0] = cleenList[i].f;
        }
    }

    delete[] cleenList;
    return res;
}

void intervalCP(interval& dest, interval& src){
    dest.s = src.s;
    dest.f = src.f;
    return;
}

interval* mergeSort(interval* a, int s, int f){

    int l = f - s;
    int f1 = s + l/2;

    if(l == 2){
        interval* r = new interval[2];
        if(a[s].s == a[s + 1].s){
            if(a[s].f < a[s + 1].f){
                intervalCP(r[0], a[s]);
                intervalCP(r[1], a[s + 1]);
            }
            else{
                intervalCP(r[0], a[s + 1]);
                intervalCP(r[1], a[s]);
            }
        }
        else if(a[s].s < a[s + 1].s){
            intervalCP(r[0], a[s]);
            intervalCP(r[1], a[s + 1]);        
        }
        else{
            intervalCP(r[0], a[s + 1]);
            intervalCP(r[1], a[s]);
        }
        return r;
    }
    else if(l == 1){
        interval* r = new interval[1];
        intervalCP(r[0], a[s]);
        return r;
    }
    interval* a1 = mergeSort(a, s, f1);
    interval* a2 = mergeSort(a, f1, f);
    return merge(a1, a2, f1 - s, f - f1);
}

interval* merge(interval* a1, interval* a2, int a1l, int a2l){
    int j = 0;
    int k = 0;

    interval* r = new interval[a1l + a2l];
    for(int i = 0; i < a1l + a2l; i++){
        if(j == a1l){
            intervalCP(r[i], a2[k++]);
            continue;
        }
        else if(k == a2l){
            intervalCP(r[i], a1[j++]);
            continue;
        }
        if(a1[j].s == a2[k].s){
            if(a1[j].f < a2[k].f)
                intervalCP(r[i], a1[j++]);
            else
                intervalCP(r[i], a2[k++]);
        }
        else if(a1[j].s < a2[k].s)
            intervalCP(r[i], a1[j++]);
        else
            intervalCP(r[i], a2[k++]);
    }
    delete[] a1;
    delete[] a2;
    return r;
}
