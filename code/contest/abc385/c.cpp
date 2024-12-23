#include <bits/stdc++.h>
using namespace std;

// 調和級数の和に気づかないといけない問題
// -> ナイーブに全探索すればいいだけ

// 調和級数の和
// 配列を間隔をk=1,2,...,Nと広げて走査する場合に典型的に現れる

int main() {
    int N; cin >> N;
    vector<int> H(N);
    for (int i = 0; i < N; i++) cin >> H[i];

    int ans = 1, cur, h;
    for (int d = 1; d < N; d++) {
        for (int s = 0; s + d < N; s++) {
            cur = 0; h = H[s];
            for (int i = s; i < N; i += d) {
                if (h == H[i]) cur++;
                else break;
            }
            ans = max(ans, cur);
        }
    }
    cout << ans << endl;
}
