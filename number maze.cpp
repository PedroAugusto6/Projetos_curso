#include <bits/stdc++.h>

using namespace std;

typedef tuple<int,int,int> item;

void dijkstra(int n, int m, vector<vector<int>>& matriz){
    priority_queue<item, vector<item>, greater<item>> pq;
    vector<vector<int>> dist(n+1,vector<int>(m+1, std::numeric_limits<int>::max()));
    dist[1][1]=matriz[1][1];
    pq.push({dist[1][1],1,1});
    int dl[4]={-1, 1, 0, 0};
    int dc[4]={0, 0, -1, 1};
    while(!pq.empty()){
        auto[custo,linha,coluna]=pq.top();
        pq.pop();
        if(custo>dist[linha][coluna])continue;
        for(int i=0;i<4;i++){
            int l=linha+dl[i];
            int c=coluna+dc[i];
            if(l>=1 && l<=n && c>=1 && c<=m){
                int dis=dist[linha][coluna]+matriz[l][c];
                if(dist[l][c]>dis){
                    dist[l][c]=dis;
                    pq.push({dist[l][c],l,c});
                }
            }
        }

    }
    cout<<dist[n][m]<<endl;

}

int main(){
    int t,n,m,v,i,j;
    cin>>t;
    while(t--){
        cin>>n>>m;
        vector<vector<int>> matriz(n+1,vector<int>(m+1));
        for(i=1;i<=n;i++){
            for(j=1;j<=m;j++){
                cin>>v;
                matriz[i][j]=v;
            }
        }
        dijkstra(n,m,matriz);
    }
}