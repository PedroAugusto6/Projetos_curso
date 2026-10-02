#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> pai,tam;
    int find(int x){
       if(pai[x]==x)return x;
       return pai[x]=find(pai[x]);
    }
    void add(int a,int b){
        int r1,r2;
        r1=find(a),r2=find(b);
        if(r1==r2)return;
        if(tam[r1]<tam[r2])swap(r1,r2);
        pai[r2]=r1;
        tam[r1]+=tam[r2];
    }

    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        pai.resize(n);
        tam.resize(n);
        tam.assign(n,1);
        iota(pai.begin(),pai.end(),0);
        for(auto fi : edges){
            add(fi[0],fi[1]);
        }
        if(find(destination) == find(source))return true;
        return false;
    }
};