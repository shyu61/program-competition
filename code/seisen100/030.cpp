#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
using P = pair<int, int>;

const vector<int> dx = {0,1,0,-1}, dy = {1,0,-1,0};

int main() {
    int h, w, n; cin >> h >> w >> n;
    vector<string> mas(h);
    rep(i, h) cin >> mas[i];

    vector<P> c(n + 1);
    rep(i, h) rep(j, w) {
        if (mas[i][j] == 'S') c[0] = {i, j};
        else if ('1' <= mas[i][j] && mas[i][j] <= '9') {
            c[mas[i][j] - '0'] = {i, j};
        }
    }

    auto bfs = [&](int si, int sj, int ti, int tj) -> int {
        queue<P> que;
        que.emplace(si, sj);
        vector<vector<int>> dist(h, vector<int>(w, -1));
        dist[si][sj] = 0;
        while (!que.empty()) {
            auto [ni, nj] = que.front(); que.pop();
            if (ni == ti && nj == tj) return dist[ni][nj];
            rep(r, 4) {
                int n2i = ni + dx[r], n2j = nj + dy[r];
                if (n2i < 0 || n2i >= h || n2j < 0 || n2j >= w) continue;
                if (mas[n2i][n2j] == 'X') continue;
                if (dist[n2i][n2j] != -1) continue;
                que.emplace(n2i, n2j);
                dist[n2i][n2j] = dist[ni][nj] + 1;
            }
        }
        return -1;
    };

    int ans = 0;
    rep(i, n) {
        ans += bfs(c[i].first, c[i].second, c[i + 1].first, c[i + 1].second);
    }
    cout << ans << endl;
}
