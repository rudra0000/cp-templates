struct Trie {
    int id;
    Trie* nxt[26];

    Trie() {
        id = -1;
        memset(nxt, 0, sizeof(nxt));
    }
};

void insert(Trie* root, const string &s, int id) {
    Trie* cur = root;
    for (char c : s) {
        int x = c - 'a';
        if (!cur->nxt[x]) cur->nxt[x] = new Trie();
        cur = cur->nxt[x];
    }
    // cout<<"id "<<id<<" inserted"<<endl;
    cur->id = id;
}
