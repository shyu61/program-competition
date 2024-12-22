#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>
#include <unordered_map>
using namespace std;
const int MAXV = 100 * 2000 + 1;

vector<vector<int> > A;


int solve(vector<int> vec) {
    if (vec.size() == 1) return 0;

    int minv = MAXV;
    for (int i = 0; i < vec.size(); i++) {
        vector<int> new_vec = vec;
        vector<int>::iterator right_it = new_vec.begin() + i;
        int removed = *right_it;
        new_vec.erase(right_it);

        int cost = solve(new_vec);

        int min_w = MAXV;
        for (int j = 0; j < new_vec.size(); j++) {
            int v = new_vec[j];
            min_w = min(min_w, A[removed][v]);
        }
        cost += min_w;
        minv = min(minv, cost);
    }
    return minv;
}

int main() {
    int n; cin >> n;
    vector<int> vec(n);
    A = vector<vector<int> >(n, vector<int>(n, MAXV));
    for (int i = 0; i < n; i++) {
        vec[i] = i;
        for (int j = 0; j < n; j++) {
            int a; cin >> a;
            if (a != -1) A[i][j] = a;
        }
    }

    int minv = solve(vec);
    cout << minv << endl;
}