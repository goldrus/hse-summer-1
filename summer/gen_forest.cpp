#include "testlib.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

using namespace std;

void gen_tree(int n, int t) {
    vector<int> p(n);
    for (int i = 0; i < int(n); i++) {
        if (i > 0) {
            p[i] = rnd.wnext(i, t);
        }
    }
    printf("%d\n", n);
    vector<int> perm(n);
    for (int i = 0; i < int(n); i++) {
        perm[i] = i;
    }
    shuffle(perm.begin() + 1, perm.end());
    vector<pair<int, int>> edges;

    for (int i = 1; i < n; i++) {
        if (rnd.next(2)) {
            edges.push_back(make_pair(perm[i], perm[p[i]]));
        } else {
            edges.push_back(make_pair(perm[p[i]], perm[i]));
        }
    }

    shuffle(edges.begin(), edges.end());

    for (int i = 0; i + 1 < n; i++) {
        printf("%d %d\n", edges[i].first + 1, edges[i].second + 1);
    }
}

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);

    int n = atoi(argv[1]);
    int min_vert = atoi(argv[2]);
    int max_vert = atoi(argv[3]);

    printf("%d\n", n);

    for (int i = 0; i < n; i++) {
        int t = rnd.next(min_vert, max_vert);
        gen_tree(t, 0);
    }

    return 0;
}
