// くじびき: p8
#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> a;

bool f(int sum, int d) {
    if (d == 4) return sum == m;

    for (int i = 0; i < n; i++) {
        if (f(sum + a[i], d + 1)) return true;
    }
    return false;
}

int main() {
    cin >> n >> m;
    a = vector<int>(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    if (f(0, 0)) cout << "Yes" << endl;
    else cout << "No" << endl;
}
