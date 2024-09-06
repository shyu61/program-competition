#include <iostream>
#include <vector>
using namespace std;

int n, q;
vector<int> A;

int check(vector<int> vec, int val) {
    for (int i = 0; i < vec.size(); i++) {
        int new_val = val - vec[i];

        if (new_val == 0) return 1;
        else if (new_val > 0) {
            vector<int> new_vec;
            for (int j = 0; j < vec.size(); j++) {
                if (i != j) new_vec.push_back(vec[j]);
            }
            if (check(new_vec, new_val) == 1) return 1;
        }
    }
    return 0;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        A.push_back(a);
    }
    cin >> q;

    for (int i = 0; i < q; i++) {
        int m;
        cin >> m;
        int ans = check(A, m);
        if (ans == 1) {
            cout << "yes" << endl;
        } else {
            cout << "no" << endl;
        }
    }
}