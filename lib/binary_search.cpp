#include <bits/stdc++.h>
using namespace std;

// https://x.com/meguru_comp/status/697008509376835584/photo/4

int main() {
    auto check = [&](int mid) -> bool {
        // TODO
    };

    int ok, ng; // TODO
    while (abs(ok - ng) > 1) {
        int mid = (ok + ng) / 2;
        check(mid) ? ok = mid : ng = mid;
    }
}
