#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)

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

int main() {
    int n, k; cin >> n >> k;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    CC c;
    rep(i, n) c.add(a[i]);

    vector<int> cnt(n);
    int l = 0, num = 0, ans = 0;
    rep(i, n) {
        int ai = c(a[i]);
        cnt[ai]++;
        if (cnt[ai] == 1) num++;
        if (num <= k) ans = max(ans, i - l + 1);
        else {
            while (num > k) {
                int al = c(a[l]);
                cnt[al]--;
                if (cnt[al] == 0) num--;
                l++;
            }
        }
    }
    cout << ans << endl;
}

int main() {
    int n, k; cin >> n >> k;
    vector<int> a(n);
    rep(i, n) cin >> a[i];

    unordered_map<int, int> mp;
    int l = 0, ans = 0;
    rep(i, n) {
        mp[a[i]]++;
        if (mp.size() <= k) {
            ans = max(ans, i - l + 1);
        } else {
            while (mp.size() > k) {
                mp[a[l]]--;
                if (mp[a[l]] == 0) mp.erase(a[l]);
                l++;
            }
        }
    }
    cout << ans << endl;
}
