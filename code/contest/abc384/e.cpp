#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;
using ll = long long;

struct Point {
    int x, y;
    ll s;
    Point(int x, int y, ll s) : x(x), y(y), s(s) {};
    bool operator<(const Point &other) const {
        return s > other.s;
    };
};

vector<int> dx = {1,0,-1,0}, dy = {0,1,0,-1};
int H, W, X, P, Q;
vector<vector<ll>> S;

void adj(int x, int y, priority_queue<Point>& pq) {
    for (int r = 0; r < 4; r++) {
        int nx = x + dx[r], ny = y + dy[r];
        if (nx >= 0 && nx < H && ny >= 0 && ny < W && S[nx][ny] != -1) {
            pq.emplace(nx, ny, S[nx][ny]);
        }
    }
}

bool over18(ll a, ll b) {
    return (to_string(a).size() - 1) + (to_string(b).size() - 1) >= 18;
}

int main() {
    cin >> H >> W >> X;
    cin >> P >> Q; P--; Q--;
    S = vector<vector<ll>>(H, vector<ll>(W));
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) cin >> S[i][j];
    }

    priority_queue<Point> pq;
    ll now = S[P][Q];
    S[P][Q] = -1;  // 吸収済み
    adj(P, Q, pq);

    while (!pq.empty()) {
        Point p = pq.top(); pq.pop();
        if (S[p.x][p.y] == -1) continue;
        if (over18(p.s, X)) break;  // 戦闘力のmaxは2.5*1e17
        // over18により19桁以上になることはないが、18桁になることはあるのでlong longだと足りない可能性がある
        if (ull(p.s) * X < now) {
            now += p.s;
            S[p.x][p.y] = -1;
            adj(p.x, p.y, pq);
        } else break;
    }

    cout << now << endl;
}
