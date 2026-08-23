#include <bits/stdc++.h>

using namespace std;

void bfs(int inicio, vector<vector<int>>& rotas, vector<bool>& visitado, int* ultimo, set<int>& cities){
    queue <int> fila;
    fila.push(inicio);
    visitado[inicio]=true;
    *ultimo= inicio;
    cities.erase(inicio);
    while(!fila.empty()){
        int u=fila.front();
        fila.pop();

        for(int vizinho: rotas[u]){
            if(!visitado[vizinho]){
                visitado[vizinho]=true;
                fila.push(vizinho);
                *ultimo=vizinho;
                cities.erase(vizinho);
            }
        }
    }
}

int main(){
    int n,m,a,b;
    cin>>n>>m;
    vector<vector<int>> rotas(n+1);
    set<int> cities;
    for(int i=0;i<m;i++){
        cin>>a>>b;
        rotas[a].push_back(b);
        rotas[b].push_back(a);
    }
    for(int i=1;i<=n;i++)cities.insert(i);
    vector<bool> visitados(n+1,false);
    visitados[0]=true;
    int ultimo;
    set<int>::iterator it=cities.begin();
    queue<int> road;
    while(!cities.empty()){
        bfs(*it,rotas,visitados,&ultimo,cities);
        if(!cities.empty()){
            it=cities.begin();
            road.push(ultimo);
            road.push(*it);
        }
    }
    int t=(road.size()/2);
    cout<<t<<endl;
    for(int i=0;i<t;i++){
        cout<<road.front();
        road.pop();
        cout<<' '<<road.front();
        road.pop();
        cout<<endl;
    }
    
}