#include <bits/stdc++.h>

using namespace std;

class TrieNode {
public:
     string prefix;
    bool isEndOfWord;
     unordered_map<char, TrieNode*> children;

    TrieNode(const  string& prefix = "")
        {
            this->prefix=prefix;
            this->isEndOfWord=false;
        }
};

class PatriciaTrie {
private:
    TrieNode* root;

    int commonPrefixLength(const  string& a, const  string& b) {
        int len = 0;
        while (len < a.size() && len < b.size() && a[len] == b[len]) {
            len++;
        }
        return len;
    }

    void findWords(TrieNode* node, const  string& currentWord,  vector< string>& results) {
        if (node->isEndOfWord) {
            results.push_back(currentWord);
        }
        for (const auto& child : node->children) {
            findWords(child.second, currentWord + child.second->prefix, results);
        }
    }

public:
    PatriciaTrie() {
        root = new TrieNode();
    }

    void insert(const  string& word) {
        TrieNode* node = root;
        size_t i = 0;

        while (i < word.size()) {
            char key = word[i];
            bool childExists = node->children.count(key);

            if (!childExists) {
                TrieNode* newNode = new TrieNode(word.substr(i));
                newNode->isEndOfWord = true;
                node->children[key] = newNode;
                break;
            }

            node = node->children[key];
            int prefixLen = commonPrefixLength(word.substr(i), node->prefix);
            i += prefixLen;

            if (prefixLen < node->prefix.size()) {
                TrieNode* newChild = new TrieNode(node->prefix.substr(prefixLen));
                newChild->isEndOfWord = node->isEndOfWord;
                newChild->children = node->children;

                node->prefix = node->prefix.substr(0, prefixLen);
                node->children.clear();
                node->children[newChild->prefix[0]] = newChild;

                node->isEndOfWord = (i == word.size());
            }
        }
    }

    bool search(const  string& word) {
        TrieNode* node = root;
        size_t i = 0;

        while (i < word.size()) {
            char key = word[i];
            if (!node->children.count(key)) {
                return false;
            }

            node = node->children[key];
            int prefixLen = commonPrefixLength(word.substr(i), node->prefix);
            if (prefixLen != node->prefix.size()) {
                return false;
            }

            i += prefixLen;
            if (i == word.size()) {
                return node->isEndOfWord;
            }
        }

        return false;
    }

     vector< string> recommendWords(const  string& prefix) {
        TrieNode* node = root;
        size_t i = 0;

        while (i < prefix.size()) {
            char key = prefix[i];
            if (!node->children.count(key)) {
                return {};
            }

            node = node->children[key];
            int prefixLen = commonPrefixLength(prefix.substr(i), node->prefix);
            if (prefixLen != node->prefix.size()) {
                return {};
            }

            i += prefixLen;
        }

         vector< string> results;
        findWords(node, prefix, results);
        return results;
    }
};

int main() {
    PatriciaTrie trie;
    int t;
    cin>>t;
    while(t--)
    {
        string s;
        cin>>s;
        trie.insert(s);
    }

     string prefix;
     cout << "vnesi prefix: ";
     cin >> prefix;

     vector< string> recommendations = trie.recommendWords(prefix);
    if (recommendations.empty()) {
         cout << "error 404 " << prefix << endl;
    } else {
         cout <<"rec:" << prefix << endl;
        for (const  string& word : recommendations) {
             cout << word << endl;
        }
    }

    return 0;
}
