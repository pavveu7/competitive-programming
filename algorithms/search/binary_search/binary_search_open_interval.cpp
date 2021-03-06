/*
* author: pavveu
* task: 
*       Determine if value x exists in sorted array A 
* solution:
*       Binary Search
* time: 
*       O(logn)
*/

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;

#define FOR(name__, upper__) for (int name__ = 0; name__ < (upper__); ++name__)
#define all(x) begin(x), end(x)
#define mp make_pair
#define mt make_tuple

bool bin_search(vi& a, int x) {
    int n = a.size();

    int l = -1;     // a[l] < l
    int r = n;      // a[r] >= x,
    while ( r - l > 1 ) {
        int m = l + (r - l)/2;
        if ( a[m] >= x ) r = m;
        else l = m;
    }

    //                  < x       |     >= x 
    // a[0], ... , a[l - 1] a[l] | a[r], a[r + 1], ... a[n - 1]

    if ( r < n && a[r] == x ) return true;
    else return false;
}

void go() {
    vi a { 5, 12, 125, -2, 252, 12, -54, 13, 123, 111, -100, 23 };
    sort(all(a));
    for(int i : a) assert(bin_search(a, i));
    assert(!bin_search(a, 1000));
    assert(!bin_search(a, 0));
    assert(!bin_search(a, -3));
    assert(!bin_search(a, 3));
    assert(!bin_search(a, 6));
}

int main() {
	ios::sync_with_stdio(false); 
	cin.tie(0);
	go();

	return 0;
}
