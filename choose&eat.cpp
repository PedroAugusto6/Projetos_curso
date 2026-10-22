#include <bits/stdc++.h>

using namespace std;

#define ll long long int

vector<ll> pai,tam;

int find(ll x){
    if(pai[x]==x)return x;
    return pai[x]=find(pai[x]);
}

bool add(ll a,ll b){
    ll r1,r2;
    r1=find(a),r2=find(b);
    if(r1==r2)return false;
    if(tam[r1]<tam[r2])swap(r1,r2);
    pai[r2]=r1;
    tam[r1]+=tam[r2];
    return true;
}


ll potenciacaoModular(ll base, ll expoente, ll modulo) {
    ll resultado = 1;

    // Atualiza a base caso ela seja maior ou igual ao módulo
    base = base % modulo;

    while (expoente > 0) {
        // Se o expoente for ímpar, multiplica a base com o resultado
        if (expoente % 2 == 1) {
            resultado = (resultado * base) % modulo;
        }

        // Expoente deve ser par agora
        expoente = expoente / 2;
        base = (base * base) % modulo;
    }
    return resultado;
}

int main(){
    ll n,m,a,total=0;
    priority_queue<pair<ll,pair<ll,ll>>> pesos;
    cin>>n>>m;
    vector<ll> p;
    pai.resize(n);
    iota(pai.begin(),pai.end(),0);
    tam.assign(n,1);
    for(ll i=0;i<n;i++){
        cin>>a;
        p.push_back(a);
    }
    for(ll i=0;i<n;i++){
        for(ll j=i+1;j<n;j++){
            ll aux = (potenciacaoModular(p[i],p[j],m) + potenciacaoModular(p[j],p[i],m))%m;
            pair<ll,ll> AUX={i,j};
            pesos.push({aux,AUX});
        }
    }
    ll cont=0;
    do{
        auto[a,b]=pesos.top();
        pesos.pop();
        if(add(b.first,b.second)){
            cont+=1;
            total+=a;
        }
    }while(cont!=(n-1));

    cout<<total<<endl;
    
}