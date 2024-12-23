#include <bits/stdc++.h>
using namespace std;

int H, W, X, Y, ans = 0;
vector<vector<char>> grid;
vector<vector<bool>> used;
string T;

void update(int nx, int ny, int& x, int& y) {
    if (nx >= 0 && nx < H && ny >= 0 && ny < W && grid[nx][ny] != '#') {
        if (grid[nx][ny] == '@' && !used[nx][ny]) {
            used[nx][ny] = true;
            ans++;
        }
        x = nx; y = ny;
    }
}

int main() {
    cin >> H >> W >> X >> Y;
    grid = vector<vector<char>>(H, vector<char>(W));
    used = vector<vector<bool>>(H, vector<bool>(W));
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) cin >> grid[i][j];
    }
    cin >> T;

    int x = X - 1, y = Y - 1;
    for (char t : T) {
        if (t == 'U') update(x - 1, y, x, y);
        else if (t == 'D') update(x + 1, y, x, y);
        else if (t == 'L') update(x, y - 1, x, y);
        else if (t == 'R') update(x, y + 1, x, y);
    }

    cout << x + 1 << " " << y + 1 << " " << ans << endl;
}
