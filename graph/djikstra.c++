vector<int> djikstra(int root,vector<vector<vector<int>>>& graph){
    priority_queue<pair<int,int>> q;
    vector<int> distance(graph.size(),LONG_MAX);
    distance[root]=0;
    q.push(make_pair(0,root));
    while(!q.empty()){
        int dist=-q.top().first;
        int node=q.top().second;
        q.pop();
        if(dist>distance[node]) continue;//this condition optimizes the code
        for(int i=0;i<graph[node].size();i++){
            if(dist+graph[node][i][1]<distance[graph[node][i][0]]){
                distance[graph[node][i][0]]=dist+graph[node][i][1];
                q.push(make_pair(-distance[graph[node][i][0]],graph[node][i][0]));
            }
        }
    }
    
    return distance;
}