// 最長増加部分列(LIS): O(nlogn)
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int n;
vector<int> A;

int solve() {
    vector<int> dp;
    dp.push_back(A[0]);
    for (int i = 0; i < n; i++) {
        if (A[i] > *(dp.end() - 1)) {
            dp.push_back(A[i]);
        } else {
            vector<int>::iterator it = lower_bound(dp.begin(), dp.end(), A[i]);
            *it = A[i];
        }
    }
    return dp.size();
}

int main() {
    cin >> n;
    A = vector<int>(n);
    for (int i = 0; i < n; i++) cin >> A[i];
    cout << solve() << endl;
}
