#include <bits/stdc++.h>

using namespace std;

class Solution {
public:

    vector<char> pai;
    vector<int> tam;
    char find(char x){
        if(pai[x-97]==x)return x;
        return pai[x-97]=find(pai[x-97]);
    }

    void add(char a, char b){
        char r1 = find(a), r2 = find(b);
        if(r1==r2)return;
        if(tam[r1-97]<tam[r2-97])swap(r1,r2);
        pai[r2-97]=r1;
        tam[r1-97]+=tam[r2-97];
    }

    bool equationsPossible(vector<string>& equations) {
        pai.resize(26);
        tam.assign(26,1);
        iota(pai.begin(),pai.end(),'a');
        for(auto letra : equations){
            if(letra[1]=='='){
                add(letra[0],letra[3]);
            }
        }
        for(auto letra : equations){
            if(letra[1]=='!'){
                if(find(letra[0])==find(letra[3]))return false;
            }
        }
        return true;
        
    }
};