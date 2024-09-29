#include <bits/stdc++.h>
using namespace std;

int n, r, cnt;
vector<int> a;

// n!
void f1(vector<int> cur, vector<bool> seen, int d) {
    if (d == n) {
        for (auto v : cur) cout << v << " ";
        cout << endl;
        cnt++;
        return;
    }

    for (int i = 0; i < n; i++) {
        if (seen[i]) continue;
        seen[i] = true;

        // seenのように戻すのが面倒な時は新しい変数を使う
        vector<int> ncur = cur;
        ncur.push_back(a[i]);
        f1(ncur, seen, d + 1);

        seen[i] = false;
    }
}

// nPr
void f2(vector<int> cur, vector<bool> seen, int d) {
    if (d == r) {
        for (auto v : cur) cout << v << " ";
        cout << endl;
        cnt++;
        return;
    }

    for (int i = 0; i < n; i++) {
        if (seen[i]) continue;
        seen[i] = true;

        vector<int> ncur = cur;
        ncur.push_back(a[i]);
        f2(ncur, seen, d + 1);

        seen[i] = false;
    }
}

// nCr
void f3(vector<int> cur, int start, int d) {
    if (d == r) {
        for (auto v : cur) cout << v << " ";
        cout << endl;
        cnt++;
        return;
    }

    // 必ず昇順になるように選べば同じ組み合わせて順番が異なるものを除外できる
    // 樹形図で数える時、自分より小さい値の枝を伸ばした時、必ず自分の兄にその組み合わせが存在することになるので
    // それを除外するために、常に自分より大きい数を選び続ければ良い
    for (int i = start; i < n; i++) {
        vector<int> ncur = cur;
        ncur.push_back(a[i]);
        f3(ncur, i + 1, d + 1);
    }
}

int main() {
    cin >> n >> r;
    a = vector<int>(n);
    for (int i = 0; i < n; i++) a[i] = i;

    cnt = 0;
    cout << "n!" << endl;
    f1(vector<int>(), vector<bool>(n), 0);
    cout << "cnt: " << cnt << endl << endl;

    cnt = 0;
    cout << "nPr" << endl;
    f2(vector<int>(), vector<bool>(n), 0);
    cout << "cnt: " << cnt << endl << endl;

    cnt = 0;
    cout << "nCr" << endl;
    f3(vector<int>(), 0, 0);
    cout << "cnt: " << cnt << endl;
}
