#include <bits/stdc++.h>
using namespace std;

struct Trie {
    static const int ALPH = 26; // lowercase letters a-z
    struct Node {
        Node* nxt[ALPH];
        int sz;        // number of strings passing through this node
        int ends_here; // number of strings ending at this node
        Node() {
            fill(nxt, nxt + ALPH, nullptr);
            sz = ends_here = 0;
        }
    };

    Node* root;

    Trie() {
        root = new Node();
    }

    // Insert a string into trie
    void insert(const string& s) {
        Node* cur = root;
        cur->sz++;
        for (char c : s) {
            int idx = c - 'a';
            if (!cur->nxt[idx]) cur->nxt[idx] = new Node();
            cur = cur->nxt[idx];
            cur->sz++;
        }
        cur->ends_here++;
    }

    // Count exact occurrences of a string
    int search(const string& s) {
        Node* cur = root;
        for (char c : s) {
            int idx = c - 'a';
            if (!cur->nxt[idx]) return 0;
            cur = cur->nxt[idx];
        }
        return cur->ends_here;
    }

    // Count number of strings with given prefix
    int count_prefix(const string& prefix) {
        Node* cur = root;
        for (char c : prefix) {
            int idx = c - 'a';
            if (!cur->nxt[idx]) return 0;
            cur = cur->nxt[idx];
        }
        return cur->sz;
    }

    // Erase a string (assumes it exists)
    void erase(const string& s) {
        Node* cur = root;
        cur->sz--;
        for (char c : s) {
            int idx = c - 'a';
            cur = cur->nxt[idx];
            cur->sz--;
        }
        cur->ends_here--;
    }

    // Find lexicographically smallest string XOR-like analog: here just smallest in trie
    string get_min() {
        string ans;
        Node* cur = root;
        while (cur) {
            bool found = false;
            for (int i = 0; i < ALPH; i++) {
                if (cur->nxt[i] && cur->nxt[i]->sz > 0) {
                    ans += char('a' + i);
                    cur = cur->nxt[i];
                    found = true;
                    break;
                }
            }
            if (!found) break;
        }
        return ans;
    }

    // Find lexicographically largest string
    string get_max() {
        string ans;
        Node* cur = root;
        while (cur) {
            bool found = false;
            for (int i = ALPH - 1; i >= 0; i--) {
                if (cur->nxt[i] && cur->nxt[i]->sz > 0) {
                    ans += char('a' + i);
                    cur = cur->nxt[i];
                    found = true;
                    break;
                }
            }
            if (!found) break;
        }
        return ans;
    }

    // Delete all nodes (destructor)
    void del(Node* cur) {
        for (int i = 0; i < ALPH; i++) if (cur->nxt[i]) del(cur->nxt[i]);
        delete cur;
    }

    ~Trie() {
        del(root);
    }
};

int main() {
    Trie t;
    t.insert("apple");
    t.insert("app");
    t.insert("bat");

    cout << t.search("app") << "\n";       // 1
    cout << t.count_prefix("ap") << "\n";  // 2
    t.erase("app");
    cout << t.search("app") << "\n";       // 0
    cout << t.get_min() << "\n";           // "apple"
    cout << t.get_max() << "\n";           // "bat"
}