#include <bits/stdc++.h>
using namespace std;

// https://x.com/meguru_comp/status/697008509376835584/photo/4

int main() {
    auto is_ok = [&](int mid) -> bool {
        // TODO
    };

    int ok, ng; // TODO
    while (ok - ng > 1) {
        int mid = (ok + ng) / 2;
        is_ok(mid) ? ok = mid : ng = mid;
    }
}
