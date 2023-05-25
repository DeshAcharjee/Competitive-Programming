#include <bits/stdc++.h>
using namespace std;

struct node {
    node* c[26] = {NULL};
    bool endofword;
    int sz, f;
    node(bool x) : endofword(x), f(-1), sz(-1) { };
};

vector<char> ans;

struct trie {
    node* root;
    trie() : root(NULL) { };
    void insert(node* &u, int id, string &s) {
        if (u == NULL) u = new node(false);
        if (id == s.size()) {
            u->endofword = true;
            return;
        }
        if (u->sz < (int) s.size() - id) u->sz = s.size() - id, u->f = s[id] - 'a';
        insert(u->c[s[id] - 'a'], id + 1, s);
    }
    void dfs(node* u) {
        if (u->endofword) ans.push_back('P');
        for (int i = 0; i < 26; i++)
            if (u->c[i] != NULL && i != u->f) {
                ans.push_back('a' + i);
                dfs(u->c[i]);
            }
        if (u->f != -1) ans.push_back('a' + u->f), dfs(u->c[u->f]);
        ans.push_back('-');
    }
    void insert(string s) {
        insert(root, 0, s);
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    trie tr;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        tr.insert(s);
    }
    tr.dfs(tr.root);
    while (ans.back() == '-') ans.pop_back();
    cout << ans.size() << '\n';
    for (char c : ans) cout << c << '\n';
}
