#include <bits/stdc++.h>

using namespace std;

#define ll long long int

    ll inversa(const vector<ll>& pb, ll a, ll b){
        return pb[b-1]-pb[a-1];
    }

    ll original(const vector<ll>& p, ll a, ll b){
        return p[b-1]-p[a-1];
    }

int main(){
    cin.tie(0)->sync_with_stdio(0);

    ll n,m,a,b;
    cin>>n>>m;
    vector<ll> fila(n),p(n,0),pb(n,0);
    cin>>fila[0];
    for(int i=1;i<n;i++){
        cin>>fila[i];
        ll aux=0;
        if(fila[i]<fila[i-1]){
            aux = fila[i-1]-fila[i];
        }
        p[i]=p[i-1]+aux;
    }
    for(int i=n-2;i>=0;i--){
        ll aux=0;
        if(fila[i]<fila[i+1]){
            aux=fila[i+1]-fila[i];
        }
        pb[i]=aux+pb[i+1];
    }
    for(int i=0;i<m;i++){
        cin>>a>>b;
        ll aux;
        if(a>b)aux=inversa(pb,a,b);
        else aux=original(p,a,b);
        cout<<aux<<'\n';

    }

}