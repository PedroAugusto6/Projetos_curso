#include <bits/stdc++.h>

using namespace std;

void kahn(queue<int>& s, vector<int>& L,vector<int>& filho,vector<vector<int>>& tree){
    while(!s.empty()){
        int aux=s.front();
        L.push_back(aux);
        s.pop();
        for(auto at : tree[aux]){
            filho[at]-=1;
            if(filho[at]<1){
                s.push(at);
            }
        }
    }
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    int n,m,a,b;
    cin>>n>>m;
    while(n!=0||m!=0){
        vector<vector<int>> tree(n+1);
        vector<int> filho(n+1,0);
        for(int i=0;i<m;i++){
            cin>>a>>b;
            tree[a].push_back(b);
            filho[b]++;
        }
        vector<int> L;
        queue<int> s;
        for(int i=1;i<=n;i++){
            if(filho[i]==0)s.push(i);
        }
        kahn(s,L,filho,tree);
        int t = L.size();
        cout<<L[0];
        for(int i=1;i<t;i++)
            cout<<' '<<L[i];
        cout<<'\n';
        cin>>n>>m;
    }
}