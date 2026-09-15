#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

const ll INF = numeric_limits<ll>::max() / 4;

void dijkstra(ll n, ll m, vector<vector<pair<ll,ll>>>& adj_a, vector<vector<pair<ll,ll>>>& adj_b,vector<tuple<ll,ll,ll>>& arestas){
    vector<ll> dist_a(n+1, INF),dist_b(n+1, INF);
    priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, greater<pair<ll,ll>>> pq;
    dist_a[1]=0;
    pq.push({0,1});
    while(!pq.empty()){
        auto[peso_atual,no_atual]=pq.top();
        pq.pop();
        if(peso_atual>dist_a[no_atual])continue;
        for(auto [peso_prox,no_prox] : adj_a[no_atual]){
            ll dis=dist_a[no_atual]+peso_prox;
            if(dist_a[no_prox]>dis){
                dist_a[no_prox]=dis;
                pq.push({dis,no_prox});
            }
        }
    }
    dist_b[n]=0;
    pq.push({0,n});
    while(!pq.empty()){
        auto[peso_atual,no_atual]=pq.top();
        pq.pop();
        if(peso_atual>dist_b[no_atual])continue;
        for(auto [peso_prox,no_prox] : adj_b[no_atual]){
            ll dis=dist_b[no_atual]+peso_prox;
            if(dist_b[no_prox]>dis){
                dist_b[no_prox]=dis;
                pq.push({dis,no_prox});
            }
        }
    }
    ll menor=INF;
    for(ll i=0;i<m;i++){
        auto[A,B,C]=arestas[i];
        auto aux=dist_a[A]+dist_b[B]+(C/2);
        if(aux < menor)menor=aux;
    }

    cout<<menor<<endl;

}

int main(){
    ll n,m,a,b,c;
    cin>>n>>m;
    vector<vector<pair<ll,ll>>> adj_a(n+1),adj_b(n+1);
    vector<tuple<ll,ll,ll>> arestas(m);
    for(ll i=0;i<m;i++){
        cin>>a>>b>>c;
        adj_a[a].push_back({c,b});
        adj_b[b].push_back({c,a});
        arestas[i]={a,b,c};
    }
    dijkstra(n,m,adj_a,adj_b,arestas);
}