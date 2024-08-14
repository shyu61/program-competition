// E - Sinking Land
// https://atcoder.jp/contests/abc363/tasks/abc363_e
// ダイクストラ法
#include <bits/stdc++.h>
using namespace std;

struct Node {
    int id, e;
    Node (int id, int e): id(id), e(e) {};
    bool operator>(const Node& a) const { return e > a.e; };
};

const int H_MAX = 1000;
const int W_MAX = 1000;
const int Y_MAX = 1e5;
int h, w, y, e[H_MAX][W_MAX], dist[H_MAX * W_MAX];
priority_queue<Node, vector<Node>, greater<Node>> pq;

int horizon[4] = {1, 0, -1, 0};
int vertical[4] = {0, 1, 0, -1};

void solve() {
    while (!pq.empty()) {
        Node v = pq.top(); pq.pop();
        // 更新前の古いqueueはスキップ
        if (v.e > dist[v.id]) continue;

        int dh = v.id / w;
        int dw = v.id % w;
        for (int r = 0; r < 4; r++) {
            int ah = dh + horizon[r];
            int aw = dw + vertical[r];
            int adj = ah * w + aw;

            if (ah >= 0 && ah < h && aw >= 0 && aw < w) {
                if (dist[adj] > max(dist[v.id], e[ah][aw])) {
                    dist[adj] = max(dist[v.id], e[ah][aw]);
                    pq.push(Node(adj, e[ah][aw]));
                }
            }
        }
    }
}

int main() {
    cin >> h >> w >> y;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cin >> e[i][j];

            if (i == 0 || i == h - 1 || j == 0 || j == w - 1) {
                pq.push(Node(i * w + j, e[i][j]));
                dist[i * w + j] = e[i][j];
            } else {
                dist[i * w + j] = y + 1;
            }
        }
    }

    solve();
    sort(dist, dist + h * w);

    int cnt = h * w;
    for (int i = 1; i <= y; i++) {
        int pos = upper_bound(dist, dist + h * w, i) - dist;
        cout << cnt - pos << endl;
    }
}
