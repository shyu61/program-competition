// 線分交差問題
#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// 想定解
// 平面走査

// 罠
// 同じ走査線に要素が複数ある場合の処理する順は要注意

// ポイント
// 平面走査は一方の軸についてsortし順に見ることで固定する。
// もう一方は二分探索などで処理することでO(NlogN)で実行する

struct Point {
    int x, y;
    Point() {}
    Point(int x, int y) : x(x), y(y) {}
};

int main() {
    int n; cin >> n;
    vector<pair<Point, Point>> seg(n);
    rep(i, n) {
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);
        seg[i] = {Point(x1, y1), Point(x2, y2)};
    }

    // type: 1=bottom, 2=other, 3=top
    vector<tuple<int, int, int>> events;
    rep(i, n) {
        if (seg[i].first.x == seg[i].second.x) {
            events.emplace_back(seg[i].first.y, 1, i);
            events.emplace_back(seg[i].second.y, 3, i);
        } else {
            events.emplace_back(seg[i].first.y, 2, i);
        }
    }
    sort(events.begin(), events.end());

    int ans = 0;
    set<int> st;
    for (auto [ny, type, id] : events) {
        if (type == 1) st.insert(seg[id].first.x);
        if (type == 3) st.erase(seg[id].second.x);
        if (type == 2) {
            ans += distance(
                st.lower_bound(seg[id].first.x),
                st.upper_bound(seg[id].second.x)
            );
        }
    }
    cout << ans << endl;
}
