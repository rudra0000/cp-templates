//dont forget to initialize visited by -1
bool is_bipartite(int root,vector<vector<int>>& adj,vector<int>& visited,int color){
    visited[root]=color;
    for(auto &neigh:adj[root]){
        if(visited[neigh]==-1){
            if(!is_bipartite(neigh,adj,visited,1-color)){
                return false;
            }
        }else{
            if(visited[neigh]==visited[root]){return false;}
        }
    }
    return true;
}