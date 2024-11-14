// 平面走査: p231
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 平面走査を使った解法
// 平面走査は、領域や図形の位置関係(内包/交差/接する/含まない)を評価したい時に特に有用
// 理由は、平面走査の本質は変数固定であり、x,yの2変数を考えるより片方を固定して1変数で考えた方が楽だから
//   それができる前提として走査線を離散的に動かせる必要がある。多くは対象領域/図形の端点をループすることになる

// 思考フロー
// 円の位置関係を調べる問題 -> 全探索したらO(N^2)になって間に合わん -> 位置関係なので平面走査が使えそう -> 円の左端と右端で判定すれば良さそう
// -> xを固定して走査しているので、各地点ではyについて判定すれば良い -> 最も近い上下だけ調べれば十分 -> O(NlogN)で解けた

vector<double> x, y, r;

bool inside(int i, int j) {
    double dx = x[i] - x[j], dy = y[i] - y[j];
    return dx * dx + dy * dy <= r[j] * r[j];
}

int main() {
    int N; cin >> N;
    x = y = r = vector<double>(N);
    vector<pair<double, int>> events;
    for (int i = 0; i < N; i++) {
        cin >> x[i] >> y[i] >> r[i];
        events.emplace_back(x[i] - r[i], i);  // 左端の点
        events.emplace_back(x[i] + r[i], i + N);  // 右端の点
    }
    sort(events.begin(), events.end());

    // 左から右へ走査する
    set<pair<double, int>> cand;  // 今内側を通過している円の集合
    vector<int> ans;
    for (int i = 0; i < N * 2; i++) {
        int id = events[i].second % N;
        if (events[i].second < N) {  // 左端の場合
            // 現在捜査の内側にある円のうち、現在対象の円のすぐ上下にあるものを調べる
            auto it = cand.lower_bound(make_pair(y[id], id));
            if (it != cand.end() && inside(id, it->second)) continue;
            if (it != cand.begin() && inside(id, (--it)->second)) continue;
            ans.push_back(id);
            cand.insert(make_pair(y[id], id));
        } else {  // 右端の場合
            cand.erase(make_pair(y[id], id));
        }
    }
    sort(ans.begin(), ans.end());

    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] + 1 << (i == (ans.size() - 1) ? "\n" : " ");
    }
}
