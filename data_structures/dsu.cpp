template<typename A>
class DSU{
public:
    vector<A>parent;
    DSU(A n){
        parent.resize(n);
        for(A i=0;i<n;i++)
            parent[i]=-1;
    }
    A find_set(A x){
        return parent[x]<0?x:parent[x]=find_set(parent[x]);
    } 
    void union_set(A a,A b){
        A pa=find_set(a);
        A pb=find_set(b);
        if(pa==pb)
            return;
        if(parent[pa]>parent[pb])
            swap(pa,pb);
 
        parent[pa]+=parent[pb];
        parent[pb]=pa;
    } 
    bool same_set(A a,A b){
        return find_set(a)==find_set(b);
    }
 
};