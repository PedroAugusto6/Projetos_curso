#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> pai,tam;
    int find(int x){
        if(pai[x]==x)return x;
        return pai[x]= find(pai[x]);
    }

    void add(int a,int b){
        int r1,r2;
        r1=find(a),r2=find(b);
        if(r1==r2)return;
        if(tam[r1]<tam[r2])swap(r1,r2);
        pai[r2]=r1;
        tam[r1]+=tam[r2];
    }

    int findCircleNum(vector<vector<int>>& isConnected) {
        int n=isConnected.size();
        set<int> validos;
        pai.resize(n);
        iota(pai.begin(),pai.end(),0);
        tam.assign(n,1);
        for(int i=0;i<n;i++){
            validos.insert(i);
            for(int j=0;j<n;j++){
                if(isConnected[i][j]==1){
                    add(i,j);
                    
                }
            }
        }
        int cont=0;
        for(int i=0;i<n;i++){
            if(validos.count(find(i))){
                cont++;
                validos.erase(find(i));
            }
        }

        return cont;
    }
};