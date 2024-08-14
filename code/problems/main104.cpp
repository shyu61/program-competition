// E - Sinking Land
// https://atcoder.jp/contests/abc363/tasks/abc363_e
// 逐次シミュレーションを丁寧に実装した場合
#include <bits/stdc++.h>
using namespace std;

const int H_MAX = 1000;
const int W_MAX = 1000;
const int Y_MAX = 1e5;
int h, w, y, e[H_MAX][W_MAX], cnt;
bool seen[H_MAX * W_MAX];
queue<int> que[Y_MAX + 1];

int horizon[4] = {1, 0, -1, 0};
int vertical[4] = {0, 1, 0, -1};

void solve(int year) {
    while (!que[year].empty()) {
        int sec = que[year].front(); que[year].pop();
        seen[sec] = true;
        cnt--;

        int dh = sec / w;
        int dw = sec % w;

        // secの四方を調べる
        for (int r = 0; r < 4; r++) {
            int adjh = dh + horizon[r];
            int adjw = dw + vertical[r];
            int adj = adjh * w + adjw;
            if (adjh >= 0 && adjh < h && adjw >= 0 && adjw < w && !seen[adj]) {
                que[max(e[adjh][adjw], year)].push(adj);
                seen[adj] = true;
            }
        }
    }

    cout << cnt << endl;
}

int main() {
    cin >> h >> w >> y;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cin >> e[i][j];

            if (i == 0 || i == h - 1 || j == 0 || j == w - 1) {
                que[e[i][j]].push(i * w + j);
                seen[i * w + j] = true;
            }
        }
    }

    cnt = h * w;
    for (int year = 1; year <= y; year++) {
        solve(year);
    }
}