// べき乗
#include <cmath>
#include <iostream>
using namespace std;

using ullong = unsigned long long;

const ullong M = 1000000007;

ullong power(ullong m, ullong n) {
    // 繰り返し自乗法
    if (n == 0) return 1;
    if (n % 2 == 0) {
        return power(m * m % M, n / 2) % M;
    } else {
        return m * power(m * m % M, n / 2) % M;
    }
}

int main() {
    ullong m, n;
    cin >> m >> n;
    cout << power(m, n) << endl;
}
