//disjoint set by size
//1 based indexing
class DisjointSet{
    public:
    vector<int> size;
    vector<int> parent;
    DisjointSet(int n){
        size.resize(n+1,1);
        for(int i=0;i<=n;i++){
            parent.push_back(i);
        }
    }
    int find_ultimate_parent(int n){
        if(n==parent[n]){
            return n;
        }
        parent[n]=find_ultimate_parent(parent[n]);
        return parent[n];
    }
    void union_by_size(int u,int v){
        int v_par,u_par;
        v_par=find_ultimate_parent(v);
        u_par=find_ultimate_parent(u);
        if(v_par==u_par) return;
        if(size[v_par]>size[u_par]){
            parent[u_par]=v_par;
            size[v_par]+=size[u_par];
        }
        else{
            parent[v_par]=u_par;
            size[u_par]+=size[v_par];
        }
    }
    bool sameComponent(int u,int v){
        return find_ultimate_parent(u)==find_ultimate_parent(v);
    }
};

//disjoint set by rank
class DisjointSet{
    public:
    vector<int> rank;
    vector<int> parent;
    DisjointSet(int n){
        rank.resize(n+1,0);//assuming 1 based indexing
        for(int i=0;i<n;i++){
            parent.push_back(i);
        }
    }
    int find_ultimate_parent(int n){
        if(n==parent[n]){
            return n;
        }
        parent[n]=find_ultimate_parent(parent[n]);
        return parent[n];
    }
    void union_by_rank(int u,int v){
        int u_par,v_par;
        u_par=find_ultimate_parent(u);
        v_par=find_ultimate_parent(v);
        if(u_par==v_par) return;
        if(rank[u_par]>rank[v_par]){
            parent[v_par]=u_par;
        }
        else if(rank[v_par]>rank[u_par]){
            parent[u_par]=v_par;
        }
        else{
            rank[v_par]++;
            parent[u_par]=v_par;
        }
    }
    bool sameComponent(int u,int v){
        return find_ultimate_parent(u)==find_ultimate_parent(v);
    }
};
