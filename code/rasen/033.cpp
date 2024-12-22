#include <iostream>
#include <map>
using namespace std;

map<string, bool> M;


int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string com, s;
        cin >> com >> s;
        if (com == "insert") M[s] = true;
        else {
            cout << "=====" << M[s] << endl;
            if (M[s]) cout << "yes" << endl;
            else cout << "no" << endl;
        }
    }
}