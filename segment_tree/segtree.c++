struct LazySeg {
    struct F { // Lazy update
        int inc = 0;
        F() {}
        F(int x) { inc = x; }
        F& operator*=(const F& a) {
            inc += a.inc;
            return *this;
        }
    };
    vector<F> lazy;

    struct T { // Data stored for each interval
        int sz = 1, mn = INT_MAX, sum = 0, mx = INT_MIN;
        int ind = -1;
        T() {}
        T(int x) {
            sum = x;
            mx = x;
            mn = x;
        }

        friend T operator+(const T& a, const T& b) { // Combine two nodes
            T res;
            res.sz = a.sz + b.sz;
            res.mn = min(a.mn, b.mn);
            res.mx = max(a.mx, b.mx);
            res.ind = (a.mx > b.mx ? a.ind : b.ind);
            res.sum = a.sum + b.sum;
            return res;
        }

        T& operator*=(const F& a) {
            mx += a.inc;
            mn += a.inc;
            sum += (long long)sz * a.inc;
            return *this;
        }
    };
    vector<T> seg;
    int SZ = 1;

    // Initialize internal arrays with appropriate size
    void init(int n) {
        while (SZ < n) SZ *= 2;
        seg.assign(2 * SZ, T());
        lazy.assign(2 * SZ, F());
    }

    // Build from input vector A in O(N)
    void build(const vector<int>& A) {
        int n = A.size();
        init(n); // sets SZ and resizes seg and lazy
        // Set leaves
        for (int i = 0; i < n; ++i) {
            seg[SZ + i] = T(A[i]);
            seg[SZ + i].ind = i; // Keep track of index if needed
        }
        for (int i = n; i < SZ; ++i) {
            seg[SZ + i] = T(); // Fill unused leaves with default T
        }
        // Build parents bottom-up
        for (int i = SZ - 1; i >= 1; --i) {
            seg[i] = seg[2 * i] + seg[2 * i + 1];
        }
    }

    // Direct point set, O(log N)
    void set(int idx, int val) {
        idx += SZ;
        seg[idx] = T(val);
        seg[idx].ind = idx - SZ;
        for (idx /= 2; idx > 0; idx /= 2) {
            seg[idx] = seg[2 * idx] + seg[2 * idx + 1];
        }
    }

    void push(int ind) {
        seg[ind] *= lazy[ind];
        if (ind < SZ) {
            lazy[2 * ind] *= lazy[ind];
            lazy[2 * ind + 1] *= lazy[ind];
        }
        lazy[ind] = F();
    }

    void pull(int ind) {
        seg[ind] = seg[2 * ind] + seg[2 * ind + 1];
    }

    void upd(int lo, int hi, F inc, int ind, int L, int R) {
        push(ind);
        if (hi < L || R < lo) return;
        if (lo <= L && R <= hi) {
            lazy[ind] = inc;
            push(ind);
            return;
        }
        int M = (L + R) / 2;
        upd(lo, hi, inc, 2 * ind, L, M);
        upd(lo, hi, inc, 2 * ind + 1, M + 1, R);
        pull(ind);
    }

    void upd(int lo, int hi, int inc) {
        upd(lo, hi, F(inc), 1, 0, SZ - 1);
    }

    T query(int lo, int hi, int ind, int L, int R) {
        push(ind);
        if (lo > R || L > hi) return T();
        if (lo <= L && R <= hi) return seg[ind];
        int M = (L + R) / 2;
        return query(lo, hi, 2 * ind, L, M) + query(lo, hi, 2 * ind + 1, M + 1, R);
    }

    T query(int lo, int hi) {
        return query(lo, hi, 1, 0, SZ - 1);
    }
};
