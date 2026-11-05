#include <bits/stdc++.h>

using namespace std;

#define ll long long int


int main(){
    cin.tie(0)->sync_with_stdio(0);
    ll n,q,x,y,d;
    cin>>n>>q;
    vector<ll> price(n),p(n);
    for(int i=0;i<n;i++){
        cin>>d;
        price[i]=d;
    }
    sort(price.rbegin(),price.rend());
    ll soma=0;
    for(int i=0;i<n;i++){
        p[i]=soma+price[i];
        soma=p[i];
    }
    while(q--){
        cin>>x>>y;
        if(x>y){
            ll aux=p[x-1]-p[(x-1)-y];
            cout<<aux<<'\n';
        }
        else cout<<p[x-1]<<'\n';
    }


}