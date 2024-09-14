#include <bits/stdc++.h>
using namespace std;

int n, r, cnt = 0;
vector<int> a;

void print(vector<int> vec) {
    cnt++;
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;
}

void npr(vector<int> cur) {
    if (cur.size() == r) {
        print(cur);
        return;
    }

    for (auto v : a) {
        bool seen = false;
        for (auto u : cur) {
            if (v == u) {
                seen = true;
                break;
            }
        }
        if (!seen) {
            cur.push_back(v);
            npr(cur);
            cur.pop_back();
        }
    }
}

void ncr(int start, vector<int> cur) {
    if (cur.size() == r) {
        print(cur);
        return;
    }

    for (int i = start; i < n; i++) {
        cur.push_back(a[i]);
        ncr(i + 1, cur);
        cur.pop_back();
    }
}

int main() {
    cin >> n >> r;
    a = vector<int>(n);
    for (int i = 0; i < n; i++) a[i] = i;

    do {
        print(a);
    } while (next_permutation(a.begin(), a.end()));

    // npr(vector<int>());
    // ncr(0, vector<int>());
    cout << "cnt: " << cnt << endl;
}
