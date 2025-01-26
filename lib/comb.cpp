#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // nCk
    vector<vector<int>> out;
    auto comb = [&](auto comb, int k, vector<int>& cur, int s) -> void {
        if (cur.size() == k) {
            out.push_back(cur);
            return;
        }
        for (int i = s; i <= n; i++) {
            cur.push_back(a[i]);
            comb(comb, k, cur, i + 1);
            cur.pop_back();
        }
    };

    // nPk
    vector<vector<int>> out2;
    auto perm = [&](int k, vector<int>& cur, int s) -> void {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                out2.emplace_back(a[i], a[j]);
            }
        }
    };

    // bell
    vector<vector<vector<int>>> out3;
    auto bell = [&](auto bell, int cur, vector<vector<int>>& pt) -> void {
        if (cur == n) {
            out3.push_back(pt);
            return;
        }

        for (int i = 0; i < pt.size(); i++) {
            pt[i].push_back(a[cur]);
            bell(bell, cur + 1, pt);
            pt[i].pop_back();
        }

        pt.push_back(vector<int>{a[cur]});
        bell(bell, cur + 1, pt);
        pt.pop_back();
    };
}
