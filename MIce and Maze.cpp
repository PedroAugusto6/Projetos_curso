#include <bits/stdc++.h>

using namespace std;

void dijkstra(int ori, int dest, vector<vector<pair<int,int>>>& adj, int n, int t, int& ratos){
    vector<int> dist(n+1, std::numeric_limits<int>:: max());
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    dist[ori]=0;
    pq.push({0,ori});
    while(!pq.empty()){
        auto[peso_atual,no_atual]=pq.top();
        pq.pop();
        if(peso_atual>dist[no_atual])continue;
        for(auto [peso_prox,no_prox] : adj[no_atual]){
            int dis=dist[no_atual]+peso_prox;
            if(dist[no_prox]>dis){
                dist[no_prox]=dis;
                pq.push({dis,no_prox});
            }
        }
    }
    if(dist[dest]<=t)ratos+=1;

}

int main(){
    int c,n,e,t,m,a,b,C,ratos,linha=0;
    cin>>c;
    while(c--){
        ratos=0;
        cin>>n>>e>>t>>m;
        vector<vector<pair<int,int>>> adj(n+1);
        for(int i=1;i<=m;i++){
            cin>>a>>b>>C;
            adj[a].push_back({C,b});
            //grafo construido com pesos nas arestas
        }
        for(int i=1;i<=n;i++){
            if(i==e){
                ratos+=1;
            }
            else{
                dijkstra(i,e,adj,n,t,ratos);
            }
        }
        if(linha>=1)cout<<' '<<endl;
        cout<<ratos<<endl;
        linha+=1;

    }
}