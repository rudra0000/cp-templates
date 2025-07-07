//d[l] is the minimum element at which longest increasing subsequence of length l ends
// the below solution exploits the fact that d will always be sorted moreover each element a[i] will update atmost one value of d
//this gives a complexity of nlogn
int lis(vector<int> const& a) {
    int n = a.size();
    const int INF = 1e9;
    vector<int> d(n+1, INF);
    d[0] = -INF;

    for (int i = 0; i < n; i++) {
        int l = upper_bound(d.begin(), d.end(), a[i]) - d.begin();
        if (d[l-1] < a[i] && a[i] < d[l])
            d[l] = a[i];
    }

    int ans = 0;
    for (int l = 0; l <= n; l++) {
        if (d[l] < INF)
            ans = l;
    }
    return ans;
}

vector<int> lis(vector<int> const& a) {
        int n = a.size();
        const int INF = 1e9;
        vector<int> d(n+1, INF);
        vector<int> lis(n,1);
        d[0] = -INF;

        for (int i = 0; i < n; i++) {
            int l = upper_bound(d.begin(), d.end(), a[i]) - d.begin();
            if (d[l-1] < a[i] && a[i] < d[l]){
                d[l] = a[i];
                lis[i]=max(lis[i],l);
            }else if(d[l-1]==a[i]){
                lis[i]=max(lis[i],l-1);
            }else if(d[l-1]<a[i]){
                lis[i]=max(lis[i],l);
            }
        }
        return lis;
    } 
