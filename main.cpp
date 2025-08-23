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
#include <utility>
#include"ui.h"
using namespace std;



int rows[] = {1,-1,0, 0, 1,1,-1,-1};
int cols[] = {0, 0,1,-1, 1,-1,1,-1};
bool isValid(int i ,int j , int n , int m){
    return i>=0 and j>=0 and i<n and j<m;
}


void find_word(vector<string>grid, string&word, int i , int j, int k, vector<pair<int,int>>path, vector<vector<int>>&visited, vector<pair<int,int>>&ans){
    if(k == word.length()){
        ans = (std::move(path));
        return ;
    }
    visited[i][j] = 1;
    for(int idx =0; idx<8; idx++){
        int new_i = i + rows[idx];
        int new_j = j + cols[idx];
        if(isValid(new_i, new_j, grid.size(), grid[0].size()) and grid[new_i][new_j] == word[k] and !visited[new_i][new_j]){
            path.push_back({new_i, new_j});
            find_word(grid, word, new_i, new_j, k+1, path, visited, ans);
            path.pop_back();
        }
    }
    visited[i][j] =0;
}


vector<pair<int,int>>strands_game(const vector<string>&grid,  string &word){
    int m = 6,n = 8 ; // n rows and m cols this is static
    
    vector<pair<int,int>>ans;

    vector<pair<int,int>>path;
    vector<vector<int>>visited(n, vector<int>(m, 0)); // declared the visited matrix
    for(int i =0; i<n; i++){
        for(int j =0; j<m; j++){
            if(grid[i][j] == word[0]){
                visited[i][j] = 1;
                path.push_back({i,j});
                find_word(grid, word, i, j, 1, path, visited, ans);
                visited[i][j] = 0;
                path.pop_back();
            }
        }
    }
    // find_word(grid, word, 0, 0, 0, path, visited);
    // cout<<ans.size()<<endl;
    return ans;

}
vector<string> get_grid(){
    int m = 6,n = 8 ; // n rows and m cols this is static
    
    printf("Enter the grid of size (%d,%d) \n", n, m);;
    vector<string>grid(n);
    for(int i=0; i<n; i++){
        cin >> grid[i];
    }
    return grid;    
}


int main(){
    const vector<string>grid = get_grid();
    show_grid(grid);
    while (true){
        printf("Enter the word you want to find \n");
        string word;
        cin >> word;
        vector<pair<int,int>>path = strands_game(grid, word);  
        highlight_path(grid, path);
    }
    return 0;
}