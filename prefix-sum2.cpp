#include <bits/stdc++.h>

using namespace std;

#define ll long long int

int main(){
    cin.tie(0)->sync_with_stdio(0);
    ll t,x,y,z;
    cin>>t;
    while(t--){
        ll n,q;
        cin>>n>>q;
        vector<ll> number(n),p(n);
        cin>>number[0];
        p[0]=number[0];
        for(int i=1;i<n;i++){
            cin>>number[i];
            p[i]=number[i]+p[i-1];
        }
        for(int i=0;i<q;i++){
            cin>>x>>y>>z;
            x-=1,y-=1;
            ll aux=p[n-1]-p[y];
            if(x>=1)aux+=p[x-1];
            aux+=z*(y-x + 1);
            if(aux%2==1)cout<<"YES"<<'\n';
            else cout<<"NO"<<'\n';
        }
    }
}