#include <bits/stdc++.h>

using namespace std;


int main(){
    int n,m;
    cin>>n>>m;
    pair<int,int> inicio={0,0}, fim={0,0};
    char mapa[n][m];
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>mapa[i][j];
            if(mapa[i][j]=='A')inicio={i,j};
            if(mapa[i][j]=='B')fim={i,j};
        }
    }
    int dl[4]={-1,0,1,0};
    int dc[4]={0,-1,0,1};
         //  u, l,d,r
    int l=inicio.first, c = inicio.second;
    //guarda as coordenadas de onde vai começar a busca
    queue<pair<int,int>> prox;
    //guarda a proxima celula a ser visitada;
    prox.push({inicio.first,inicio.second});
    //inicializa a fila;
    pair<int,int> atual;
    //armazena a celula atual;
    map <pair<int,int>,pair<int,int>> filhos;
    //é o grafo de coordenadas;
    while(!prox.empty() && (l!=fim.first || c!=fim.second)){
        atual= prox.front();
        prox.pop();
        l=atual.first;
        c=atual.second;
        for(int i=0;i<4;i++){
            if(((l+dl[i]>=0) && (c+dc[i]>=0) && (l+dl[i] < n) && (c+dc[i] < m)) && (mapa[l+dl[i]][c+dc[i]]=='.' || mapa[l+dl[i]][c+dc[i]]=='B')){
                prox.push({l+dl[i],c+dc[i]});
                filhos[{l+dl[i],c+dc[i]}]={l,c};
                mapa[l+dl[i]][c+dc[i]]='#';
            }
        }
    }
    if(l!=fim.first && c!=fim.second)cout<<"NO"<<endl;
    else{
        int contador=0;
        deque<char> rota;
        cout<<"YES"<<endl;
        while(l!= inicio.first || c!=inicio.second){
            atual=filhos.at({l,c});
            if(atual.first<l){
                rota.push_front('D');
            }
            else{
                if(atual.second<c){
                    rota.push_front('R');
                }
                else{
                    if(atual.first>l){
                        rota.push_front('U');
                    }
                    else{
                        rota.push_front('L');
                    }
                }
            }
            contador++;
            l=atual.first;
            c=atual.second;

        }
        cout<<contador<<endl;
        while(!rota.empty()){
            cout<<rota.front();
            rota.erase(rota.begin());
        }
        cout<<endl;
    }
    
}
