#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

void dijkstra(int n,vector<vector<pair<ll,ll>>>& adj,map<ll,ll>& filhos){
    priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, greater<pair<ll,ll>>> pq;
    vector<ll> dist_a(n,numeric_limits<ll>:: max());
    vector<ll> dist_b(n,numeric_limits<ll>:: max());

    dist_b[1]=0;
    pq.push({0,1});
    while(!pq.empty()){
        auto[a,b]=pq.top();
        pq.pop();
        if(a>dist_b[b])continue;
        for(auto[i,j]:adj[b]){
            ll dis= a+i;
            if(dist_b[j]>dis){
            dist_b[j]=dis;
            pq.push({dis,j});
            filhos[j]=b;
            }
        }
    }
    ll placas[n][2];
    for(ll j=0;j<n;j++)placas[j][1]={numeric_limits<ll>::max()};
    for(ll i=0;i<n;i++){
        for(auto[a,b]:adj[i]){
            ll custo = a + dist_b[b]; 
            if(custo<placas[i][1]){
                placas[i][0]=b;
                placas[i][1]=custo;
            }
        }
    }

    dist_a[0]=0;
    pq.push({0,0});
    while(!pq.empty()){
        auto[a,b]=pq.top();
        pq.pop();
        if(a>dist_a[b])continue;
        for(auto[i,j]:adj[b]){
            if(j!=placas[b][0]){
                ll dis= a+i;
                if(dist_a[j]>dis){
                    dist_a[j]=dis;
                    pq.push({dis,j});
                    filhos[j]=b;
                }
            }
        }
    }

}

int main(){
    ll n,m,a,b,c;
    cin>>n>>m;
    vector<vector<pair<ll,ll>>> adj(n);
    map<ll,ll> filhos;
    ll placas[n][2];
    for(ll i=0;i<m;i++){
        cin>>a>>b>>c;
        adj[a].push_back({c,b});
        adj[b].push_back({c,a});
    }
    filhos[1]=-1;
    dijkstra(n,adj,filhos);
    if(filhos[1]==-1)cout<<"impossible";
    else{
        deque<ll> path;
        ll aux=1;
        path.push_front(aux);
        do{
            path.push_front(filhos[aux]);
            aux=filhos[aux];
        }while(aux!=0);
        cout<<(int)path.size()<<' ';
        while(!path.empty()){
            cout<<' '<<path.front();
            path.pop_front();
        }
    }
    cout<<endl;

}