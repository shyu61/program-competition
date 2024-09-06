#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 10000;
int T[MAX_N];
int Rank[MAX_N];

int getRoot(int x) {
    if (T[x] == x) return x;
    T[x] = getRoot(T[x]);
    return T[x];
}

void unite(int x, int y) {
    int rootx = getRoot(x);
    int rooty = getRoot(y);

    if (Rank[rootx] > Rank[rooty]) {
        T[rooty] = rootx;
    } else if (Rank[rootx] < Rank[rooty]) {
        T[rootx] = rooty;
    } else {
        T[rooty] = rootx;
        Rank[rootx]++;
    }
}

void same(int x, int y) {
    cout << (getRoot(x) == getRoot(y)) << endl;
}

int main() {
    int n, q; cin >> n >> q;
    for (int i = 0; i < n; i++) {
        T[i] = i;
        Rank[i] = 0;
    }
    for (int i = 0; i < q; i++) {
        int com, x, y; cin >> com >> x >> y;
        if (com == 0) unite(x, y);
        else same(x, y);
    }
}