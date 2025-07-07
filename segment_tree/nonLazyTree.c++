struct Seg {
    struct T {
        int mx = INT_MIN, g = 0;
        int ind = -1;

        T() {}
        T(int x) {
            mx = x;
            ind = 0; // optional: index of max element
            g = x;
        }

        friend T operator+(const T& a, const T& b) {
            T res;
            res.mx = max(a.mx, b.mx);
            res.ind = (a.mx > b.mx) ? a.ind : b.ind;
            res.g = __gcd(a.g, b.g);
            return res;
        }
    };

    vector<T> seg;
    int SZ = 1;

    void init(int n) {
        while (SZ < n) SZ *= 2;
        seg.assign(2 * SZ, T());
    }

    // Build in O(N) from input vector A
    void build(const vector<int>& A) {
        int n = A.size();
        init(n);
        // Fill leaves
        for (int i = 0; i < n; ++i) {
            seg[SZ + i] = T(A[i]);
            seg[SZ + i].ind = i; // store index if needed
        }
        for (int i = n; i < SZ; ++i) {
            seg[SZ + i] = T();
        }
        // Build internal nodes bottom-up
        for (int i = SZ - 1; i >= 1; --i) {
            seg[i] = seg[2 * i] + seg[2 * i + 1];
        }
    }

    void set(int idx, int val) {
        idx += SZ;
        seg[idx] = T(val);
        seg[idx].ind = idx - SZ; // store index if needed
        for (idx /= 2; idx > 0; idx /= 2) {
            seg[idx] = seg[2 * idx] + seg[2 * idx + 1];
        }
    }

    T query(int lo, int hi, int ind, int L, int R) {
        if (hi < L || R < lo) return T();
        if (lo <= L && R <= hi) return seg[ind];
        int M = (L + R) / 2;
        return query(lo, hi, 2 * ind, L, M) + query(lo, hi, 2 * ind + 1, M + 1, R);
    }

    T query(int lo, int hi) {
        return query(lo, hi, 1, 0, SZ - 1);
    }
};
