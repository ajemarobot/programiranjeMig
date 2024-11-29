#include <bits/stdc++.h>
using namespace std;


class Vektor {
private:
    int* data;
    size_t size;
    size_t capacity;

    void resize() {
        capacity = capacity == 0 ? 1 : capacity * 2;
        int* newData = new int[capacity];
        for (size_t i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }

public:
    Vektor() : data(nullptr), size(0), capacity(0) {}

    ~Vektor() {
        delete[] data;
    }

    void push_back(int value) {
        if (size == capacity) {
            resize();
        }
        data[size++] = value;
    }

    int operator[](size_t index) const {
        return data[index];
    }

    size_t getSize() const {
        return size;
    }

    int* begin() { return data; }
    int* end() { return data + size; }

    bool isEmpty() const {
        return size == 0;
    }
};

class String {
    char* chars;
    int length;

public:
    String(char* str="")
    {
        length = strlen(str);
        chars = new char[length + 1];
        strcpy(chars, str);
    }

    String(const String& s)
    {
        length = s.length;
        chars = new char[length + 1];
        strcpy(chars, s.chars);
    }

    ~String() {
        delete[] chars;
    }

    String& operator=(const String& other)
    {
        if (this != &other)
        {
            delete[] chars;
            length = other.length;
            chars = new char[length + 1];
            strcpy(chars, other.chars);
        }
        return *this;
    }

    int* buildKMPTable(char* pattern)
    {
        int patternLength = strlen(pattern);
        int* kmpTable = new int[patternLength];
        kmpTable[0] = 0;
        int preth = 0;

        for (int i=1;i<patternLength;i++)
        {
            while (preth>0 && pattern[i]!=pattern[preth])
                preth = kmpTable[preth-1];

            if (pattern[i] == pattern[preth]) preth++;

            kmpTable[i] = preth;
        }
        return kmpTable;
    }

    Vektor findAllSubStr(const String& subStr) {
        Vektor results;
        int resultCount = 0;

        int* kmpTable = buildKMPTable(subStr.chars);
        int j = 0;

        for (int i=0;i<length;i++) {
            while (j>0 && chars[i]!=subStr.chars[j]) {
                j = kmpTable[j-1];
            }
            if (chars[i] == subStr.chars[j]) {
                j++;
            }
            if (j==subStr.length) {
                results.push_back( i-j+1);
                j = kmpTable[j-1];
            }
        }
        delete[] kmpTable;
        return results;
    }

    int findFirstSubStr(const String& subStr) {
        int* kmpTable = buildKMPTable(subStr.chars);
        int j = 0;

        for (int i=0;i<length;i++)
        {
            while (j>0 && chars[i] != subStr.chars[j]) {
                j = kmpTable[j-1];
            }
            if (chars[i] == subStr.chars[j]) {
                j++;
            }
            if (j == subStr.length)
            {
                delete[] kmpTable;
                return i-j +1;
            }
        }
        delete[] kmpTable;
        return -1;
    }

    int* buildKMPTableReverse(const char* pattern) {
        int patternLength = strlen(pattern);
        int* kmpTable = new int[patternLength];
        kmpTable[patternLength-1] = 0;
        int j=0;

        for (int i=patternLength-2;i>=0;i--) {
            while (j>0 && pattern[i] != pattern[patternLength-j-1]) {
                j = kmpTable[patternLength - j];
            }
            if (pattern[i] == pattern[patternLength-j-1]) {
                j++;
            }
            kmpTable[i] = j;
        }
        return kmpTable;

    }

    int findLastSubStr(String& subStr) {
        int* kmpTable = buildKMPTableReverse(subStr.chars);
        int j = 0;

        for (int i=length-1;i>=0;i--) {
            while (j>0 && chars[i] != subStr.chars[subStr.length-j-1])
            {
                j = kmpTable[subStr.length-j];
            }
            if (chars[i] == subStr.chars[subStr.length-j-1]) {
                j++;
            }
            if (j == subStr.length)
            {
                delete[] kmpTable;
                return i;
            }
        }
        delete[] kmpTable;
        return -1;
    }
};

int main()
{
    String Str("bananarama");
    String subStr("ana");

    Vektor all= Str.findAllSubStr(subStr);
    cout<<"Site pojavuvanja: ";
    for (auto pojava : all)
    {
        cout<<++pojava<<" ";
    }
    cout<<endl;

    int first= Str.findFirstSubStr(subStr);
    cout<<"Prvo pojavuvanje: "<< ++first<<endl;

    int last = Str.findLastSubStr(subStr);
    cout<<"Posledno pojavuvanje: "<<++last<<endl;

    return 0;
}
