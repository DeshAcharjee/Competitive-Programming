#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 1e6;
int L[20 * N], R[20 * N], t;
char s[20 * N];

void upd(int &v, int l, int r, const int &x, const char &z) {
    ++t;
    L[t] = L[v];
    R[t] = R[v];
    v = t;
    if (l == r) {
        s[v] = z;
        return;
    }
    int m = l + r >> 1;
    if (x <= m) upd(L[v], l, m, x, z);
    else upd(R[v], m + 1, r, x, z);
}
 
char qry(int v, int l, int r, const int &x) {
    if (l == r) return s[v];
    int m = l + r >> 1;
    return x <= m ? qry(L[v], l, m, x) : qry(R[v], m + 1, r, x);
}

vector<pair<int, int>> st;

void Init() {
    st.push_back({0, 0});
}

void TypeLetter(char L) {
    st.push_back(st.back());
    upd(st.back().first, 0, N - 1, st.back().second++, L);
}

void UndoCommands(int U) {
    st.push_back(st[st.size() - U - 1]);
}

char GetLetter(int P) {
    return qry(st.back().first, 0, N - 1, P);
}
