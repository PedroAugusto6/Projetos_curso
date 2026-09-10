#include <bits/stdc++.h>

using namespace std;

void dijkstra(long long int& ori, vector<vector<pair<int,int>>>& adj,map<int,int>& filhos,int n){
    priority_queue<pair<long long int,long long int>, vector<pair<long long int,long long int>>, greater<pair<long long int,long long int>>> pq; 
    vector<long long int> dist(n+1,-1);
    dist[1]=0;
    pq.push({0,1});
    while(!pq.empty()){
        auto [a,b]=pq.top();
        pq.pop();
        if(a>dist[b] && dist[b]!=-1)continue;
        for(auto[i,j]:adj[b]){
            long long int dis= dist[b]+i;
            if(dist[j]>dis || dist[j]==-1){
                dist[j]=dis;
                pq.push({dis,j});
                filhos[j]=b;
            }
        }
    }
    ori=dist[n];

}

int main(){
    int n,m,ai,bi,ci;
    long long int ori=0;
    cin>>n>>m;
    map<int,int> filhos;
    vector<vector<pair<int,int>>> adj(n+1);
    for(int i=0;i<m;i++){
        cin>>ai>>bi>>ci;
        adj[ai].push_back({ci,bi});
        adj[bi].push_back({ci,ai});
    }
    dijkstra(ori,adj,filhos,n);
    if(ori!=-1){
        ori=n;
        deque<int> ordem;
        while(ori!=1){
            ordem.push_front(ori);
            ori=filhos[ori];
        }
        cout<<'1';
        while(!ordem.empty()){
            cout<<' '<<ordem.front();
            ordem.pop_front();
        }
    }
    else cout<<-1;

    cout<<endl;


}