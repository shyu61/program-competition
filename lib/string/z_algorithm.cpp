#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

// sとs[i:|s|-1]の最長共通接頭辞の長さ: O(|s|)
vector<int> z_algorithm(const string &s) {
    vector<int> a(s.size());
    a[0] = s.size();
    int i = 1, j = 0;
    while (i < s.size()) {
        while (i + j < s.size() && s[j] == s[i + j]) j++;
        a[i] = j;
        if (j == 0) {
            i++;
            continue;
        }
        int k = 1;
        while (i + k < s.size() && k + a[k] < j) {
            a[i + k] = a[k];
            k++;
        }
        i += k; j -= k;
    }
    return a;
}
