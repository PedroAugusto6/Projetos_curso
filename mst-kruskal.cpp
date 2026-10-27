#include <bits/stdc++.h>

using namespace std;

vector<int> pai,tam;


int find(int x){
    if(pai[x]==x)return x;
    return pai[x]=find(pai[x]);
}

bool add(int a,int b){
    int r1=find(a),r2=find(b);
    if(r1==r2)return false;
    if(tam[r1]<tam[r2])swap(r1,r2);
    tam[r1]+=tam[r2];
    pai[r2]=pai[r1];
    return true;
}


int main()
{
    int n,m,u,v,w,M;
    cin>>n>>m;
    vector<int> lixo;
    vector<tuple<int,int,int>> ordem;
    while(n!=0 || m!=0){
        M=m;
        pai.resize(n);
        tam.assign(n,1);
        iota(pai.begin(),pai.end(),0);
        while(M--){
            cin>>u>>v>>w;
            ordem.push_back({w,u,v});
        }
        int it=0;
        sort(ordem.begin(),ordem.end());
        M=m;
        int cont=0;
        while(M--){
            auto[a,b,c]=ordem[it];
            it++;
            if(!add(b,c)){
                lixo.push_back(a);
                cont++;
            }   
        }
        if(cont==0)cout<<"forest";
        else{
            cout<<lixo[0];
            int pos=1;
            cont-=1;
            while(cont--){
                cout<<' '<<lixo[pos];
                pos++;
            }
        }
        cout<<endl;

        lixo.clear();
        ordem.clear();
        cin>>n>>m;
    }
    
    return 0;
}
