// 半分全列挙(巨大ナップサック): p148
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// そもそもDPする理由は全探索ができないから。本問題のようにnが小さいなら全探索を最初に検討するのは基本。
// 全探索は2分割して二分探索することで半分*logの計算量まで抑えられる(特にsumを求めるケースで有効)

// 配列において要素の除外はinplaceで処理できる。末尾のindexを持っておき、その要素を採用するときのみincrementする

// 本問題のコアは以下にして後ろ半分に対して二分探索ができる形に持っていくか
// 何とかしてvで二分探索したい -> 制約はwに対してなのでvで二分探索は無理 -> wとvの順位を一致させておけば良い
// w[i]<w[j]<=>v[i]<v[j]にしておけば良く、これがO(n^2)以内ならできる -> 累積的に処理すればO(n)でできる

const ll INF = 1e15 + 1;

int main() {
    int n; cin >> n;
    vector<int> w(n), v(n);
    for (int i = 0; i < n; i++) cin >> w[i] >> v[i];
    ll W; cin >> W;

    // 前半分
    int n1 = n / 2;
    vector<pair<ll, ll>> na(1 << n1);
    for (int i = 0; i < 1 << n1; i++) {
        ll sw = 0, sv = 0;
        for (int j = 0; j < n1; j++) {
            if (i >> j & 1) {
                sw += w[j];
                sv += v[j];
            }
        }
        na[i] = make_pair(sw, sv);
    }
    // w[i]<w[j] && v[i]>v[j]のものをは除外する
    sort(na.begin(), na.end());
    int num = 1;
    for (int i = 1; i < na.size(); i++) {
        if (na[num - 1].second < na[i].second) {
            na[++num] = na[i];
        }
    }

    // 後ろ半分を列挙しつつ求解
    ll ans = 0;
    for (int i = 0; i < 1 << (n - n1); i++) {
        ll sw = 0, sv = 0;
        for (int j = 0; j < n1; j++) {
            if (i >> j & 1) {
                sw += w[j];
                sv += v[j];
            }
        }
        if (W - sw >= 0) {
            // naを二分探索する
            ll tv = (lower_bound(na.begin(), na.begin() + num, make_pair(W - sw, INF)) - 1)->second;
            ans = max(ans, sv + tv);
        }
    }
    cout << ans << endl;
}
