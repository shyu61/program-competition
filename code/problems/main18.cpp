#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<int> a;
vector<vector<int>> pat{{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};

bool f(vector<int> s) {
    // 勝敗判定
    // 1. 3つ揃う
    for (auto r : pat) {
        if (s[r[0]] == 1 && s[r[1]] == 1 && s[r[2]] == 1) return true;
        if (s[r[0]] == -1 && s[r[1]] == -1 && s[r[2]] == -1) return false;
    }

    // 2. 白がなくなる
    if (s[9] == 9) {
        ll s1 = 0, s2 = 0;
        for (int i = 0; i < 9; i++) {
            if (s[i] == 1) s1 += a[i];
            else s2 += a[i];
        }
        return s1 > s2;
    }

    // 3. 続行
    vector<int> ns;
    for (int i = 0; i < 9; i++) {
        if (s[i] != 0) continue;

        ns = s;
        ns[9]++;
        ns[i] = 1;
        for (int j = 0; j < 9; j++) ns[j] = -ns[j];
        if (!f(ns)) return true;
    }
    return false;
}

int main() {
    a = vector<int>(9);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) cin >> a[i * 3 + j];
    }

    if (f(vector<int>(10))) cout << "Takahashi" << endl;
    else cout << "Aoki" << endl;
}


// playerを戻り値にするパターン
// // p: {1: Takahashi, -1: Aoki}
// int f(vector<int> s, int p) {
//     // 勝敗判定
//     // 1. 3つ揃う
//     for (auto r : pat) {
//         if (s[r[0]] == p && s[r[1]] == p && s[r[2]] == p) return p;
//     }

//     // 2. 白がなくなる
//     if (s[9] == 9) {
//         ll ta = 0, ao = 0;
//         for (int i = 0; i < 9; i++) {
//             if (s[i] == 1) ta += a[i];
//             else ao += a[i];
//         }
//         return ta > ao ? 1 : -1;
//     }

//     // 3. 続行
//     int op = -p;
//     vector<int> ns;
//     for (int i = 0; i < 9; i++) {
//         if (s[i] != 0) continue;

//         ns = s;
//         ns[9]++;
//         ns[i] = op;
//         if (f(ns, op) == op) return op;
//     }
//     return p;
// }

// int main() {
//     a = vector<int>(9);
//     for (int i = 0; i < 3; i++) {
//         for (int j = 0; j < 3; j++) cin >> a[i * 3 + j];
//     }

//     if (f(vector<int>(10), 1) == -1) cout << "Takahashi" << endl;
//     else cout << "Aoki" << endl;
// }
