#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds;
using namespace std;
using ll = long long;
const int MOD = 1e9 + 7;
template <typename T> using pbds = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>; 

const int p = 137, mxN = 1e5 + 9;
int pw[mxN];

void pre_calculate_power ()
{
    pw[0] = 1;
    for (int i = 1; i < mxN; i++)
    {
        pw[i] = (1LL * pw[i-1] * p)%MOD;
    }
}

int get_hash (string a)
{
    int n = a.size();
    int hash = 0;
    for (int i = 0; i < n; i++)
    {
        hash += (1LL * a[i] * pw[i]) % MOD;
        hash %= MOD;
    }
    return hash;
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