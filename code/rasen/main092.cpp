// 素数判定: エラトステネスの篩
#include <iostream>
#include <vector>
using namespace std;

vector<int> A;
vector<bool> pn;  // 素数表

void eratos(int a) {
    pn = vector<bool>(a + 1, true);
    pn[0] = pn[1] = false;
    // 合成数pは√p以下の素因子を持つため、
    // i*iより大きい合成数はi*iまでの定数倍で全てチェック済みになる
    for (int i = 2; i * i <= a; i++) {
        if (pn[i]) {
            for (int j = 2; i * j <= a; j++) {
                pn[i * j] = false;
            }
        }
    }
}

int main() {
    int n; cin >> n;
    A = vector<int>(n);
    int maxv = 0;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
        maxv = max(maxv, A[i]);
    }
    // 素数表の作成
    eratos(maxv);

    int total = 0;
    for (int i = 0; i < n; i++) {
        total += pn[A[i]];
    }
    cout << total << endl;
}
