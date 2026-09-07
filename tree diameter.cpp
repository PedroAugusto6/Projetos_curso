#include <bits/stdc++.h>

using namespace std;

void dfs(vector<vector<int>> & adj, vector<bool> & vis, int at,int profundidade ,int & maior_profundidade, int & no){
    vis[at]=true;
    if(profundidade>maior_profundidade){
        maior_profundidade=profundidade;
        no = at;
    }
    for(auto vou:adj[at]){
        if(!vis[vou]){
            dfs(adj,vis,vou,profundidade + 1,maior_profundidade,no);
        }
    }
}

int main(){
    int profundidade=0,maior_profundidade=0,n,i,a,b,no;
    cin>>n;
    vector<vector<int>> adj(n);
    vector<bool> vis(n);
    if(n>1){
        for(i=0;i<n-1;i++){
            cin>>a>>b;
            adj[a-1].push_back(b-1);
            adj[b-1].push_back(a-1);
        }
        dfs(adj,vis,0,profundidade,maior_profundidade,no);
        vis.assign(n, false);
        profundidade=0;
        maior_profundidade=0;
        dfs(adj,vis,no,profundidade,maior_profundidade,no);
        cout<<maior_profundidade<<endl;
    }
    else cout<<'0'<<endl;
}