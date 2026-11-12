#include <bits/stdc++.h>

using namespace std;
void kahn(queue<int>& s, vector<int>& L,vector<int>& filho,vector<vector<int>>& adj){
    while(!s.empty()){
        int aux=s.front();
        L.push_back(aux);
        s.pop();
        for(auto at : adj[aux]){
            filho[at]-=1;
            if(filho[at]<1){
                s.push(at);
            }
        }
    }
}

int main(){
    int n,m,a,b;
    cin>>n>>m;
    while(n!=0 || m!=0){
        int r=m;
        queue<int> s;
        vector<vector<int>> adj(n+1);
        vector<int> filho(n+1,0);
        while(r--){
            cin>>a>>b;
            adj[a].push_back(b);
            filho[b]++;
        }
        for(int i=1;i<=n;i++){
            if(filho[i]==0)s.push(i);
        }
        vector<int> L;
        kahn(s,L,filho,adj);
        int t=L.size();
        if(t==0)cout<<"IMPOSSIBLE"<<'\n';
        else{
            for(int i=0;i<n;i++){
                cout<<L[i]<<'\n';
            }
        }
        cin>>n>>m;
    }

}