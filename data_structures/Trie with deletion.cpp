struct Trie {
    basic_string<int> v;
    basic_string<array<int, 2>> child;
    int id = 0;
    Trie() : v(1, 0), child(1, array{-1, -1}) {}
    void create() {
        v.push_back(0);
        child.push_back({-1, -1});
        ++id;
    }
    void add(int x) {
        int node = 0;
        // cerr << "Inserting " << x<< '\n';
        for (int bit = 30; bit >= 0; --bit) {
            int b = (x >> bit) & 1;
            ++v[node];
            if (child[node][b] == -1) {
                create();
                child[node][b] = id;
            }
            node = child[node][b];
        }
        ++v[node];
    }
    void erase(int x) { // Assumes x exists
        int node = 0;
        // cerr << "Deleting " << x<< '\n';
        for (int bit = 30; bit >= 0; --bit) {
            int b = (x >> bit) & 1;
            --v[node];
            node = child[node][b];
        }
        --v[node];
    }
    int query(int x) { // max a^x for a in the trie
        int ret = 0, node = 0;
        for (int bit = 30; bit >= 0; --bit) {
            int b = (x >> bit) & 1;
            if (child[node][1^b] == -1 or v[child[node][1^b]] == 0) node = child[node][b];
            else {
                ret += 1 << bit;
                node = child[node][1^b];
            }
        }
        return ret;
    }
};
