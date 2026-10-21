#include <bits/stdc++.h>

using namespace std;

vector<int> pai,tam;

int find(int x){
    if(pai[x]==x)return x;
    return pai[x]=find(pai[x]);
}

bool add(int a, int b){
    int r1,r2;
    r1=find(a),r2=find(b);
    if(r1==r2)return false;
    if(tam[r1]>tam[r2])swap(r1,r2);
    pai[r2]=r1;
    tam[r1]+=tam[r2];
    return true;
}

int main(){
    int n,m,a,b;
    cin>>n>>m;
    pai.resize(n+1);
    iota(pai.begin(),pai.end(),0);
    tam.assign(n+1,1);
    priority_queue<int> size;
    while(m--){
        cin>>a>>b;
        if(add(a,b)){
            n--;
            if(tam[find(a)]<tam[find(b)])swap(a,b);
            size.push(tam[find(a)]);
        }
        cout<<n<<' '<<size.top()<<endl;

    }
}