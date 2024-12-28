#include <bits/stdc++.h>
using namespace std;
using P = pair<int, string>;

const int N = 5;

int main() {
    vector<int> score(N);
    for (int i = 0; i < N; i++) cin >> score[i];

    string S = "ABCDE";

    vector<P> res;
    for (int i = 1; i <= 1 << N; i++) {
        int sum = 0;
        string s = "";

        for (int j = 0; j < N; j++) {
            if (i >> j & 1) {
                sum += score[j];
                s += S[j];
            }
        }
        res.emplace_back(sum, s);
    }

    sort(res.begin(), res.end(), [](const P& a, const P& b) {
        if (a.first != b.first) return a.first > b.first;
        return a.second < b.second;
    });
    for (auto p : res) {
        cout << p.second << endl;
    }
}
