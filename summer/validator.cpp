#include "testlib.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <ctime>
#include <climits>
#include <cassert>
#include <vector>
#include <queue>
#include <stack>
#include <deque>
#include <set>
#include <map>
#include <bitset>
#include <utility>
#include <algorithm>

using namespace std;

int min_n = 1, min_m = 2;
int max_n = 100000, max_m = 100000;
int max_sum = 1000000;

int leader(vector<int> & dsu, int idx) {
    return dsu[idx] == idx ? dsu[idx] : (dsu[idx] = leader(dsu, dsu[idx]));
}

bool merge(vector<int>& dsu, int a, int b) {
    a = leader(dsu, a);
    b = leader(dsu, b);
    if (a == b) {
        return false;
    } else {
        if (rnd.next(2) == 0) {
            dsu[a] = b;
        } else {
            dsu[b] = a;
        }
        return true;
    }
}

bool tree_validator(int n) {
    vector<int> dsu(n);
    for (int i = 0; i < n; i++) {
        dsu[i] = i;
    }

    set<pair<int,int> > edges;

    for (int i = 0; i < n - 1; i++) {
        int x = inf.readInt(1, n, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, n, "y_i");
        inf.readEoln();

        ensuref(x != y, "Tree can't contain loops");
        ensuref(edges.count(make_pair(x, y)) == 0, "Tree can't contain multiple edges between a pair of vertices");

        edges.insert(make_pair(x, y));
        edges.insert(make_pair(y, x));

        ensuref(merge(dsu, x - 1, y - 1), "Tree can't contain cycles");
    }
    return true;
}

int main(int argc, char** argv) {
	registerValidation(argc, argv);
	
	int n = inf.readInt(min_n, max_n, "n");
	inf.readEoln();
	int vertex_sum = 0;

	for (int i = 0; i < n; i++) {
		int m = inf.readInt(min_m, max_m, "m");
		vertex_sum += m;
		ensuref(vertex_sum <= max_sum, "Sum of graphs' vertexes exceeds the limit");
		inf.readEoln();
		ensuref(tree_validator(m), "At least one of the graphs is not a tree");
	}

	inf.readEof();
	return 0;
}
