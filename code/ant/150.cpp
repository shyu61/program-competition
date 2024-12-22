// 接頭辞配列(最長回文): p342
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 回文を考える問題のポイント
// - 回文の中心をまず考える
// - 必ず偶奇で場合分けする

// 思考フロー
// 回文は中心で文字列を分割した時、逆転文字列との共通prefix部分になる -> LCP問題に帰着できそう
// -> LCP問題は文字列を結合してsa,lcpを計算し、条件を満たすlcpの最大値を取れば良い
// -> 条件を満たすlcpは、分割点をiとすると、前半部分は位置i, 後半部分は位置sl+sl-i となるlcp。これはsa上で連続しないのでRMQで求める
// <- ナイーブなLCP問題(文字列S,TのLCPを求める問題)では、ある文字列の共通prefixの最大値は必ず辞書順で隣接する部分文字列に存在するので、解の候補はlcp配列の中に存在することになる。
//    一方で回文のLCPの場合、解の候補となる共通prefixは辞書順で隣接しているとは限らないため、lcpを使って明示的に計算する必要がある

// ポイント
// LCP問題は、辞書順で隣接するものを解の候補として良いのか考える必要がある

const int INF = numeric_limits<int>::max();
int n, k;
vector<int> rnk, tmp;

struct RMQ {
    vector<int> dat;
    int sz = 1;

    RMQ() {}
    // n: 要素数, a: 初期化時に利用する値
    RMQ(int n, const vector<int>& a) {
        while (sz < n) sz *= 2;
        dat = vector<int>(sz * 2 - 1, -1);

        for (int i = 0; i < n; i++) dat[i + sz - 1] = a[i];
        for (int i = sz - 2; i >= 0; i--) {
            dat[i] = min(dat[i * 2 + 1], dat[i * 2 + 2]);
        }
    }

    // (value,index)
    int query(int a, int b, int k, int l, int r) {
        if (b <= l || r <= a) return INF;
        if (a <= l && r <= b) return dat[k];
        else {
            int vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
            int vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
            return min(vl, vr);
        }
    }

    // k: 要素番号, a: 更新値
    void update(int k, int a) {
        // ノード番号に変換
        k += sz - 1;
        dat[k] = a;
        while (k > 0) {
            k = (k - 1) / 2;
            dat[k] = min(dat[k * 2 + 1], dat[k * 2 + 2]);
        }
    }
};

bool compare_sa(int i, int j) {
    if (rnk[i] != rnk[j]) return rnk[i] < rnk[j];
    else {
        int ri = i + k <= n ? rnk[i + k] : -1;
        int rj = j + k <= n ? rnk[j + k] : -1;
        return ri < rj;
    }
}

void construct_sa(string S, vector<int>& sa) {
    rnk = tmp = vector<int>(n + 1);

    for (int i = 0; i <= n; i++) {
        sa[i] = i;
        rnk[i] = i < n ? S[i] : -1;
    }

    for (k = 1; k <= n; k *= 2) {
        sort(sa.begin(), sa.end(), compare_sa);

        tmp[sa[0]] = 0;
        for (int i = 1; i <= n; i++) {
            tmp[sa[i]] = tmp[sa[i - 1]] + (compare_sa(sa[i - 1], sa[i]) ? 1 : 0);
        }
        for (int i = 0; i <= n; i++) rnk[i] = tmp[i];
    }
}

void construct_lcp(string S, vector<int>& sa, vector<int>& lcp) {
    rnk = vector<int>(n + 1);
    for (int i = 0; i <= n; i++) rnk[sa[i]] = i;

    int h = 0;
    lcp[0] = 0;
    for (int i = 0; i < n; i++) {
        int j = sa[rnk[i] - 1];

        if (h > 0) h--;
        for (; j + h < n && i + h < n; h++) {
            if (S[j + h] != S[i + h]) break;
        }
        lcp[rnk[i] - 1] = h;
    }
}

int main() {
    string S; cin >> S;

    string T = S;
    reverse(T.begin(), T.end());
    string ST = S + '$' + T;
    n = ST.length();

    vector<int> sa(n), lcp(n);
    construct_sa(ST, sa);
    construct_lcp(ST, sa, lcp);
    RMQ rmq(n, lcp);

    int ans = 0, sl = S.length();

    // 文字iを中心とする奇数長の回文
    for (int i = 0; i < n; i++) {
        int j = sl * 2 - i;
        // 位置i,jのlcpを求める
        int l = rmq.query(min(rnk[i], rnk[j]), max(rnk[i], rnk[j]), 0, 0, rmq.sz);
        ans = max(ans, l * 2 - 1);
    }

    // 文字i-1と文字iを中心とする偶数長の回文
    for (int i = 1; i < n; i++) {
        int j = sl * 2 - i + 1;
        int l = rmq.query(min(rnk[i], rnk[j]), max(rnk[i], rnk[j]), 0, 0, rmq.sz);
        ans = max(ans, l * 2);
    }

    cout << ans << endl;
}
