// 区間の問題: p43
#include <bits/stdc++.h>
using namespace std;

// 現在時刻から見て常に終了時刻が早いタスクを選び続けることで解ける
// いかなるタスクを選んでも経過時間は単調であるし有名問題として押さえておくべきパターンでもある

// 貪欲法の注意点はエッジケースの見落としにより、実は局所最適性が成立しなかった場合
// これを防ぐために、証明を頭の中で組み立てると良い。帰納法や背理法を使うケースが多い
// 帰納法を使う場合でも内部で背理法的に証明するケースが多い

int main() {
    int n; cin >> n;
    vector<pair<int, int>> t(n);  // (終了時刻, 開始時刻)
    for (int i = 0; i < n; i++) cin >> t[i].second >> t[i].first;

    sort(t.begin(), t.end());

    int now = 0, ans = 0;
    for (int i = 0; i < n; i++) {
        if (t[i].second <= now) continue;
        now = t[i].first;
        ans++;
    }

    cout << ans << endl;
}
