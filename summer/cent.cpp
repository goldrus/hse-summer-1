#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>

using namespace std;

#define ull unsigned long long int

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

 

int main() {

    int n, m;
    cin >> n;
    set<vector<ull>> classes;
    for (int i = 0; i < n; i++) {
        cin >> m;
        vector<vector<int>> graph(m);
        for (int j = 0; j < m - 1; j++) {
            int a, b;
            cin >> a >> b;
            a--;
            b--;
            graph[a].push_back(b);
            graph[b].push_back(a);
        }
        vector<int> centers = find_center(graph);
        for (size_t j = 0; j < centers.size(); j++) {
            cout << centers[i] << ' ';
        }
        cout << endl;
    }
}
