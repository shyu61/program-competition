#include <iostream>
using namespace std;

int linearSearch(int t, int S[], int n) {
    S[n] = t;
    int i = 0;
    while (S[i] != t) i++;
    return i != n;
}

int main() {
    int n, q, t;
    int c = 0;
    int S[10000 + 1];

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> S[i];
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> t;
        if (linearSearch(t, S, n)) c++;
    }

    cout << c << endl;

    return 0;
}