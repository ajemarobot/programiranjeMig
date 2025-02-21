#include <bits/stdc++.h>
using namespace std;

class LONG_INT
{
    string data;
public:
    LONG_INT(string data)
    {
        this->data = removeLeadingZeros(data);
    }

    static string removeLeadingZeros(string num)
    {
        while (num.size() > 1 && num[0] == '0')
        {
            num.erase(num.begin());
        }
        return num;
    }

    bool operator>=(const LONG_INT &other) const
    {
        if (data.size() > other.data.size()) return true;
        if (data.size() < other.data.size()) return false;
        return data >= other.data;
    }

    bool operator<(const LONG_INT &other) const
    {
        return !(*this >= other);
    }

    bool operator<=(const LONG_INT &other) const
    {
        return (*this < other) || (*this == other);
    }

    bool operator==(const LONG_INT &other) const
    {
        return data == other.data;
    }
    bool operator!=(const LONG_INT &other) const
    {
        return data != other.data;
    }

    string operator+(const LONG_INT &other) const
    {
        string a = data;
        string b = other.data;
        string result = "";
        int carry = 0;

        int a_size = a.size(), b_size = b.size(), n = max(a_size, b_size);
        for (int i = 0; i < n; ++i)
        {
            int digit1 = (i < a_size) ? a[a_size - 1 - i] - '0' : 0;
            int digit2 = (i < b_size) ? b[b_size - 1 - i] - '0' : 0;
            int sum = digit1 + digit2 + carry;
            carry = sum / 10;
            result.push_back(sum % 10 + '0');
        }

        if (carry) result.push_back(carry + '0');
        reverse(result.begin(), result.end());
        return result;
    }

    string operator-(const LONG_INT &other) const
    {
        string a = data;
        string b = other.data;
        bool isNegative = false;

        if (*this < other)
        {
            swap(a, b);
            isNegative = true;
        }

        string result = "";
        int borrow = 0;

        int a_size = a.size(), b_size = b.size();
        for (int i = 0; i < a_size; ++i)
        {
            int digit1 = a[a_size - 1 - i] - '0';
            int digit2 = (i < b_size) ? b[b_size - 1 - i] - '0' : 0;
            digit1 -= borrow;
            if (digit1 < digit2)
            {
                digit1 += 10;
                borrow = 1;
            }
            else
            {
                borrow = 0;
            }
            result.push_back((digit1 - digit2) + '0');
        }

        while (result.size() > 1 && result.back() == '0') result.pop_back();
        reverse(result.begin(), result.end());

        if (isNegative) result.insert(result.begin(), '-');
        return result;
    }

    string operator*(const LONG_INT &other) const
    {
        string a = data, b = other.data;
        int a_size = a.size(), b_size = b.size();
        vector<int> result(a_size + b_size, 0);

        for (int i = a_size - 1; i >= 0; --i)
        {
            for (int j = b_size - 1; j >= 0; --j)
            {
                int mul = (a[i] - '0') * (b[j] - '0');
                int sum = mul + result[i + j + 1];
                result[i + j + 1] = sum % 10;
                result[i + j] += sum / 10;
            }
        }

        string result_str;
        for (int num : result)
        {
            if (!(result_str.empty() && num == 0))
                result_str.push_back(num + '0');
        }
        return result_str.empty() ? "0" : result_str;
    }

    string operator/(const LONG_INT &other) const
    {
        if (other.data == "0") throw runtime_error("Division by zero");

        string result = "";
        string current = "";
        LONG_INT divisor = other;

        for (char digit : data)
        {
            current += digit;
            current = removeLeadingZeros(current);
            int count = 0;

            while (LONG_INT(current) >= divisor)
            {
                current = LONG_INT(current) - divisor;
                count++;
            }

            result.push_back(count + '0');
        }

        result = removeLeadingZeros(result);
        return result.empty() ? "0" : result;
    }

    string operator%(const LONG_INT &other) const
    {
        if (other.data == "0") throw runtime_error("Modulo by zero");

        string current = "";
        for (char digit : data)
        {
            current += digit;
            current = removeLeadingZeros(current);
            while (LONG_INT(current) >= other)
            {
                current = LONG_INT(current) - other;
            }
        }
        return current;
    }

