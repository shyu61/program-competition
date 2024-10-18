// Crazy Rows: p119
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// いわゆる逐次問題。アプローチ方法は、全探索/貪欲法/DP/グラフ/stack,queueなど多岐にわたる
// 全探索は40!になるので間に合わないし、グラフもフィットしなさそう。DPはどの部分をswapするか絞りにくいので考えにくく、構造的にstack,queueは使いにくい。
// なんとなく、違反している行だけを移動させることで最小コストで達成できそう -> 貪欲法でやってみる

// 解法: 違反している位置に持って来れるもののうち、それより右側で最も近いものを持ってくる。この操作を繰り返す

int main() {
    int n; cin >> n;
    vector<int> a(n, -1);
    for (int i = 0; i < n; i++) {
        string x; cin >> x;
        for (int j = 0; j < n; j++) {
            if (x[j] == '1') a[i] = j;
        }
    }

    int ans = 0;
    // 上から順に違反している行を探す
    for (int i = 0; i < n; i++) {
        // 違反
        if (a[i] > i) {
            // iに持って来れるものを探す
            for (int j = i + 1; j < n; j++) {
                // jが持って来れるのでiまで順にswapする
                if (a[j] <= i) {
                    while (j > i) {
                        swap(a[j], a[j - 1]);
                        j--;
                        ans++;
                    }
                    break;
                }
            }
        }
    }
    cout << ans << endl;
}
