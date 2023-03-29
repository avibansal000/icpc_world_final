struct pt {
    ll x, y;
};

int orientation(pt a, pt b, pt c) { // cross of (b-a)X(c-a)
    ll v = a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y);
    if (v < 0) return -1; // clockwise
    if (v > 0) return +1; // counter-clockwise
    return 0;
}
vector<pt> convex_hull(vector<pt> a, bool include_collinear = true) {
    if (a.size() == 1)
        return a;
    sort(a.begin(), a.end(), [](pt a, pt b) {
        return make_pair(a.x, a.y) < make_pair(b.x, b.y);
    });
    pt p1 = a[0], p2 = a.back();
    vector<pt> up, down;
    up.push_back(p1);
    down.push_back(p1);
    // all <= and >= should be changes to < and > in case of collinear not counting 
    for (int i = 1; i < (int)a.size(); i++) {
        if (i == a.size() - 1 || orientation(p1, a[i], p2)<=0) {
            while (up.size() >= 2 && !(orientation(up[up.size()-2], up[up.size()-1], a[i])<=0)) // 
                up.pop_back();
            up.push_back(a[i]);
        }
        if (i == a.size() - 1 || orientation(p1, a[i], p2)>=0) {
            while (down.size() >= 2 && !(orientation(down[down.size()-2], down[down.size()-1], a[i])>=0))
                down.pop_back();
            down.push_back(a[i]);
        }
    }
    if (include_collinear && up.size() == a.size()) {
        reverse(a.begin(), a.end());
        return a;
    }
    a.clear();
    for (int i = 0; i < (int)up.size(); i++)
        a.push_back(up[i]);
    for (int i = down.size() - 2; i > 0; i--)
        a.push_back(down[i]);
    return a;
}