    string operator^(const LONG_INT &exponent) const
    {
        if (exponent.data == "0") return "1";
        LONG_INT result("1");
        LONG_INT base = *this;
        LONG_INT exp = exponent;

        while (exp.data != "0")
        {
            if ((exp.data.back() - '0') % 2 == 1)
            {
                result = result * base;
            }
            base = base * base;
            exp = exp / LONG_INT("2");
        }
        return result.data;
    }

    vector<pair<string, int>> canonicalFactorization()
    {
        vector<pair<string, int>> factors;
        LONG_INT n = *this, two("2");

        while (n % two == "0")
        {
            if (factors.empty() || factors.back().first != "2")
                factors.emplace_back("2", 0);
            factors.back().second++;
            n = n / two;
        }

        for (LONG_INT i = LONG_INT("3"); LONG_INT(i * i) <= n; i = LONG_INT(i + LONG_INT("2")))
        {
            while (n % i == "0")
            {
                if (factors.empty() || factors.back().first != i.data)
                    factors.emplace_back(i.data, 0);
                factors.back().second++;
                n = n / i;
            }
        }

        if (n.data != "1") factors.emplace_back(n.data, 1);
        return factors;
    }



    string lucasTest()
    {
        LONG_INT n = LONG_INT(this->data);
        if (*this == LONG_INT("1"))
            return "neither prime nor composite";
        if (*this == LONG_INT("2"))
            return "prime";
        if (*this % LONG_INT("2") == "0")
            return "composite";

        vector<pair<string, int>> factors = n.canonicalFactorization();

        for (LONG_INT a = LONG_INT("2"); a < *this; a = a + LONG_INT("1"))
        {
            if (LONG_INT(a ^ LONG_INT( *this - LONG_INT("1")) ) != LONG_INT("1"))
                return "composite";

            bool flag = true;
            for (auto &factor : factors)
            {
                LONG_INT q(factor.first);
                if (LONG_INT(LONG_INT(a ^ LONG_INT(LONG_INT(*this - LONG_INT("1"))/ q))) == LONG_INT("1"))
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
                return "prime";
        }
        return "probably composite";
    }
    bool miillerTest(LONG_INT d, LONG_INT n)
    {

        LONG_INT a = LONG_INT(this->data);
        LONG_INT x = LONG_INT(LONG_INT(a^d)% n);

        if (x == LONG_INT("1") || x == LONG_INT(n-LONG_INT("1")))
            return true;

        while (d != LONG_INT(n-LONG_INT("1")))
        {
            x = LONG_INT(LONG_INT(x * x) % n);
            d = LONG_INT(d * LONG_INT("2"));
            if (x == LONG_INT("1")) return false;
            if (x == LONG_INT(n-LONG_INT("1"))) return true;
        }
        return false;
    }

    bool isPrime(LONG_INT k, LONG_INT n)
    {
        if (n <= LONG_INT("1") || n == LONG_INT("4")) return false;
        if (n <= LONG_INT("3")) return true;
        LONG_INT d = LONG_INT(n - LONG_INT("1"));
        while (LONG_INT(d % LONG_INT("2")) == LONG_INT("0"))
            d = LONG_INT(d / LONG_INT("2"));
        for (LONG_INT i = LONG_INT("0"); i < k; i = LONG_INT(i + LONG_INT("1")))
            if (!miillerTest(d, n))
                return false;

        return true;
    }
};

int main()
{
    LONG_INT test("1234567890123456789531");
    vector<pair<string, int>> factors = test.canonicalFactorization();
    for (auto &p : factors)
        cout << p.first << "^" << p.second << " ";
    cout << endl;

    LONG_INT a("10000000000000000000");
    LONG_INT b("999999999999939994995132132");
    cout << (a - b) << endl;

    LONG_INT c("1234534234234234243243243234");
    LONG_INT d("9876523423423424234234");
    cout << (c * d) << endl;

    LONG_INT e("1000000000000000000000000");
    LONG_INT f("5131231312223");
    cout << (e / f) << endl;

    LONG_INT g("123456789");
    LONG_INT h("112312");
    cout << (g % h) << endl;

    LONG_INT i("2");
    LONG_INT j("1000");
    cout << (i ^ j) << endl;

    LONG_INT k("9973482422");
    cout << "Lucas test for 9973482422" << ": " << k.lucasTest() << endl;

    return 0;
}
