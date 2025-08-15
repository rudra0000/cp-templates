struct Trie {
    vector<int> ct;
    vector<array<int, 2>> ch;
    Trie() : ct(1, 0), ch(1, {-1, -1}) {}
    void create() {
        ct.push_back(0);
        ch.push_back({-1, -1});
    }
    void insert(int x) {
        int node = 0;
        for (int bit = 30; bit >= 0; --bit) {
            ++ct[node];
            int b = (x >> bit) & 1;
            if (ch[node][b] == -1) {
                create();
                ch[node][b] = size(ct) - 1;
            }
            node = ch[node][b];
        }
        ++ct[node];
    }
    void erase(int x) { // Assumes x exists
        int node = 0;
        for (int bit = 30; bit >= 0; --bit) {
            --ct[node];
            int b = (x >> bit) & 1;
            node = ch[node][b];
        }
        --ct[node];
    }
    array<int, 2> query_min(int x) {
        int node = 0, res = 0, val = 0;
        for (int bit = 30; bit >= 0; --bit) {
            int b = (x >> bit) & 1;
            if (ch[node][b] == -1 or ct[ch[node][b]] == 0) {
                val += (1^b) << bit;
                res += 1 << bit;
                node = ch[node][1^b];
            }
            else {
                val += b << bit;
                node = ch[node][b];
            }
        }
        return {res, val}; // res-> the minimum XOR value found with x
        // val-> the actual number from the trie that produces this minimum XOR
    }
};
