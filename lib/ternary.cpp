#include<bits/stdc++.h>
using namespace std;

int main() {
    // s: 集合, i: 位置, v: 変更値(0-2)
    auto get = [&](int s, int i) -> int { return s >> 2 * i & 3; };
    auto set = [&](int& s, int i, int v) -> void { s = (s & ~(3 << 2 * i)) | (v << 2 * i); };
}
