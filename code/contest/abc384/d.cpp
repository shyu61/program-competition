#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ll N, S; cin >> N >> S;
    vector<ll> A(N);
    for (int i = 0; i < N; i++) cin >> A[i];

    ll sum = 0;
    for (int i = 0; i < N; i++) sum += A[i];
    if (S > sum) S %= sum;

    // 尺取り法
    sum = 0;
    int right = 0;
    for (int left = 0; left < N * 2; left++) {
        while (sum < S && right < N * 2) {
            sum += A[right % N];
            right++;
        }

        if (sum == S) {
            cout << "Yes" << endl;
            return 0;
        }

        if (sum > S) {
            sum -= A[left % N];
        } else break;
    }
    cout << "No" << endl;
}
