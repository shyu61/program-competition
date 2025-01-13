#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, D; cin >> N >> D;
    int total = 0;
    for (int i = 0; i < N; i++) {
        char c; cin >> c;
        if (c == '@') total++;
    }
    cout << N - (total - D) << endl;
}
