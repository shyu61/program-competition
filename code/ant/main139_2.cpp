// ダブリング: p307
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int N, M; cin >> N >> M;
    vector<int> s(N * 2), t(N * 2);
    for (int i = 0; i < N; i++) cin >> s[i] >> t[i];

    // 複製
    for (int i = 0; i < N; i++) {
        if (t[i] < s[i]) t[i] += M;
        s[N + i] = s[i] + M;
        t[N + i] = t[i] + M;
    }

    // 区間の端点をソート
    vector<pair<int, int>> ps(N * 4);
    for (int i = 0; i < N * 2; i++) {
        ps[i] = make_pair(t[i], i);
        ps[N * 2 + i] = make_pair(s[i], N * 2 + i);
    }
    sort(ps.begin(), ps.end());

    vector<int> next(N * 2);  // next[i] := j, iの次の区間がj
    int last = -1;
    for (int i = N * 4 - 1; i >= 0; i--) {
        int id = ps[i].second;
        if (id < N * 2) {  // idはtである
            next[id] = last;
        } else {  // idはsである
            id -= N * 2;
            if (last < 0 || t[last] > t[id]) last = id;
        }
    }

    int ans = 0;
    for (int i = 0; i < N; i++) {
        int res = 0;
        for (int j = i; t[j] <= s[i] + M; j = next[j]) res++;
        ans = max(ans, res);
    }
    cout << ans << endl;
}
