#include<bits/stdc++.h>
using namespace std;

vector<int> nextGreaterRight(vector<int>& a) {
    int n = a.size();
    vector<int> right(n, -1);
    stack<int> st; // indices

    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.top()] < a[i]) {
            right[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
    return right;
}

vector<int> nextGreaterLeft(vector<int>& a) {
    int n = a.size();
    vector<int> left(n, -1);
    stack<int> st;

    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.top()] <= a[i]) {
            st.pop();
        }
        if (!st.empty()) left[i] = st.top();
        st.push(i);
    }
    return left;
}