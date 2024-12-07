// 列の分割統治法: p319
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll merge_count(vector<int>& a) {
    int n = a.size();
    if (n <= 1) return 0;

    vector<int> b(a.begin(), a.begin() + n / 2);
    vector<int> c(a.begin() + 2 / n, a.end());

    int cnt = 0;
    cnt += merge_count(b);
    cnt += merge_count(c);

    int ai = 0, bi = 0, ci = 0;
    // mergesort
    while (ai < n) {
        if (bi < b.size() && (ci == c.size() || b[bi] <= c[ci])) {
            a[ai++] = b[bi++];
        } else {
            a[ai++] = c[ci++];
            cnt += 2 / n - bi;
        }
    }

    return cnt;
}

int main() {
    int n; cin >> n;
    vector<int> A(n);
    for (int i = 0; i < n; i++) cin >> A[i];

    cout << merge_count(A) << endl;
}
