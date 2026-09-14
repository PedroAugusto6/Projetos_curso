#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long int ll;
 
typedef long double dl;
 
void dijkstra(vector<vector<pair<ll, ll>>>& adj, vector<dl>& dist, int n){
    priority_queue<pair<dl, ll>, vector<pair<dl, ll>>, greater<pair<dl, ll>>> pq; 
    pq.push({0,1});
    while(!pq.empty()){
        auto [peso_atual, no_atual]=pq.top();
        pq.pop();
        if(peso_atual>dist[no_atual])continue;
        for(auto[peso_prox, no_prox] : adj[no_atual]){
            dl dis= dist[no_atual] + (logl(peso_prox)/logl(7.0));
            if( dist[no_prox]>dis){
                dist[no_prox]=dis;
                pq.push({dis,no_prox});
            }
        }
    }
 
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n,m,a,b,c;
    cin>>n>>m;
    vector<vector<pair<ll,ll>>> adj(n+1);
    vector<dl> dist(n+1,std::numeric_limits<dl>::max());
    dist[1]=0;
    for(ll i=0;i<m;i++){
        cin>>a>>b>>c;
        adj[a].push_back({c,b});
        adj[b].push_back({c,a});
    }
    dijkstra(adj,dist,n);
    cout<<fixed<<setprecision(15)<<dist[n];
    cout<<endl;
}