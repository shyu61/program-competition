// バケット法と平方分割: p168
#include <bits/stdc++.h>
using namespace std;

// バケット法: 分割した区間の代表値を使って計算量を落とすという設計は、セグ木と同じ。ただし、区間幅が一定でセグ木より実装がシンプル

// バケット法を使う時必ずしも平方分割が最適とは限らない。
// k番目の数を得るためにまず区間をソートしたい -> O(nmlogn)で間に合わない
// -> クエリごとにソートするのは無理なので、区間問題であることを考慮して区間を高速に処理する構造体にソートを持たせて結果をマージすればいい
// 区間のアルゴリズムといえば、セグ木/sparse-table/BIT/尺取り法/累積和/バケット法。今回は和や最小/最大ではなくk-th numberなので汎用性が高いセグ木もしくはバケット法を検討する。
// つまりバケットごとにソート列を持つ、もしくはセグ木の各ノードにソート列を持つことを考える
// バケット法とセグ木は全く構造が違うので区間の取り扱い方が違うので注意。いずれにしても最大のポイントは、"どうやって区間をmergeするか"

// バケット法で考える場合
// 2つのソートされた区間同士のmergeで新たなソート列を構築する場合、O(n1+n2)コストがかかる。これは結局O(nmlogn)になり間に合わない。
// -> つまりk-th numberをソート列から求めるのは不可能で、言い換える必要があることに気付く。
// -> そこでk-th number = xと置いた時、x以下の個数がkになるようなxを探索する問題に変換することができる。
// そうすると完全なソート済み配列を用意する必要はなく、各ソート済み配列ごとにx以下の個数を数えて合計すれば良いことがわかる
// -> 計算量はO(log√n * √n + √n)なので、O(m√nlog√n)で間に合う

// セグ木で考える場合
// 考え方はバケット法と全く同じ。

// 抽象化
// 最大/最小に加えて、kth-numberも境界判定問題に帰着できる。というか最大/最小は、first-number,last-numberなのでkth-numberの特殊ケースと考えても良いかもしれない。

int main() {
    int n, m; cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // バケット法でバケット毎にsort列を用意しておく
    int n2 = sqrt(n);
    vector<vector<int>> bk(n / n2 + 1);
    for (int i = 0; i < n; i++) {
        bk[i / n2].push_back(a[i]);
        if ((i + 1) % n2 == 0) {
            sort(bk[i / n2].begin(), bk[i / n2].end());
        }
    }

    vector<int> sorted = a;
    sort(sorted.begin(), sorted.end());

    while (m--) {
        int l, r, k; cin >> l >> r >> k; l--;

        // 二分探索: mid番目の数以下の数がk個以下か判定
        int lb = n, ub = -1;
        while (lb - ub > 1) {
            int mid = (lb + ub) / 2;
            int x = sorted[mid];
            int tl = l, tr = r, cnt = 0;

            // 境界バケットを処理
            while (tl < tr && tl % n2 != 0) if (a[tl++] <= x) cnt++;
            while (tl < tr && tr % n2 != 0) if (a[--tr] <= x) cnt++;

            // 完全に含まれるバケットを処理
            while (tl < tr) {
                int i = tl / n2;
                cnt += upper_bound(bk[i].begin(), bk[i].end(), x) - bk[i].begin();
                tl += n2;
            }

            // true: 下限を緩和
            cnt < k ? ub = mid : lb = mid;
        }
        cout << sorted[lb] << '\n';
    }
}
