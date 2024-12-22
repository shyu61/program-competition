// D - Tiling
// https://atcoder.jp/contests/abc345/tasks/abc345_d
#include <bits/stdc++.h>
using namespace std;

int n, h, w;
vector<int> a, b;
vector<bool> used;

bool dfs(vector<vector<bool>> mas) {
    int eh = -1, ew = -1;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (!mas[i][j]) eh = i, ew = j;
        }
    }
    // 終了判定
    if (eh == -1) return true;

    // 次に進む
    for (int i = 0; i < n; i++) {
        if (used[i]) continue;
        used[i] = true;

        int na = a[i], nb = b[i];
        for (int r = 0; r <= 1; r++) {
            if (r == 1 && na == nb) break;
            swap(na, nb);
            vector<vector<bool>> nmas = mas;
            if (eh + na > h || ew + nb > w) continue;
            // マスをタイルで塗る
            bool ok = true;
            for (int j = 0; j < na; j++) {
                for (int k = 0; k < nb; k++) {
                    if (nmas[eh + j][ew + k]) ok = false;
                    nmas[eh + j][ew + k] = true;
                }
            }
            if (!ok) continue;
            if (dfs(nmas)) return true;
        }

        used[i] = false;
    }
    return false;
}

int main() {
    cin >> n >> h >> w;
    a = b = vector<int>(n);
    for (int i = 0; i < n; i++) cin >> a[i] >> b[i];

    used = vector<bool>(n);
    if (dfs(vector<vector<bool>>(h, vector<bool>(w)))) cout << "Yes" << endl;
    else cout << "No" << endl;
}
