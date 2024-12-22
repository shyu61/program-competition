// ダブリング: p307
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 循環は「円」と考える
// - どこから始めるかによって解が変わるのが直感的にわかる
// - 実際に扱う時は2倍に複製すると良い: 本問題のように時刻を扱う場合は特によく使う

int main() {
    int N, M; cin >> N >> M;
    vector<pair<int, int>> ps(N * 2);  // (t,s)
    for (int i = 0; i < N; i++) cin >> ps[i].second >> ps[i].first;

    // 2周分に複製する
    for (int i = 0; i < N; i++) {
        if (ps[i].first < ps[i].second) ps[i].first += M;
        ps[N + i] = make_pair(ps[i].first + M, ps[i].second + M);
    }

    sort(ps.begin(), ps.end());

    // 最初の区間を決める
    int ans = 0;
    for (int i = 0; i < N; i++) {
        int res = 0, now = 0;
        // 貪欲法でtが早いものを選ぶ
        for (int j = i; j < N * 2; j++) {
            // スタート地点から一周したら終了
            if (ps[i].second + M < ps[j].first) break;
            if (ps[j].second >= now) {
                res++;
                now = ps[j].first;
            }
        }
        ans = max(ans, res);
    }
    cout << ans << endl;
}
