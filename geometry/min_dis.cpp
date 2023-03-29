struct min_dis{
    struct pt {
        ll x, y, id;
    };
    vector<pt> a,t;
    ll mindist=9e18;
    pair<ll, ll> best_pair;
    struct cmp_x {
        bool operator()(const pt & a, const pt & b) const {
            return a.x < b.x || (a.x == b.x && a.y < b.y);
        }
    };
    struct cmp_y {
        bool operator()(const pt & a, const pt & b) const {
            return a.y < b.y;
        }
    };
    void upd_ans(const pt & a, const pt & b) {
        ll dist = ((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
        if (dist < mindist) {
            mindist = dist;
            best_pair = {a.id, b.id};
        }
    }
    void rec(int l, int r) {
        if (r - l <= 3) {
            for (int i = l; i < r; ++i) {
                for (int j = i + 1; j < r; ++j) {
                    upd_ans(a[i], a[j]);
                }
            }
            sort(a.begin() + l, a.begin() + r, cmp_y());
            return;
        }

        int m = (l + r) >> 1;
        int midx = a[m].x;
        rec(l, m);
        rec(m, r);

        merge(a.begin() + l, a.begin() + m, a.begin() + m, a.begin() + r, t.begin(), cmp_y());
        copy(t.begin(), t.begin() + r - l, a.begin() + l);

        int tsz = 0;
        for (int i = l; i < r; ++i) {
            if (abs(a[i].x - midx) < mindist) {
                for (int j = tsz - 1; j >= 0 && a[i].y - t[j].y < mindist; --j)
                    upd_ans(a[i], t[j]);
                t[tsz++] = a[i];
            }
        }
    }
    pair<pl,ll> cal_min_dis(vector<pl>& points){
        int n=points.size();
        t.resize(n);
        a.resize(n);
        for(int i=0;i<n;i++){
            a[i]={points[i].first,points[i].second,i};
        }
        sort(a.begin(),a.end(),cmp_x());
        mindist=9e18;
        rec(0,n);
        return {best_pair,mindist};
    }
};