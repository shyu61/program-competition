#include <bits/stdc++.h>
using namespace std;

// ジャンル
// bounding box

// 方針
// bounding boxは四隅を特定すれば良い

int main() {
    int h, w; cin >> h >> w;
    vector<string> s(h);
    for (int i = 0; i < h; i++) cin >> s[i];

    vector<int> a = {h,-1,w,-1};  // 上下左右
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (s[i][j] == '#') {
                a[0] = min(a[0], i);
                a[1] = max(a[1], i);
                a[2] = min(a[2], j);
                a[3] = max(a[3], j);
            }
        }
    }

    for (int i = a[0]; i <= a[1]; i++) {
        for (int j = a[2]; j <= a[3]; j++) {
            if (s[i][j] == '.') {
                cout << "No" << endl;
                return 0;
            }
        }
    }
    cout << "Yes" << endl;
}
