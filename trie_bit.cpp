#include<bits/stdc++.h>
using namespace std;

struct Trie
{
    static const int B = 31;
    struct Node
    {
        Node*nxt[2];
        int sz;
        Node()
        {
            nxt[0] = nxt[1] = NULL;
            sz = 0;
        }
    };

    Node *root;

    Trie()
    {
        root = new Node();
    }

    void insert(int val)
    {
        Node* cur = root;
        cur->sz++;
        for (int i = B - 1; i >= 0; i--)
        {
            int b = (1<<i) & val ? 1 : 0;
            if (cur->nxt[b] == NULL) cur->nxt[b] = new Node();
            cur = cur->nxt[b];
            cur->sz++;
        }
    }

    int query(int x, int k) // number of values s.t. val ^ x < k
    {
        Node* cur = root;
        int ans = 0;
        for (int i = B - 1; i >= 0; i--)
        {
            if (cur == NULL) break;
            int b1 = (1<<i) & x ? 1 : 0, b2 = (1<<i) & k ? 1 : 0;
            if (b2 == 1)
            {
                if (cur->nxt[b1]) ans += cur->nxt[b1]->sz;
                cur = cur->nxt[!b1];
            }
            else cur = cur->nxt[b1];
        }
        return ans;
    }

    int get_max(int x) // returns maximum of val ^ x
    {
        Node* cur = root;
        int ans = 0;
        for (int i = B - 1; i >= 0; i--)
        {
            int k = (1<<i) & x ? 1 : 0;
            if (cur->nxt[!k]) cur = cur->nxt[!k], ans <<= 1, ans++;
            else cur = cur->nxt[k], ans <<= 1;
        }
        return ans;
    }

    int get_min(int x) // returns minimum of val ^ x
    {
        Node* cur = root;
        int ans = 0;
        for (int i = B - 1; i >= 0; i--)
        {
            int k = (1<<i) & x ? 1 : 0;
            if (cur->nxt[k]) cur = cur->nxt[k], ans <<= 1;
            else cur = cur->nxt[!k], ans <<= 1, ans++;
        }
        return ans;
    }

    void del(Node* cur)
    {
        for (int i = 0; i < 2; i++) if (cur->nxt[i]) del(cur->nxt[i]);
        delete(cur);
    }
};