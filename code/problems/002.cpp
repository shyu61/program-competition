// E - Manhattan Multifocal Ellipse
// https://atcoder.jp/contests/abc366/tasks/abc366_e
#include <bits/stdc++.h>
using namespace std;

const int N_MAX = 2e5;
const int D_MAX = 1e6;
const int MAXV = 2e6;
int n, d, x[N_MAX], y[N_MAX];

vector<long long> getMD(int (&xs)[N_MAX]) {
    // とりうる全ての点に対するMDの合計
    vector<long long> md_sum(2 * MAXV + 1, 0);

    // 左端を求める
    for (int i = 0; i < n; i++) {
        md_sum[0] += xs[i] + MAXV;
    }
    // 尺取り法を使って、全ての点についてMDの合計を求める
    int cnt = 0;
    for (int i = -MAXV + 1; i <= MAXV; i++) {
        while (cnt < n && xs[cnt] < i) cnt++;
        md_sum[i + MAXV] = md_sum[i + MAXV - 1] + (cnt - (n - cnt));
    }

    sort(md_sum.begin(), md_sum.end());
    return md_sum;
}

int main() {
    cin >> n >> d;
    for (int i = 0; i < n; i++) cin >> x[i] >> y[i];

    sort(x, x + n);
    sort(y, y + n);

    vector<long long> xsum = getMD(x);
    vector<long long> ysum = getMD(y);

    int j = 0;
    long long ans = 0;
    for (int i = 2 * MAXV; i >= 0; i--) {
        while (j <= 2 * MAXV && xsum[i] + ysum[j] <= d) j++;
        ans += j;
    }
    cout << ans << endl;
}
