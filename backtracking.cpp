#include <bits/stdc++.h>

using namespace std;
void kahn(queue<int>& s, vector<int>& L, map<int,int>& coord, map<int,char>& pos){
    set <char> valido;
    while(!s.empty()){
        int aux=s.front();
        s.pop();
        if(valido.count(pos[aux])==0){
            L.push_back(aux);
            valido.insert(pos[aux]);
        }
        if(coord.count(aux))
            s.push(coord[aux]);
    }
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    vector<int> L;
    string word;
    int i=1;
    queue<int> s;
    map <int,char> pos;
    map<int,int> coord;
    while(1)
    {
        cin>>word;
        if(word =="#")break;
        s.push(i);
        int t=word.size();
        pos.insert({i,word[0]});
        i+=1;
        for(int j=1;j<t;j++,i++){
            pos.insert({i,word[j]});
            coord.insert({i-1,i});
        }
    }
    kahn(s,L,coord,pos);
    int t=L.size();
    for(int j=0;j<t;j++){
        cout<<pos[L[j]];
    }
    cout<<'\n';

}