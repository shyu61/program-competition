#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using P = pair<int, int>;

int N, M, sx, sy, ans = 0;
vector<P> house;
vector<int> X, Y;
vector<bool> used;

void fx(int x, int& y, int ny) {
    auto lb = lower_bound(house.begin(), house.end(), make_pair(x, y));
    if (lb != house.end()) {
        auto ub = upper_bound(house.begin(), house.end(), make_pair(x, ny));

        for (auto it = lb; it < ub; it++) {
            if (it->first != x) continue;
            int dist = it - house.begin();
            if (!used[dist]) {
                used[dist] = true;
                ans++;
            }
        }
    }
    y = ny;
}

void fy(int& x, int y, int nx) {
    auto lb = lower_bound(house.begin(), house.end(), make_pair(x, y));
    if (lb != house.end()) {
        auto ub = upper_bound(house.begin(), house.end(), make_pair(nx, y), [](P a, P b) {
            return a.second != b.second ? a.second < b.second : a.first < b.first;
        });

        for (auto it = lb; it < ub; it++) {
            if (it->second != y) continue;
            int dist = it - house.begin();
            if (!used[dist]) {
                used[dist] = true;
                ans++;
            }
        }
    }
    x = nx;
}

int main() {
    int x, y; cin >> N >> M >> x >> y; x--; y--;
    house = vector<P>(N);
    for (int i = 0; i < N; i++) {
        cin >> house[i].first >> house[i].second;
        house[i].first--; house[i].second--;
    }
    sort(house.begin(), house.end());

    used = vector<bool>(N);
    for (int i = 0; i < M; i++) {
        char d; int c; cin >> d >> c;

        if (d == 'U') fx(x, y, y + c);
        else if (d == 'D') fx(x, y, y - c);
        else if (d == 'L') fy(x, x - c, y);
        else if (d == 'R') fy(x, x + c, y);
    }

    cout << x + 1 << " " << y + 1 << " " << ans << endl;
}
