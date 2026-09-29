#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds;
using namespace std;
using ll = long long;
// const int MOD = 1e9 + 7;
template <typename T> using pbds = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>; 

const int p1 = 137, p2 = 277, MOD1 = 2147483647, MOD2 = 1e9+7, mxN = 1e5 + 9;
int pw1[mxN], pw2[mxN];

void pre_calculate_power ()
{
    pw1[0] = 1;
    for (int i = 1; i < mxN; i++)
    {
        pw1[i] = (1LL * pw1[i-1] * p1)%MOD1;
    }
    pw2[0] = 1;
    for (int i = 1; i < mxN; i++)
    {
        pw2[i] = (1LL * pw2[i-1] * p2)%MOD2;
    }
}

pair<int, int> get_hash (string a)
{
    int n = a.size();
    int hash1 = 0, hash2 = 0;
    for (int i = 0; i < n; i++)
    {
        hash1 += (1LL * a[i] * pw1[i]) % MOD1;
        hash1 %= MOD1;
    }
    for (int i = 0; i < n; i++)
    {
        hash2 += (1LL * a[i] * pw2[i]) % MOD2;
        hash2 %= MOD2;
    }
    return {hash1, hash2};
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    pre_calculate_power ();

    string a, b;
    cin >> a >> b;

    if (get_hash(a) == get_hash(b))
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
    
    return 0;
}