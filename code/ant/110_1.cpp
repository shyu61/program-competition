// 平面走査: p231
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 普通に全探索する方法: O(N^2)

int main() {
    int N; cin >> N;
    vector<double> x(N), y(N), r(N);
    for (int i = 0; i < N; i++) cin >> x[i] >> y[i] >> r[i];

    for (int i = 0; i < N; i++) {
        bool contained = false;
        for (int j = 0; j < N; j++) {
            if (i == j) continue;
            // 中心間の距離
            double d = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
            if (abs(r[i] - r[j]) > d && r[i] < r[j]) {
                contained = true;
                break;
            }
        }
        if (!contained) cout << i + 1 << endl;
    }
}
