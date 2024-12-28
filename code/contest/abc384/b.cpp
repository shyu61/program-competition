#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, R; cin >> N >> R;
    for (int i = 0; i < N; i++) {
        int d, a; cin >> d >> a;

        if (d == 1) {
            if (1600 <= R && R <= 2799) R += a;
        } else {
            if (1200 <= R && R <= 2399) R += a;
        }
    }
    cout << R << endl;
}
