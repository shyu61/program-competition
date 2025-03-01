#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    int n, q; cin >> n >> q;

    vector<int> p(n), box(n), box_num(n);
    rep(i, n) {
        p[i] = i;
        box[i] = i;  // box_to_box-num
        box_num[i] = i;  // box-num_to_box
    }

    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            int a, b; cin >> a >> b, a--, b--;
            p[a] = box_num[b];
        } else if (type == 2) {
            int a, b; cin >> a >> b, a--, b--;
            box[box_num[a]] = b;
            box[box_num[b]] = a;
            swap(box_num[a], box_num[b]);
        } else {
            int a; cin >> a, a--;
            cout << box[p[a]] + 1 << '\n';
        }
    }
}
