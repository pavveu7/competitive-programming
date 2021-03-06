#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void countSort(vector<int>& order, vector<int>& keys)  {
    int n = order.size();

    vector<int> cnt(n, 0);
    for (auto x : keys) {
        cnt[x]++;
    }
    vector<int> pos(n); // position in bucket

    pos[0] = 0;
    for (int i = 1; i < n; i++) {
        pos[i] = pos[i - 1] + cnt[i - 1];
    }

    vector<int> newOrder(n);
    for (auto i : order) {
        int key = keys[i];
        newOrder[pos[key]] = i;
        pos[key]++;
    }
    order = newOrder;
}

vector<int> createSuffixArray(string s) {
    s += "$";
    int n = s.size();

    vector<int> p(n), c(n);

    // k = 0;
    {

        iota(begin(p), end(p), 0);
        sort(begin(p), end(p), [&](int a, int b){
            if ( s[a] != s[b] ) return s[a] < s[b];
            else return a < b;
        });

        c[p[0]] = 0;
        for(int i = 1; i < n; i++) {
            if ( s[p[i]] == s[p[i - 1]] ) {
                c[p[i]] = c[p[i - 1]];
            }
            else {
                c[p[i]] = c[p[i - 1]] + 1;
            }
        }
    }

    int k = 0;
    while ( (1<<k) < n ) {
        for (auto &i : p) i = (i - (1<<k) + n) % n;

        countSort(p, c);

        vector<int> cNew(n);
        cNew[p[0]] = 0;
        for(int i = 1; i < n; i++) {
            pair<int, int> last { c[p[i - 1]], c[(p[i - 1] + (1<<k)) % n]};
            pair<int, int> now { c[p[i]], c[(p[i] + (1<<k)) % n]};

            if ( now == last ) {
                cNew[p[i]] = cNew[p[i - 1]];
            }
            else {
                cNew[p[i]] = cNew[p[i - 1]] + 1;
            }
        }
        c = cNew;
        k++;
    }

    return p;
}

vector<int> createLCPArray(string s, vector<int>& p) {
    int n = p.size();
    vector<int> pInv(n);
    for (int i = 0; i < n; i++)
        pInv[p[i]] = i;

    vector<int> lcp(n);

    int k = 0;
    for (int i = 0; i < n - 1; i++) {
        int pi = pInv[i];
        int j = p[pi - 1];

        while ( s[i + k] == s[j + k] ) k++;

        lcp[pi] = k;
        k = max(k - 1, 0);
    }

    return lcp;
}

int main() {
    ios::sync_with_stdio(0);
    string s; 
    cin >> s;

    auto p { createSuffixArray(s) };
    auto lcp { createLCPArray(s, p) };

    ll n = s.size();
    ll allSubs = n * ( n + 1 ) / 2;
    ll same = accumulate(begin(lcp),end(lcp), 0ll);

    cout << allSubs - same << "\n";

    return 0;
}