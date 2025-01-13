#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, D;
    string S; cin >> N >> D >> S;
    for (int i = N - 1; i >= 0; i--) {
        if (S[i] == '@') {
            S[i] = '.';
            D--;
        }
        if (D == 0) break;
    }
    cout << S << endl;
}
