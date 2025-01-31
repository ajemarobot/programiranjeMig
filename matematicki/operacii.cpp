#include <bits/stdc++.h>
using namespace std;

class LONG_INT
{
    string data;
public:
    LONG_INT(string data)
    {
        this->data = data;
    }
        static string removeLeadingZeros(string num)
    {
        while (num.size() > 1 && num[0] == '0')
        {
            num.erase(num.begin());
        }
        return num;
    }

     bool operator>=(const LONG_INT &other) const {
        if (data.size() > other.data.size()) return true;
        if (data.size() < other.data.size()) return false;
        return data >= other.data;
    }

    bool operator<(const LONG_INT &other) const {
        return !(*this >= other);
    }

    string mod(LONG_INT b)
    {
        string delenik = data;
        string delitel = b.data;

        LONG_INT remainder("0");
        for (char digit : delenik)
        {
            remainder.data += digit;
            remainder.data = removeLeadingZeros(remainder.data);

            int count = 0;
            while (LONG_INT(remainder.data) >=LONG_INT(delitel))
            {
                remainder =LONG_INT(remainder.data) - LONG_INT(delitel);
            }
        }
        return remainder.data;
    }

    /**string gcd(LONG_INT b)
    {
        LONG_INT a = *this;
        while (b.data != "0")
        {
            LONG_INT temp = b;
            b = LONG_INT(a.mod(b));
            a = temp;
        }
        return a.data;
    }

    string lcm(LONG_INT b)
    {
        LONG_INT a = *this;
        LONG_INT gcd_value = gcd(b);
        LONG_INT product = a * b;
        return (product / gcd_value).data;
    }*/
/// radi nekoja magepsna pricina sto veruvam ni toj so go sozdal c++ ne znae da ja otkrie gcd_value compilerot mi go registrira kako string wtf ne e string i zatoa nemam cool feature nzd i nzs, nejse drugoto e ok
    string operator+(LONG_INT dat)
    {
        string a = data;
        string b = dat.data;
        string result = "";
        int carry = 0;

        int a_size = a.size();
        int b_size = b.size();
        int n = max(a_size, b_size);

        for(int i = 0; i < n; ++i)
        {
            int digit1 = (i < a_size) ? a[a_size - 1 - i] - '0' : 0;
            int digit2 = (i < b_size) ? b[b_size - 1 - i] - '0' : 0;
            int sum = digit1 + digit2 + carry;
            carry = sum / 10;
            result.push_back(sum % 10 + '0');
        }

        if(carry)
        {
            result.push_back(carry + '0');
        }

        reverse(result.begin(), result.end());
        return result;
    }
    string operator-(LONG_INT dat)
    {
        string a = data;
        string b = dat.data;
        string result = "";
        int carry = 0;

        int a_size = a.size();
        int b_size = b.size();
        int n = max(a_size, b_size);

        for(int i = 0; i < n; ++i)
        {
            int digit1 =(i < a_size) ? a[a_size - 1 - i] - '0' : 0;
            int digit2 =(i < b_size) ? b[b_size - 1 - i] - '0' : 0;
            int sum = digit1+ digit2 + carry;
            carry = sum / 10;
            result.push_back(sum % 10 + '0');
        }

        if(carry)
        {
            result.push_back(carry +'0');
        }

        reverse(result.begin(),result.end());
        return result;
    }
    string operator*(LONG_INT dat)
    {
        string a = data;
        string b = dat.data;

        int a_size = a.size();
        int b_size =b.size();

        vector<int> result(a_size + b_size, 0);

        for(int i = a_size - 1; i >= 0; --i)
        {
            for(int j = b_size - 1; j >= 0; --j)
            {
                int mul = (a[i] - '0') * (b[j] - '0');
                int sum = mul+result[i + j + 1];
                result[i + j + 1] = sum % 10;
                result[i + j] += sum / 10;
            }
        }

        string result_str;
        for(int num : result)
        {
            if(!(result_str.empty() && num == 0))
            {
                result_str.push_back(num + '0');
            }
        }

        return result_str.empty() ? "0" : result_str;
    }
    string operator/(LONG_INT dat)
    {
        string delenik = data;
        string delitel = dat.data;

        string result = "";
        string current = "0";

        for(char digit :delenik)
        {
            current += digit;
            if(current.size() > 1 && current[0] == '0')
            {
                current.erase(current.begin());
            }

            int k_digit = 0;
            while(current.size() > delitel.size() || (current.size() == delitel.size() && current >= delitel))
            {
                current=LONG_INT(current)-LONG_INT(delitel);
                ++k_digit;
            }

            result.push_back(k_digit +'0');
        }

        while(result.size() >1 && result[0] == '0')
        {
            result.erase(result.begin());
        }

        return result.empty() ? "0" : result;
    }



};

int main()
{
    LONG_INT n1("12"), n2("123");
    cout << n1 + n2<<endl;
    cout<<12+123<<endl;
    cout << n1 * n2<<endl;
    cout<<12*123<<endl;
    cout<<n1-n2<<endl;
    cout<<12-123<<endl;
    cout << n1 / n2<<endl;
    cout<<12/123<<endl;

    return 0;
}
