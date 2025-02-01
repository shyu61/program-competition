#include <bits/stdc++.h>
using namespace std;

int to_decimal(const vector<int>& a) {
    int res = 0;
    for (auto ai : a) res = (res << 1) | ai;
    return res;
}

int string_to_int(string s) {
    return stoi(s);
}

int char_to_int(char c) {
    return int(c - '0');
}

string int_to_string(int i) {
    return to_string(i);
}
