template<class T>
struct FenwickTree {
    vector<T> bit;  // binary indexed tree
    T n;

    FenwickTree(T n) {
        this->n = n;
        bit.assign(n, 0);
    }

    FenwickTree(vector<T> a) : FenwickTree(a.size()) {
        for (size_t i = 0; i < a.size(); i++)
            add(i, a[i]);
    }

    T sum(T r) {
        T ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }

    T sum(T l, T r) {
        return sum(r) - sum(l - 1);
    }

    void add(T idx, T delta) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }
};