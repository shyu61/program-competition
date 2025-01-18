#include <bits/stdc++.h>
using namespace std;

// ジャンル
// 文字列, 区間クエリ, subsequence問題, 最適化問題

// 方針
// 区間クエリ問題なので、オフライン型かオンライン型のどっちでいくかまず考える
// 区間の伸縮は難しそうなのでオンライン型で考える。区間mergeも難しいので判定問題帰着の二分探索を検討
// 二分探索を使うには、単調性配列の事前計算が必要
// 長さkのsubseqが作れるかは、subarrayのように'/'を中心に見る必要がなく、
// 区間の先頭から順に'1'をk個数,'/'を1個,'2'をk個取れるか判定すれば良いだけで、それぞれ位置配列は単調なので二分探索ができる

// ポイント
// subsequence問題は、位置配列をよく使う。特に単調性を導出したいときに有用

int main() {
    int n, q; string s; cin >> n >> q >> s;
    vector<vector<int>> pos(3);
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') pos[0].push_back(i);
        if (s[i] == '/') pos[1].push_back(i);
        if (s[i] == '2') pos[2].push_back(i);
    }

    const int INF = 1e5 + 10;
    auto get_next = [&](int c, int si, int d) -> int {
        if (d == 0) return si;
        vector<int>& a = pos[c];
        int p = lower_bound(a.begin(), a.end(), si) - a.begin();
        p += d - 1;
        if (p >= a.size()) return INF;
        return a[p] + 1;
    };

    // [l,r)で1,2がm個ずつのsubseqを作れるか判定
    auto check = [&](int m, int l, int r) -> bool {
        int p = get_next(0, l, m);
        p = get_next(1, p, 1);
        p = get_next(2, p, m);
        return p <= r;
    };

    while (q--) {
        int l, r; cin >> l >> r; l--;
        int lb = -1, ub = r - l;
        while (ub - lb > 1) {
            int m = (lb + ub) / 2;
            check(m, l, r) ? lb = m : ub = m;
        }
        cout << (lb == -1 ? 0 : lb * 2 + 1) << '\n';
    }
}

int main() {
    int n, q; string s; cin >> n >> q >> s;
    vector<int> a1, a2, a3;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') a1.push_back(i);
        if (s[i] == '/') a2.push_back(i);
        if (s[i] == '2') a3.push_back(i);
    }

    // [l,r)で長さmのsubseqを作れるか判定
    auto check = [&](int m, int l, int r) -> bool {
        if (m == 0) return true;
        if (m == 1) {
            auto it = lower_bound(a2.begin(), a2.end(), l);
            return it != a2.end() && *it < r;
        }

        int p1 = lower_bound(a1.begin(), a1.end(), l) - a1.begin();
        if (p1 + m / 2 - 1 >= a1.size()) return false;

        int p2 = upper_bound(a2.begin(), a2.end(), a1[p1 + m / 2 - 1]) - a2.begin();
        if (p2 >= a2.size()) return false;

        int p3 = upper_bound(a3.begin(), a3.end(), a2[p2]) - a3.begin();
        if (p3 + m / 2 - 1 >= a3.size()) return false;

        return a3[p3 + m / 2 - 1] < r;
    };

    while (q--) {
        int l, r; cin >> l >> r; l--;
        int lb = 0, ub = r - l + 1;
        while (ub - lb > 1) {
            int m = (lb + ub) / 2;
            check(m, l, r) ? lb = m : ub = m;
        }
        if (lb > 0 && lb % 2 == 0) lb++;
        cout << lb << '\n';
    }
}
