#include <bits/stdc++.h>

using namespace std;

vector<vector<pair<int,int>>> pai;
vector<vector<int>> tam;

pair<int,int> find(pair<int,int> pos){
    if(pai[pos.first][pos.second]== pos)return pos;
    return pai[pos.first][pos.second]=find(pai[pos.first][pos.second]);
}

 void add(pair<int,int> a,pair<int,int> b){
    pair<int,int> r1=find(a),r2=find(b);
    if(r1==r2)return;
    if(tam[r1.first][r1.second]<tam[r2.first][r2.second])swap(r1,r2);
    pai[r2.first][r2.second]=pai[r1.first][r1.second];
    tam[r1.first][r1.second]+=tam[r2.first][r2.second];
    return;
}

int l[4]={-1,1,0,0};

int c[4]={0,0,-1,1};

void bfs(int x,int y,const vector<string>& m,vector<vector<bool>>& vis,int N,int M){
    queue<pair<int,int>> fila;
    fila.push({x,y});
    vis[x][y]=true;
    while(!fila.empty()){
        auto[a,b]=fila.front();
        fila.pop();
        int cont=0;
        for(int i=0;i<4;i++){
            if(a+l[i]<0||b+c[i]<0||a+l[i]>=N|| b+c[i]>=M) continue;
            if(m[a+l[i]][b+c[i]]=='.'){
                    if(vis[a+l[i]][b+c[i]]==false){
                    fila.push({a+l[i],b+c[i]});
                }
            }
            else{
                cont++;
            }
            tam[a][b]=cont;
            vis[a+l[i]][b+c[i]]=true;
        }
        pair<int,int> old={x,y},novo={a,b};
        add(old,novo);
    }
}

int main(){
    int N,M,K,x,y;
    cin>>N>>M>>K;
    vector<string> m(N);
    char s;
    vector<vector<bool>> vis(N, vector<bool> (M,false));
    pai.assign(N,vector<pair<int,int>>(M));
    tam.assign(N, vector<int>(M,0));
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            cin>>s;
            m[i].push_back(s);
            pai[i][j]={i,j};
        }
    }
    for(int i=0;i<K;i++){
        cin>>x>>y;
        x-=1;
        y-=1;
        if(!vis[x][y])bfs(x,y,m,vis,N,M);
        pair<int,int> aux=find(pai[x][y]);
        cout<<tam[aux.first][aux.second]<<'\n';
    }
    
}