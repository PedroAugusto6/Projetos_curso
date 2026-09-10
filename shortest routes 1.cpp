#include <bits/stdc++.h>

using namespace std;

void dijkstra(vector<vector<pair<long long int, long long int>>>& adj, vector<long long int> dist, int n){
    priority_queue<pair<long long int, long long int>, vector<pair<long long int, long long int>>, greater<pair<long long int, long long int>>> pq; 
    pq.push({0,1});
    while(!pq.empty()){
        auto [peso_atual, no_atual]=pq.top();
        pq.pop();
        if(peso_atual>dist[no_atual])continue;
        for(auto[peso_prox, no_prox] : adj[no_atual]){
            long long int dis= dist[no_atual]+peso_prox;
            if( dist[no_prox]>dis){
                dist[no_prox]=dis;
                pq.push({dis,no_prox});
            }
        }
    }
    cout<<dist[1];
    for(int i=2;i<=n;i++){
        cout<<' '<<dist[i];
    }
    cout<<endl;

}

int main(){
    long long int n,m,i,a,b,c;
    cin>>n>>m;
    vector<long long int> dist(n+1,std::numeric_limits<long long int>::max());
    vector<vector<pair<long long int,long long int>>> adj(n+1);
    dist[1]=0;
    for(i=0;i<m;i++){
        cin>>a>>b>>c;
        adj[a].push_back({c,b});
    }
    dijkstra(adj,dist,n);
}