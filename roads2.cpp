#include <bits/stdc++.h>
 
using namespace std;
 
vector<int>pai,tam;
 
int acha(int x){
    if(pai[x]==x)return x;
    return pai[x]=acha(pai[x]);
}
 
bool add(int a,int b){
    int r1=acha(a),r2=acha(b);
    if(r1==r2)return false;
    if(tam[r1]<tam[r2])swap(r1,r2);
    pai[r2]=r1;
    tam[r1]+=tam[r2];
    return true;
}
 
void excluir(int a,set<int>& ordem){
    set<int>::iterator it;
    it=ordem.find(a);
    ordem.erase(it);
    
}
 
int main(){
    int n,a,b,d=0;
    cin>>n;
    tam.assign(n+1,1);
    pai.resize(n+1);
    set<int> ordem;
    priority_queue<pair<int,int>>prioridade;
    for(int i=1;i<=n;i++)ordem.insert(i);
    iota(pai.begin(),pai.end(),0);
    queue<pair<int,int>> constructions;
    for(int i=0;i<n-1;i++){
        cin>>a>>b;
        if(!add(a,b)){
            constructions.push({a,b});
            d++;
        }
        else{
            prioridade.push({tam[acha(a)],acha(a)});
            prioridade.push({tam[acha(b)],acha(b)});
        }
    }
    for(int i=1;i<=n;i++){
        if(pai[i]!= i){
            excluir(i,ordem);
        }
    }
    set<int>:: iterator pos=ordem.begin();
    cout<<d<<endl;
    d+=1;
    while(d--){
        if(add(prioridade.top().second,*pos)){
            cout<<constructions.front().first<<' '<<constructions.front().second<<' '<<prioridade.top().second<<' '<<*pos<<endl;
            constructions.pop();
            int aux=prioridade.top().second;
            prioridade.pop();
            prioridade.push({tam[acha(aux)], aux});
 
        }
        pos++;
 
    }
    
}
