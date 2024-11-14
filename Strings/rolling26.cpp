#include <bits/stdc++.h>
using namespace std;

vector<int> rolling_hash(string s, int window_size,int base = 26,int mod = 1000000007)
{
    int n = s.length();
    vector<int> power(n + 1, 1);
    vector<int> hash_values(n - window_size + 1);

    for (int i = 1; i <= n; i++)
    {
        power[i] = (power[i - 1] * base) % mod;
    }

    int current_hash = 0;
    for (int i = 0; i < window_size; i++)
    {
        current_hash = (current_hash * base + s[i]) % mod;
    }
    hash_values[0] = current_hash;

    for (int i = 1; i <= n - window_size; i++)
    {
        current_hash = (current_hash - power[window_size - 1] * s[i - 1])% mod;

        current_hash= (current_hash * base + s[i + window_size - 1])% mod;

        hash_values[i] = current_hash;
    }
    return hash_values;
}

int main()
{

    string s,subs;
    cin>>s>>subs;

    int k;
    cin>>k;

    vector<int> hashs = rolling_hash(s, k);
        vector<int> hahas = rolling_hash(subs,k);

    for (auto& val : hashs)
    {
        bool t = val==hahas[0];
        cout<<t;
    }
    cout << endl;

    return 0;
}

