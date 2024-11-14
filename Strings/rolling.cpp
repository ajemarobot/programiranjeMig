#include <bits/stdc++.h>
using namespace std;
 
int hashingStrings(int n, char a, char b)
{
    int x = a - '0';
    int y = b - '0';
    n -= x;
    n += y;
    return n;
}
 
int main()
{
    string s, subs;
    cin >> s >> subs;
    int subs_size = subs.size();
    int s_size = s.size();
    int hehs[s_size];
    int hehes[s_size];
    int a = 0;
 
    memset(hehs, 0, sizeof(hehs));
    memset(hehes, 0, sizeof(hehes));
 
    for (int i = 0; i < subs_size; i++)
    {
        hehs[0] += (s.at(i) - '0');
        a += (subs.at(i) - '0');
    }
 
    if (a == hehs[0]) hehes[0] = 1;
 
    for (int i = 1; i <= s_size - subs_size; i++)
    {
        hehs[i] = hashingStrings(hehs[i - 1], s.at(i - 1), s.at(i + subs_size - 1));
        if (a == hehs[i]) hehes[i] = 1;
    }
 
    for (int i = 0; i <= s_size - subs_size; i++)
    {
        cout << hehes[i] << " ";
    }
 
    return 0;
}
