// バケット法と平方分割: p168
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

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

// テクニック
// 区間を左から見ていく時、ポインターを動かしつつ処理するとシンプルに書ける

int main() {
    int n, m; cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int b = sqrt(n);
    vector<vector<int>> bc(n / b + 1);
    for (int i = 0; i < n; i++) {
        bc[i / b].push_back(a[i]);
        if ((i + 1) % b == 0) {
            sort(bc[i / b].begin(), bc[i / b].end());
        }
    }

    vector<int> nums = a;
    sort(nums.begin(), nums.end());

    for (int q = 0; q < m; q++) {
        int l, r, k; cin >> l >> r >> k;
        r++;

        // 二分探索を考える時は、lbは常に条件を満たさない、ubは常に条件を満たすようにとる
        int lb = -1, ub = n - 1;
        while (ub - lb > 1) {
            int m = (lb + ub) / 2;
            int x = nums[m];

            // m以下の個数が丁度k個かどうか判定
            int tl = l, tr = r, cnt = 0;

            // 境界のバケットに対する処理
            // 条件を満たさなくなるまでループを回したい時、終了地点を求めてforで書くよりも、whileで書いてしまう方が簡単でミスが減る
            while (tl < tr && tl % b != 0) if (a[tl++] <= x) cnt++;
            while (tl < tr && tr % b != 0) if (a[--tr] <= x) cnt++;

            // 完全に含まれるバケットに対する処理
            while (tl < tr) {
                int t = tl / b;
                cnt += upper_bound(bc[t].begin(), bc[t].end(), x) - bc[t].begin();
                tl += b;
            }

            // is_ok(m)ならub=m
            if (cnt >= k) ub = m;
            else lb = m;
        }

        cout << nums[ub] << endl;
    }
}
