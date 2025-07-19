#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using P = pair<int, int>;
using TP = tuple<int, int, char>;

// https://atcoder.jp/contests/pakencamp-2018-day2/tasks/pakencamp_2018_day2_d

// 🔷抑えるべき抽象論は？
// 区間更新について
// - セオリーはlazysegだが、圧縮配列を使う方法もある
//   - 1回での更新区間が高々1つである場合に限り使える
//   - O(1)で更新できる
//   - 区間探索は、各区間の先頭位置をもっておけば二分探索できる

int main() {
    int n, m; string s; cin >> n >> s >> m;
    vector<char> d(m), f(m);
    rep(i, m) cin >> d[i] >> f[i];
    int q; cin >> q;
    vector<vector<P>> Q(m);
    rep(i, q) {
        int t, p; cin >> t >> p;
        t--, p--;
        Q[t].emplace_back(p, i);
    }

    s += '#';
    deque<TP> deq;
    int left = 0;
    rep(i, n) {
        if (s[i] != s[i + 1]) {
            deq.emplace_back(left, i - left + 1, s[i]);
            left = i + 1;
        }
    }

    vector<char> ans(q);
    rep(i, m) {
        if (d[i] == 'L') {
            auto& [pos, len, c] = deq[0];
            if (c == f[i]) pos--, len++;
            else {
                if (deq.size() >= 2) {
                    auto& [pos2, len2, c2] = deq[1];
                    pos2 = pos - 1;
                    len2 += len + 1;
                    deq.pop_front();
                } else {
                    deq.emplace_front(pos - 1, 1, f[i]);
                }
            }
        } else {
            auto& [pos, len, c] = deq.back();
            if (c == f[i]) len++;
            else {
                if (deq.size() >= 2) {
                    auto& [pos2, len2, c2] = deq[deq.size() - 2];
                    len2 += len + 1;
                    deq.pop_back();
                } else {
                    deq.emplace_back(pos + len, 1, f[i]);
                }
            }
        }

        for (auto [p, ix] : Q[i]) {
            int offset = get<0>(deq.front());
            auto it = upper_bound(deq.begin(), deq.end(), p + offset, [](int b, const TP& a) {
                if (b == get<0>(a)) return false;
                return b < get<0>(a);
            });
            it--;
            ans[ix] = get<2>(*it);
        }
    }

    rep(i, q) cout << ans[i] << '\n';
}
