# By Andrey Nedoluzhko

#include <bits/stdc++.h>

using namespace std;

const int MX_SZ = 1e+5 + 42;
const int INF = 1e+9 + 42;

set<pair<long double, int>> tr;
vector<int> g[MX_SZ];
vector<long double> hsh(MX_SZ);
pair<int, int> forb;

void modify_graph(int v, int u, vector<int> &prev) {
    g[v].push_back(u);
    g[u].push_back(v);
    g[prev[u]].push_back(v);
    g[v].push_back(prev[u]);
    forb = {min(u, prev[u]), max(u, prev[u])};
}

int get_furthest(int v, int n, bool get_centre = false) {
    vector<int> dist(n, INF);
    dist[v] = 0;
    queue<pair<int, int>> q;
    q.push({v, 0});
    int mx = 0;
    int v_ret = v;
    vector<int> prev(n, INF);
    prev[v] = v;
    while (!q.empty()) {
        auto x = q.front();
        if (x.second > mx) {
            mx = x.second;
            v_ret = x.first;
        }
        q.pop();
        for (int u : g[x.first]) {
            if (dist[u] > x.second + 1) {
                dist[u] = x.second + 1;
                prev[u] = x.first;
                q.push({u, dist[u]});
            }
        }
    }
    if (get_centre) {
        int to_go = mx / 2;
        while (to_go) {
            v_ret = prev[v_ret];
            --to_go;
        }
        if (mx % 2 == 0) {
            return v_ret;
        } else {
            modify_graph(n + 1, v_ret, prev);
            return n + 1;
        }
    } else {
        return v_ret;
    }
}

void go_hash(int v, int prev) {
    multiset<long double> st;
    for (auto u : g[v]) {
        if (u != prev and
            (min(v, u) != forb.first or max(v, u) != forb.second)) {
            go_hash(u, v);
            st.insert(hsh[u]);
        }
    }
    hsh[v] = 13;
    for (auto x : st) {
        hsh[v] += log(x);
    }
}

void clear_all(int n) {
    for (int i = 0; i < n; ++i) {
        g[i].clear();
    }
    forb = {-1, -1};
}

void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int v, u;
        cin >> v >> u;
        --v, --u;
        g[v].push_back(u);
        g[u].push_back(v);
    }
    int v = get_furthest(1, n);
    int md = get_furthest(v, n, true);
    go_hash(md, md);
    tr.insert({hsh[md], n - (md == n + 1)});
    // cout << hsh[md] << endl;
    clear_all(n + 5);
}

int main() {
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i) {
        solve();
    }
    cout << tr.size() << endl;
}
