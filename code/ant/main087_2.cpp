// バケット法と平方分割: p168
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 領域木による解法
// セグ木などの木構造のノードに1次元配列を持たせることで2次元をカバーできる
// さらにノードに木を入れ子で持つことで3次元以上を扱うこともできる

int n, sz = 1;
vector<int> A;
vector<vector<int>> dat;

void init(int id, int l, int r) {
    if (r - l == 1) {
        dat[id].push_back(A[l]);
    } else {
        int chl = id * 2 + 1, chr = id * 2 + 2;
        init(chl, l, (l + r) / 2);
        init(chr, (l + r) / 2, r);

        dat[id].resize(r - l);
        merge(dat[chl].begin(), dat[chl].end(), dat[chr].begin(), dat[chr].end(), dat[id].begin());
    }
}

int query(int x, int a, int b, int id, int l, int r) {
    if (b <= l || r <= a) return 0;
    if (a <= l && r <= b) {
        return upper_bound(dat[id].begin(), dat[id].end(), x) - dat[id].begin();
    } else {
        int vl = query(x, a, b, id * 2 + 1, l, (l + r) / 2);
        int vr = query(x, a, b, id * 2 + 2, (l + r) / 2, r);
        return vl + vr;
    }
}

int main() {
    int m; cin >> n >> m;
    A = vector<int>(n);
    for (int i = 0; i < n; i++) cin >> A[i];

    // セグ木の初期化
    while (sz < n) sz *= 2;
    dat = vector<vector<int>>((1<<18)-1);
    init(0, 0, n);

    vector<int> nums = A;
    sort(nums.begin(), nums.end());

    while (m--) {
        int l, r, k; cin >> l >> r >> k; l--;

        // 二分探索を考える時は、lbは常に条件を満たさない、ubは常に条件を満たすようにとる
        int lb = -1, ub = n - 1;
        while (ub - lb > 1) {
            int md = (lb + ub) / 2;
            int x = nums[md];

            int cnt = query(x, l, r, 0, 0, n);

            // is_ok(m)ならub=m
            if (cnt >= k) ub = md;
            else lb = md;
        }

        cout << nums[ub] << endl;
    }
}
