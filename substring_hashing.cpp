#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds;
using namespace std;
using ll = long long;
// const int MOD = 1e9 + 7;
template <typename T> using pbds = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>; 

const int p1 = 137, p2 = 277, MOD1 = 2147483647, MOD2 = 1e9+7, mxN = 1e6 + 9;

int power (int x, int n, int MOD)
{
    int ans = 1%MOD;
    while (n)
    {
        if (n & 1)
        {
            ans = (1LL * ans%MOD * x%MOD);
        }
        x = 1LL * x * x % MOD;
        n>>=1;
    }
    return ans;
}

pair<int, int> pw[mxN], invpw[mxN];

void pre_calculate_power ()
{
    pw[0] = {1,1};
    for (int i = 1; i < mxN; i++)
    {
       pw[i].first = (1LL * pw[i-1].first * p1)%MOD1; 
       pw[i].second = (1LL * pw[i-1].second * p2)%MOD2; 
    }
    
    int ip1 = power(p1, MOD1-2, MOD1);  //! moduler inverse...
    int ip2 = power(p2, MOD2-2, MOD2);
    invpw[0] = {1,1};
    for (int i = 1; i < mxN; i++)
    {
       invpw[i].first = (1LL * invpw[i-1].first * ip1)%MOD1; 
       invpw[i].second = (1LL * invpw[i-1].second * ip2)%MOD2;
    }
}

pair<int, int> pref[mxN];

void build (string s)
{
    int n = s.size();
    for (int i = 0; i < n; i++)
    {
        pref[i].first = (1LL * s[i] * pw[i].first) % MOD1;
        if (i) pref[i].first = (1LL * pref[i].first + pref[i-1].first)%MOD1;
        
        pref[i].second = (1LL * s[i] * pw[i].second) % MOD2;
        if (i) pref[i].second = (1LL * pref[i].second + pref[i-1].second)%MOD2;
    }
}

pair<int, int> string_hash (string s)
{
    int n = s.size();
    pair<int, int> hash = {0, 0};
    
    for (int i = 0; i < n; i++)
    {
        hash.first = ((1LL * s[i] * pw[i].first) % MOD1 + (hash.first % MOD1)) % MOD1;
        hash.second = ((1LL * s[i] * pw[i].second) % MOD2 + (hash.second % MOD2)) % MOD2;
    }

    return hash;
}

pair<int, int> subString_hash (int i, int j)
{
    pair<int, int> hash ({0, 0});
    
    hash.first = pref[j].first;
    if (i) hash.first = (1LL * hash.first - pref[i-1].first + MOD1) % MOD1;
    hash.first = (1LL * hash.first * invpw[i].first) % MOD1;
    
    hash.second = pref[j].second;
    if (i) hash.second = (1LL * hash.second - pref[i-1].second + MOD2) % MOD2;
    hash.second = (1LL * hash.second * invpw[i].second) % MOD2;

    return hash;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    pre_calculate_power();
    
    string a, b;
    cin >> a >> b;
    
    build (a);

    int ans = 0, n = a.size(), m = b.size();
    auto hs = string_hash (b);

    for (int i = 0; i+m-1 < n; i++)
    {
        if (hs == subString_hash(i, i+m-1))
        {
            ans++;
        }
    }
    
    cout << ans << endl;
    
    return 0;
}