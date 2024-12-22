// その他の例題(Fence Repair): p49
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 逐次処理問題かつ、板は短くなり続けるという単調性を持ち、かつ前の操作に非依存的に最適な操作を決定できる -> 貪欲法で解けそう
// 分割を繰り返す問題は、逆の統治も一旦考えた方がいい。この問題は統治の方が圧倒的に考えやすい
// 2分割の繰り返し -> 2分木で考える -> 逆から見る -> 木の深さがその板が切り出される回数に該当する -> 長い板は浅く、短い板は深く
// ハフマン木は、データ圧縮以外にも分割や統治を繰り返しつつ全体コストを最小化する問題に応用できると言える

int main() {
    int n; cin >> n;
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < n; i++) {
        int l; cin >> l;
        pq.push(l);
    }

    ll ans = 0;
    while (pq.size() > 1) {
        // 更新がないならsort,更新があるならpriority_queueを使う
        int min1 = pq.top(); pq.pop();
        int min2 = pq.top(); pq.pop();

        int t = min1 + min2;
        ans += t;
        pq.push(t);
    }
    cout << ans << endl;
}
