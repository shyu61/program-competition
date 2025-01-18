#include <bits/stdc++.h>
using namespace std;

int main() {
    int N; string S; cin >> N >> S;
    bool ok = true;
    if (N % 2 == 0) ok = false;

    int m = (N + 1) / 2 - 1;
    for (int i = 0; i < N; i++) {
        if (i < m && S[i] != '1') ok = false;
        if (i == m && S[i] != '/') ok = false;
        if (i > m && S[i] != '2') ok = false;
    }

    cout << (ok ? "Yes" : "No") << endl;
}
