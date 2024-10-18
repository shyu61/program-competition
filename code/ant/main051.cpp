// プライオリティキューとヒープ(Expedition): p73
#include <bits/stdc++.h>
using namespace std;

// 逐次問題 -> DP,グラフ,全探索,貪欲法,stack
// 1度にできる限り多く給油し、ギリギリまで給油を先延ばしにするのが直感的には良さそうで貪欲法的な考えは筋が良さそう。
// しかし実装は難しい。頭に置きつつ別の方法も考えると、遷移は1次元なのでstackのようにGSを通過する度に順番に保存しておいて燃料が0になったら取り出すという考えが思いつく。
// これは暗に遅延評価をしている。つまり、逐次問題の中でも今回のような資源問題では"遅延評価"(ある資源を獲得した時、それを使うかどうかは後で判断する)を使うことでうまく解けるケースがあると言える

int main() {
    int n, L, P; cin >> n >> L >> P;
    queue<pair<int, int>> que;
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        que.emplace(a, b);
    }

    priority_queue<int> pq;
    int now = 0, fuel = P, ans = 0;
    while (1) {
        now += fuel;
        if (now >= L) break;

        // 通過したGSを追加
        // そのGSで給油するかどうかは遅延評価する
        while (!que.empty()) {
            auto [a, b] = que.front();
            if (a > now) break;
            pq.push(b);
            que.pop();
        }

        // 給油
        if (pq.empty()) {
            cout << -1 << endl;
            return 0;
        }
        fuel = pq.top(); pq.pop();
        ans++;
    }
    cout << ans << endl;
}
