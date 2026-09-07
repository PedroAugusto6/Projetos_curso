#include <bits/stdc++.h>

using namespace std;

void dfs(vector<vector<int>>& adj,vector<bool>& vis,set<int>& primeiro, int at){
    vis[at]=true;
    if(primeiro.find(at) != primeiro.end())primeiro.erase(at);
    for(auto vou : adj[at]){
        if(!vis[vou]){
            dfs(adj,vis,primeiro,vou);
        }
    }
}

int main(){
    int n,l,end,i,s;
    char fim,a,b;
    string linha;
    cin>>n;
    getline(cin, linha);
    while(n>0){
        cin>>fim;
        getline(cin,linha);
        s=0;
        end = fim - 'A';
        vector<vector<int>> adj(end + 1);
        set<int> primeiro;
        for (i = 0; i <= end; i++){
            primeiro.insert(i);
        }
        while (true) {
            getline(cin,linha);
            if (linha.empty() )break;
            a = linha[0];
            b = linha[1];
            int p = a - 'A';
            int d = b - 'A';
            adj[p].push_back(d);
            adj[d].push_back(p);
        }
        while(primeiro.empty()==false){
            vector<bool> vis(end + 1);
            auto it=primeiro.begin();
            int P = *it;
            dfs(adj,vis,primeiro,P);
            s++;
        }
        cout<<s<<endl;
        if(n>1)cout<<endl;
        n--;
    }
}