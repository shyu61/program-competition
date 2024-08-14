#include <iostream>
using namespace std;

int n, q, m, A[20];

int solve(int i, int m) {
    if (m == 0) return 1;
    else if (m < 0) return 0;
    if (i >= n) return 0;
    return solve(i + 1, m - A[i]) || solve(i + 1, m);
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    cin >> q;

    for (int i = 0; i < q; i++) {
        cin >> m;
        int j = 0;
        if (solve(j, m)) cout << "yes" << endl;
        else cout << "no" << endl;
    }
}