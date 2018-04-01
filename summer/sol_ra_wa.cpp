#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>

using namespace std;

#define ull unsigned long long int

int x = 53;

vector<ull> pows;

ull magic_hash(int a, int i) {
    return a * pows[i];
}

vector<int> find_center(const vector<vector<int>>& graph) {
    int last = 0;
    queue<int> q;
    q.push(last);
    vector<bool> used(graph.size(), false);
    used[0] = true;
    while (!q.empty()) {
        last = q.front();
        q.pop();
        for (size_t i = 0; i < graph[last].size(); i++) {
            if (!used[graph[last][i]]) {
                q.push(graph[last][i]);
                used[graph[last][i]] = true;
            }
        }
    }
    q.push(last);
    for (int i = 0; i < used.size(); i++) {
        used[i] = false;
    }
    used[last] = true;
    vector<int> from(graph.size()), d(graph.size(), 0);
    while (!q.empty()) {
        last = q.front();
        q.pop();
        for (size_t i = 0; i < graph[last].size(); i++) {
            if (!used[graph[last][i]]) {
                used[graph[last][i]] = true;
                from[graph[last][i]] = last;
                d[graph[last][i]] = d[last] + 1;
                q.push(graph[last][i]);
            }
        }
    }
    int v = last;
    for (int i = 0; i < d[v] / 2; i++) {
        last = from[last];
    }
    if (d[v] % 2 == 0) {
        return {last};
    } else {
        return {last, from[last]};
    }
}

ull get_tree_hash(const vector<vector<int>>& graph, int v, vector<bool>& used) {
    used[v] = true;

    vector<ull> children;
    for (size_t i = 0; i < graph[v].size(); i++) {
        if (!used[graph[v][i]]) {
            ull hash = get_tree_hash(graph, graph[v][i], used);
            children.push_back(hash);
        }
    }
    sort(children.begin(), children.end());
    ull hash = 0;
    for (size_t i = 0; i < children.size(); i++) {
        hash += magic_hash(children[i], i);
    }
    return hash;
}

int main() {
    pows.resize(200000);
    pows[0] = 1;
    for (size_t i = 1; i < pows.size(); i++) {
        pows[i] = pows[i - 1] * x;
    }

    int n, m;
    scanf("%i", &n);
    set<vector<ull>> classes;
    for (int i = 0; i < n; i++) {
        scanf("%i", &m);
        vector<vector<int>> graph(m);
        for (int j = 0; j < m - 1; j++) {
            int a, b;
            scanf("%i%i", &a, &b);
            a--;
            b--;
            graph[a].push_back(b);
            graph[b].push_back(a);
        }
        vector<int> centers = find_center(graph);
        vector<ull> tree_hash;
        for (size_t j = 0; j < centers.size(); j++) {
            vector<bool> used(m, false);
            tree_hash.push_back(get_tree_hash(graph, centers[j], used));
        }
        sort(tree_hash.begin(), tree_hash.end());

        classes.insert(tree_hash);
    }

    printf("%lu", classes.size());
}
