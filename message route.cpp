#include <bits/stdc++.h>

using namespace std;

void bfs(int inicio, vector<vector<int>>& rotas, vector<bool>& visitado, vector<vector<int>>& pais, int n){
    queue <int> fila;
    fila.push(inicio);
    visitado[inicio]=true;
    while(!fila.empty()){
        int u=fila.front();
        fila.pop();

        for(int vizinho: rotas[u]){
            if(!visitado[vizinho]){
                visitado[vizinho]=true;
                fila.push(vizinho);
                pais[vizinho].push_back(u);
                if(vizinho==n || u==n)break;
            }
        }
    }
}

int main(){
    int n,m,a,b;
    cin>>n>>m;
    vector<vector<int>> rotas(n+1);
    vector<vector<int>> pais(n+1);
    vector<bool> visitado(n+1,false);
    visitado[0]=true;
    for(int i=0;i<m;i++){
        cin>>a>>b;
        rotas[a].push_back(b);
        rotas[b].push_back(a);
    }
    bfs(1,rotas,visitado,pais,n);
    if(visitado[n]==false){
        cout<<"IMPOSSIBLE"<<endl;
        return 0;
    }
    int atual=n;
    stack<int> ordem;
    for(int i=0;i<n;i++)visitado[i]=false;
    while(atual!=1){
        visitado[atual]=true;
        ordem.push(atual);
        atual=pais[atual][0];
    }

    int t=ordem.size();
    cout<<t + 1<<endl;
    cout<<1;
    while(!ordem.empty()){
        cout<<' '<<ordem.top();
        ordem.pop();
    }
    cout<<endl;
}