#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> pai,tam;
    int find(int x){
        if(pai[x]==x) return x;
        return pai[x] = find(pai[x]);
    }

    void add(int a, int b){
        int r1,r2;
        r1=find(a),r2=find(b);
        if(r1==r2)return;
        if(tam[r1]<tam[r2])swap(r1,r2);
        pai[r2]=r1;
        tam[r1]+=tam[r2];
    }

    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        pai.resize(n+1),tam.resize(n+1);
        iota(pai.begin(),pai.end(),0);
        tam.assign(n+1,1);
        vector<int> last(2);
        for(auto fi : edges){
            if(find(fi[0]) == find(fi[1])){
                last[0]=fi[0],last[1]=fi[1];
            }
            add(fi[0],fi[1]);
        }
        return last;
    }
};