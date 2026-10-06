#include <bits/stdc++.h>

using namespace std;

class Solution {
public:

    vector<int> pai,tam;

    int find(int x){
        if(pai[x]==x)return x;

        return pai[x]= find(pai[x]);
    }

    void add(int a, int b){
        int r1,r2;
        r1=find(a),r2=find(b);
        if(r1==r2)return;
        if(tam[r1]<tam[r2])swap(r1,r2);
        pai[r2]=r1;
        tam[r1]+=tam[r2];
    }
    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        vector<int> aresta(n);
        int nc=0;
        pai.resize(n);
        tam.resize(n);
        iota(pai.begin(),pai.end(),0);
        tam.assign(n,1);
        aresta.assign(n,0);
        for(auto parent : edges){
            add(parent[0],parent[1]);
        }
        for(auto parent : edges){
            aresta[find(parent[0])]+=1;
        }
        for(int i=0;i<n;i++){
            if(find(i) == i && aresta[i]==tam[i]*(tam[i]-1)/2)nc++;
        }
        return nc;
    }
};