// 特殊な状態の列挙: p39
#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> a;
vector<bool> used;

// n!
void perm1(vector<int> cur) {
    if (cur.size() == n) {
        for (int i = 0; i < n; i++) cout << cur[i] << " ";
        cout << endl;
    }
    for (int i = 0; i < n; i++) {
        if (used[i]) continue;
        used[i] = true;
        vector<int> ncur = cur;
        ncur.push_back(a[i]);
        perm1(ncur);
        used[i] = false;
    }
}

void perm2() {
    do {
        for (int i = 0; i < n; i++) cout << a[i] << " ";
        cout << endl;
    } while (next_permutation(a.begin(), a.end()));
}

int main() {
    cin >> n;
    a = vector<int>(n);
    used = vector<bool>(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    perm1(vector<int>());
    cout << "-------" << endl;
    perm2();
}
