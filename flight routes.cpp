#include<bits/stdc++.h>

using namespace std;

typedef long long int ll;
const ll INF = numeric_limits<ll>::max() / 4;

void dijkstra(int k,ll n,ll m,vector<vector<pair<ll,ll>>>& adj){
    vector<vector<ll>> dist(n+1);
    priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, greater<pair<ll,ll>>> pq;
    dist[1].push_back(0);
    pq.push({0,1});
    while(!pq.empty()){
        auto[peso_atual,no_atual]=pq.top();
        pq.pop();
        sort(dist[no_atual].rbegin(),dist[no_atual].rend());
        if(peso_atual>dist[no_atual][0] && (int)dist[no_atual].size()==k )continue;
        for( auto[peso_prox,no_prox]: adj[no_atual]){
            ll dis=peso_atual+peso_prox;
            if((int)dist[no_prox].size()<k){
                dist[no_prox].push_back(dis);
                pq.push({dis,no_prox});
            }
            else{
                if(dist[no_prox][0]>dis){
                    dist[no_prox][0]=dis;
                    pq.push({dis,no_prox});
                }
            }
            sort(dist[no_prox].rbegin(),dist[no_prox].rend());
        }
        
    }
    sort(dist[n].begin(),dist[n].end());
    cout<<dist[n][0];
    for(int i=1;i<k;i++){
        cout<<' '<<dist[n][i];
    }
    cout<<endl;

}

int main(){

    ll n,m,a,b,c;
    int k;
    cin>>n>>m>>k;
    vector<vector<pair<ll,ll>>> adj(n+1);
    for(ll i=0;i<m;i++){
        cin>>a>>b>>c;
        adj[a].push_back({c,b});
    }
    dijkstra(k,n,m,adj);

}