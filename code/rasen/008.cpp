#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int main() {
    stack<int> S1;
    stack<pair<int, int> > S2;
    int sum = 0;
    char s;

    for (int i = 0; cin >> s; i++) {
        if (s == '\\') {
            S1.push(i);
        } else if (s == '/' && !S1.empty()) {
            int j = S1.top();
            int a = i - j;
            sum += a;
            S1.pop();

            while (!S2.empty() && j < S2.top().first) {
                a += S2.top().second;
                S2.pop();
            }
            S2.push(make_pair(j, a));
        }
    }

    cout << sum << endl;
    cout << S2.size();

    vector<int> vec;
    int len = S2.size();
    for (int i = 0; i < len; i++) {
        vec.push_back(S2.top().second);
        S2.pop();
    }

    for (int i = len - 1; i >= 0; i--) {
        cout << " " << vec[i];
    }
    cout << endl;

    return 0;
}