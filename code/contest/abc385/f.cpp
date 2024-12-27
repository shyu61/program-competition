#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    int N; cin >> N;
    vector<ll> X(N), H(N);
    for (int i = 0; i < N; i++) cin >> X[i] >> H[i];

    double ans = -1;
    double prv = double(H[0]) / X[0];
    bool all = true;
    for (int i = 1; i < N; i++) {
        double a = double(H[i] - H[i - 1]) / (X[i] - X[i - 1]);
        if (a <= prv) all = false;

        ll top = X[i] * H[i - 1] - X[i - 1] * H[i];
        ll bottom = X[i] - X[i - 1];
        ans = max(ans, double(top) / bottom);
    }

    if (all) cout << -1 << endl;
    else cout << fixed << setprecision(10) << ans << endl;
}
