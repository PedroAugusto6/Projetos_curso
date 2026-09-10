#include <bits/stdc++.h>

using namespace std;

void dijkstra(int ori, int dest,int n,vector<vector<pair<int,int>>>& grafo,int& cont,int& peso){
    vector<int> dist(n,std::numeric_limits<int>::max());
    cont=0;
    dist[ori]=0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0,ori});
    while(!pq.empty()){
        auto[Peso_at,No_at]=pq.top();
        pq.pop();
        if(Peso_at>dist[No_at])continue;
        for(auto[Peso_Prox, No_prox] : grafo[No_at]){
            int prox_dist= dist[No_at] + Peso_Prox;
            if(dist[No_prox]>prox_dist){
                dist[No_prox]=prox_dist;
                pq.push({prox_dist,No_prox});
                if(No_prox==dest)cont=1;
            }
        }
        if(cont==1)peso=dist[dest];
    }

}

int main(){
    int N,n,m,s,t,a,b,w,cont,peso;
    cin>>N;
    for(int i=0;i<N;i++){
        cin>>n>>m>>s>>t;
        vector<vector<pair<int,int>>> grafo(n);
        int contador=0;
        for(int j=0;j<m;j++){
            cin>>a>>b>>w;
            if(a<n && b<n){
                grafo[a].push_back({w,b});
                grafo[b].push_back({w,a});
            }
        }
        //leu e pôs no grafo com os pesos das arestas
        dijkstra(s,t,n,grafo,cont,peso);
        cout<<"Case #"<<i+1<<": ";
        if(cont==1){
            cout<<peso<<endl;
        }
        else cout<<"unreachable"<<endl;
    }
}