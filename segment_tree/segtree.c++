struct LazySeg {
    struct F { // Lazy update: supports both set and add
        bool has_set = false;
        int set_val = 0;
        int inc = 0;

        F() {}
        F(int add) { inc = add; }
        static F set_op(int val) {
            F f;
            f.has_set = true;
            f.set_val = val;
            return f;
        }

        F& operator*=(const F& a) {
            if (a.has_set) {
                has_set = true;
                set_val = a.set_val;
                inc = a.inc; // add after set
            } else {
                inc += a.inc;
            }
            return *this;
        }
    };

    struct T {
        int sz = 1, mn = INT_MAX, mx = INT_MIN, sum = 0;
        int ind = -1;

        T() {}
        T(int x) {
            mn = mx = sum = x;
        }

        friend T operator+(const T& a, const T& b) {
            T res;
            res.sz = a.sz + b.sz;
            res.mn = min(a.mn, b.mn);
            res.mx = max(a.mx, b.mx);
            res.ind = (a.mx > b.mx ? a.ind : b.ind);
            res.sum = a.sum + b.sum;
            return res;
        }

        T& operator*=(const F& a) {
            if (a.has_set) {
                mn = mx = a.set_val + a.inc;
                sum = (long long)sz * (a.set_val + a.inc);
            } else if (a.inc) {
                mn += a.inc;
                mx += a.inc;
                sum += (long long)sz * a.inc;
            }
            return *this;
        }
    };

    vector<T> seg;
    vector<F> lazy;
    int SZ = 1;

    void init(int n) {
        while (SZ < n) SZ *= 2;
        seg.assign(2 * SZ, T());
        lazy.assign(2 * SZ, F());
    }

    void build(const vector<int>& A) {
        int n = A.size();
        init(n);
        for (int i = 0; i < n; ++i) {
            seg[SZ + i] = T(A[i]);
            seg[SZ + i].ind = i;
        }
        for (int i = n; i < SZ; ++i)
            seg[SZ + i] = T();
        for (int i = SZ - 1; i >= 1; --i)
            seg[i] = seg[2 * i] + seg[2 * i + 1];
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

    void upd(int lo, int hi, const F& val, int ind, int L, int R) {
        push(ind);
        if (hi < L || R < lo) return;
        if (lo <= L && R <= hi) {
            lazy[ind] *= val;
            push(ind);
            return;
        }
        int M = (L + R) / 2;
        upd(lo, hi, val, 2 * ind, L, M);
        upd(lo, hi, val, 2 * ind + 1, M + 1, R);
        pull(ind);
    }

    void range_add(int lo, int hi, int v) { upd(lo, hi, F(v), 1, 0, SZ - 1); }
    void range_set(int lo, int hi, int v) { upd(lo, hi, F::set_op(v), 1, 0, SZ - 1); }

    T query(int lo, int hi, int ind, int L, int R) {
        push(ind);
        if (hi < L || R < lo) return T();
        if (lo <= L && R <= hi) return seg[ind];
        int M = (L + R) / 2;
        return query(lo, hi, 2 * ind, L, M) + query(lo, hi, 2 * ind + 1, M + 1, R);
    }

    T query(int lo, int hi) { return query(lo, hi, 1, 0, SZ - 1); }
};