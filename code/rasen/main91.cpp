// 素数判定
#include <iostream>
#include <vector>
using namespace std;

vector<bool> pn;

int solve(int a) {
    // 素数pは、pの平方根以下の数を素因子にもつ
    for (int i = 2; i * i <= a; i++) {
        if (a % i == 0) return 0;
    }
    return 1;
}

int main() {
    int n; cin >> n;
    int total = 0;
    for (int i = 0; i < n; i++) {
        int a; cin >> a;
        total += solve(a);
    }
    cout << total << endl;
}
