#include<bits/stdc++.h>
using namespace std;

struct NG2 {
    vector<int> l1, l2, r1, r2;

    NG2(vector<int>& a) {
        int n = a.size();
        l1.assign(n, -1);
        l2.assign(n, -1);
        r1.assign(n, -1);
        r2.assign(n, -1);

        {
            stack<int> st1, st2;

            for (int i = 0; i < n; i++) {

                while (!st2.empty() && a[st2.top()] < a[i]) {
                    r2[st2.top()] = i;
                    st2.pop();
                }

                vector<int> temp;
                while (!st1.empty() && a[st1.top()] < a[i]) {
                    r1[st1.top()] = i;
                    temp.push_back(st1.top());
                    st1.pop();
                }

                for (int j = (int)temp.size() - 1; j >= 0; j--) {
                    st2.push(temp[j]);
                }

                st1.push(i);
            }
        }

        {
            stack<int> st1, st2;

            for (int i = n - 1; i >= 0; i--) {

                while (!st2.empty() && a[st2.top()] < a[i]) {
                    l2[st2.top()] = i;
                    st2.pop();
                }

                vector<int> temp;
                while (!st1.empty() && a[st1.top()] < a[i]) {
                    l1[st1.top()] = i;
                    temp.push_back(st1.top());
                    st1.pop();
                }

                for (int j = (int)temp.size() - 1; j >= 0; j--) {
                    st2.push(temp[j]);
                }

                st1.push(i);
            }
        }
    }
};