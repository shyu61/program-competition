#include <bits/stdc++.h>
using namespace std;

// https://youtu.be/fR3W5IcBGLQ?t=8550
template<typename T=int>
struct CC {
    bool initialized;
    vector<T> xs;

    CC(): initialized(false) {}
    void add(T x) { xs.push_back(x); }
    void init() {
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        initialized = true;
    }
    int size() {
        if (!initialized) init();
        return xs.size();
    }

    int operator()(T x) {
        if (!initialized) init();
        return lower_bound(xs.begin(), xs.end(), x) - xs.begin();
    }
    T operator[](int i) {
        if (!initialized) init();
        return xs[i];
    }
};
