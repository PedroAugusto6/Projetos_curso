#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> pai;

    int find(int x){
        if(pai[x]==x)return x;
        return pai[x]= find(pai[x]);
    }

    void add(int a, int b){
        int r1,r2;
        r1=find(a),r2 = find(b);
        if(r1==r2)return;
        if(r1>r2)swap(r1,r2);
        pai[r2]=r1;
    }


    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        int n=accounts.size();
        map<string,int> email;
        pai.resize(n);
        iota(pai.begin(),pai.end(),0);
        for(int i=0;i<n;i++){
            for(int j=1;j<accounts[i].size();j++){
                if(!email.count(accounts[i][j]))email.insert({accounts[i][j],i});
                else{
                    if(email[accounts[i][j]]!=i){
                        add(email[accounts[i][j]],find(i));
                    }
                }
            }
        }
        vector<vector<string>> merge(n);
        set <int> valido;
        map<int,int> pos;
        for(int i=0;i<n;i++){
            valido.insert(i);
        }
        int cont=0;
        for(int i=0;i<n;i++){
            if(valido.count(find(pai[i]))){
                merge[cont]=accounts[find(pai[i])];
                pos.insert({find(pai[i]),cont});
                valido.erase(find(pai[i]));
                cont++;
            }
            else{
                for(int j=1;j<accounts[i].size();j++){
                    if(email[accounts[i][j]]==i){
                        merge[pos[find(pai[i])]].push_back(accounts[i][j]);
                    }
                }
            }
        }
        merge.resize(cont);
        for(auto& conta : merge){
            sort(conta.begin()+1, conta.end());
            conta.erase(unique(conta.begin()+1, conta.end()), conta.end());
        }

        return merge;

    }
};