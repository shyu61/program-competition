#include <iostream>
using namespace std;

const int MAX_WEIGHT = 10000;
const int MAX_LUGGAGE_SIZE = 100000;

int n, k;
int W[MAX_LUGGAGE_SIZE];

int canLoad(long long p) {
    int i = 0;
    for (int j = 0; j < k; j++) {
        long long sum = 0;
        while (i < n) {
            if (sum + W[i] > p) break;
            sum += W[i];
            i++;
        }
    }
    return i == n;
}

int solve() {
    int left = 1;
    int right = MAX_LUGGAGE_SIZE * MAX_WEIGHT + 1;
    while (left < right) {
        int mid = (left + right) / 2;
        if (canLoad(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}


int main() {
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> W[i];
    }
    int ans = solve();
    cout << ans << endl;
}