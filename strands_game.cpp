#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
#include<unordered_map>
#include<set>
#include<unordered_set>
#include<queue>
#include<stack>
#include<math.h>
#include<string>
using namespace std;


int rows[] = {1,-1,0, 0, 1,1,-1,-1};
int cols[] = {0, 0,1,-1, 1,-1,1,-1};
bool isValid(int i ,int j , int n , int m){
    return i>=0 and j>=0 and i<n and j<m;
}


void recursion(vector<string>grid, string&word, int i , int j, int k, vector<pair<int,int>>path, vector<vector<int>>&visited, vector<vector<pair<int,int>>>&ans){
    if(k == word.length()){
        // for(auto i: path){
        //     cout<<i.first<<" "<<i.second<<endl;
        // }
        ans.emplace_back(move(path));
        return ;
    }
    visited[i][j] = 1;
    for(int idx =0; idx<8; idx++){
        int new_i = i + rows[idx];
        int new_j = j + cols[idx];
        if(isValid(new_i, new_j, grid.size(), grid[0].size()) and grid[new_i][new_j] == word[k] and !visited[new_i][new_j]){
            path.push_back({new_i, new_j});
            recursion(grid, word, new_i, new_j, k+1, path, visited, ans);
            path.pop_back();
        }
    }
}


void solve(){
    int m = 6,n = 8;
    string word;
    cin >> word;

    vector<string>grid(n);
    for(int i=0; i<n; i++){
        cin >> grid[i];
    }
    vector<vector<pair<int,int>>>ans;

    vector<vector<int>>visited(n, vector<int>(m, 0));
    vector<pair<int,int>>path;
    for(int i =0; i<n; i++){
        for(int j =0; j<m; j++){
            if(grid[i][j] == word[0]){
                visited[i][j] = 1;
                path.push_back({i,j});
                // cout<<i<<" "<<j<<endl;
                recursion(grid, word, i, j, 1, path, visited, ans);
                visited[i][j] = 0;
                path.pop_back();
            }
        }
    }
    for(auto i : ans){
        for(auto j : i){
            cout<<j.first<<" "<<j.second<<endl;
        }
        // cout<<endl<<endl<<endl;
    }
    // recursion(grid, word, 0, 0, 0, path, visited);
    // cout<<ans.size()<<endl;

}

int main(){
    int t;
    cin >> t;
    // int x= 1;
    // cout<<(&x);
    while(t--){
        solve();
    }
    return 0;
}