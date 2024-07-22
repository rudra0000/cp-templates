int n,l,q;
vector<int> adj[200001];
int tin[200001];
int tout[200001];
int timer;
vector<int> up[200001];
void preprocess_dfs(int root) {
    stack<pair<int, int>> st;
    st.push({root, -1});
    vector<int> visited(n + 1, 0);
    while (!st.empty()) {
        int v = st.top().first;
        int par = st.top().second;
        if (!visited[v]) {
            visited[v] = 1;
            tin[v] = ++timer;
            up[v][0] = par;
            for (int i = 1; i <= l; i++) {
                if (up[v][i - 1] != -1) {
                    up[v][i] = up[up[v][i - 1]][i - 1];
                } else {
                    up[v][i] = -1;
                }
            }
            for (auto neigh : adj[v]) {
                if (neigh != par) {
                    st.push({neigh, v});
                }
            }
        } else {
            tout[v] = ++timer;
            st.pop();
        }
    }
}
//checks if u is the ancestor of v
bool is_ancestor(int u,int v){
    return tin[u]<=tin[v] && tout[u]>=tout[v];
}
int lca(int u, int v)
{
    if (is_ancestor(u, v))
        return u;
    if (is_ancestor(v, u))
        return v;
    for (int i = l; i >= 0; --i) {
        if ( up[u][i]!=-1 && !is_ancestor(up[u][i], v))
            u = up[u][i];

    }
    return up[u][0];
}
//works in logn 
int dist(int u,int v){
    int dist_u=0,dist_v=0;
    int org_u=u;
    bool flag1=is_ancestor(u,v),flag2=is_ancestor(v,u);
    if(flag1){
        for(int i=l;i>=0;--i){
            if ( up[v][i]!=-1 && is_ancestor(org_u, up[v][i])){
                v = up[v][i]; 
                dist_v+=pow(2,i);
            }
        }
        return dist_v;
    }else if(flag2){
        for(int i=l;i>=0;--i){
            if ( up[u][i]!=-1 && is_ancestor(v, up[u][i])){
                u = up[u][i]; 
                dist_u+=pow(2,i);
            }
        }
        return dist_u;
    }
    for(int i=l;i>=0;--i){
        if ( up[u][i]!=-1 && !is_ancestor(up[u][i], v)){
            u = up[u][i]; 
            dist_u+=pow(2,i);
        }
    }
    for(int i=l;i>=0;--i){
        if ( up[v][i]!=-1 && !is_ancestor(up[v][i], org_u)){
            v = up[v][i]; 
            dist_v+=pow(2,i);
        }
    }
    return 2+dist_u+dist_v;
}
int get_kth_ancestor(int v,int k){
    for(int bit=0;bit<=l;bit++){
        if((k&(1ll<<bit))>0){
            v=up[v][bit];
            if(v==-1) break;
        }
    }
    return v;
}

void binary_uplifting(int root){
    timer=0;
    l=ceil(log2(n));
    for(int i=0;i<=n;i++){
        up[i].resize(l+1,-1);
    }
    preprocess_dfs(root);
}   