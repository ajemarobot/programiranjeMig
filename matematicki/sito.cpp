#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<bool> is_prime(n + 1, true);

    for (int i = 2; i <= n; i++) {
        if (i > 3) {
            if (i % 6 != 1 && i % 6 != 5) {
                is_prime[i] = false;
            }
        }
    }

    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }

    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            cout << i << endl;
        }
    }

    return 0;
}
