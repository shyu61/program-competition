#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); i++)
const int M = 200;

// 🔷初見でどうやったら解けるか
// 部分和の剰余に関する問題。和の剰余なので配列の各要素はmodを取ってよく、その時点で閾値はmod未満になる。
// 閾値がmod未満になるのは、各要素だけではなく、部分和もである。故に高々mod+1通り調べれば良いことになる。

// 🔷抑えるべき抽象論は？
// 「和+剰余」問題では、各要素に加えて和の閾値もmodで絞られる

void output(vector<int>& a) {
    cout << a.size();
    for (auto v : a) cout << " " << v + 1;
    cout << endl;
}

int main() {
    int n; cin >> n;
    vector<int> a(n);
    rep(i, n) {
        cin >> a[i];
        a[i] %= M;
    }

    int m = min(n, 8);
    int m2 = 1 << m;
    vector<vector<int>> bk(M);
    for (int s = 1; s < m2; s++) {
        int sum = 0;
        vector<int> res;
        rep(i, m) {
            if (s >> i & 1) {
                sum = (sum + a[i]) % M;
                res.push_back(i);
            }
        }
        if (!bk[sum].empty()) {
            cout << "Yes" << endl;
            output(bk[sum]);
            output(res);
            return 0;
        }
        bk[sum] = res;
    }

    cout << "No" << endl;
}

int main() {
    int n; cin >> n;
    vector<int> a(n);
    rep(i, n) {
        cin >> a[i];
        a[i] %= M;
    }

    vector<vector<int>> cnt(M);
    rep(i, n) cnt[a[i]].push_back(i);
    rep(i, M) if (cnt[i].size() > 1) {
        vector<int> a = {cnt[i][0]}, b = {cnt[i][1]};
        cout << "Yes" << endl;
        output(a);
        output(b);
        return 0;
    }

    // dp[i番目までみた時][Bのmodがj][Cのmodがk]:=0,1,2
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(M, vector<int>(M)));
    dp[0][0][0] = 1;
    rep(i, n) rep(j, M) rep(k, M) {
        int nj = (j - a[i] + M) % M;
        int nk = (k - a[i] + M) % M;
        if (dp[i][j][k] == 2 || dp[i][nj][k] >= 1 || dp[i][j][nk] >= 1 || dp[i][nj][nk] == 2) dp[i + 1][j][k] = 2;
        else if (dp[i][j][k] == 1 || dp[i][nj][nk] == 1) dp[i + 1][j][k] = 1;
    }

    int mod = -1;
    for (int i = 1; i < M; i++) {
        if (dp[n][i][i] == 2) {
            mod = i;
            break;
        }
    }
    if (mod == -1) {
        cout << "No" << endl;
        return 0;
    }

    vector<int> bs, cs;
    int b = mod, c = mod;
    for (int i = n - 1; i >= 0; i--) {
        int nj = (b - a[i] + M) % M;
        int nk = (c - a[i] + M) % M;
        if (dp[i][nj][c] >= 1) {
            bs.push_back(i);
            b = nj;
        } else if (dp[i][b][nk] >= 1) {
            cs.push_back(i);
            c = nk;
        } else if (dp[i][b][c] == 2) {
            // pass
        } else {
            // dp[i][nj][nk] == 2
            bs.push_back(i);
            cs.push_back(i);
            b = nj;
            c = nk;
        }
    }

    reverse(bs.begin(), bs.end());
    reverse(cs.begin(), cs.end());

    cout << "Yes" << endl;
    output(bs);
    output(cs);
}
