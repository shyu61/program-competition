#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, D; cin >> N >> D;
    vector<int> T(N), L(N);
    for (int i = 0; i < N; i++) cin >> T[i] >> L[i];

    for (int k = 1; k <= D; k++) {
        int maxv = 0;
        for (int i = 0; i < N; i++) {
            maxv = max(maxv, T[i] * (L[i] + k));
        }
        cout << maxv << endl;
    }
}
