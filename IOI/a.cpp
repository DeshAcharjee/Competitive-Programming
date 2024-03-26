#include "supertrees.h"
#include <bits/stdc++.h>
 
using namespace std;
 
int construct(vector<vector<int>> p) {
    int n = p.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i][j] == 3) {
                return 0;
            }
        }
    }
    vector<bool> vis(n);
    vector<vector<int>> b(n, vector<int> (n));
    for (int i = 0; i < n; i++) {
        if (vis[i]) continue;
        queue<int> q;
        q.push(i);
        vector<int> nodes;
        while (q.size()) {
            int u = q.front();
            q.pop();
            if (vis[u]) continue;
            vis[u] = 1;
            nodes.push_back(u);
            for (int j = 0; j < n; j++) {
                if (!vis[j] && p[u][j]) {
                    q.push(j);
                }
            }
        }
        bool two = 0;
        for (int i = 0; i < nodes.size(); i++) {
            for (int j = i + 1; j < nodes.size(); j++) {
                if (!p[nodes[i]][nodes[j]]) {
                    return 0;
                }
                if (p[nodes[i]][nodes[j]] == 2) {
                    two = 1;
                }
            }
        }
        vector<vector<int>> trees;
        vector<bool> vis2(n);
        for (int u : nodes) {
            if (vis2[u]) continue;
            trees.push_back({});
            queue<int> q2;
            q2.push(u);
            while (q2.size()) {
                int v = q2.front();
                q2.pop();
                if (vis2[v]) continue;
                vis2[v] = 1;
                trees.back().push_back(v);
                for (int j = 0; j < n; j++) {
                    if (!vis2[j] && p[v][j] == 1) {
                        q2.push(j);
                    }
                }
            }
        }
        int sz = trees.size();
        if (two && sz < 3) return 0;
        for (int j = 0; j < sz; j++) {
            for (int k = 0; k < trees[j].size(); k++) {
                for (int l = k + 1; l < trees[j].size(); l++) {
                    if (p[trees[j][k]][trees[j][l]] != 1) {
                        return 0;
                    }
                }
            }
        }
        for (int j = 0; j < sz; j++) {
            int u = trees[j].back(), v = trees[(j + 1) % sz].back();
            if (u != v) {
                b[u][v] = b[v][u] = 1;
            }
            for (int k = 0; k < trees[j].size() - 1; k++) {
                u = trees[j][k], v = trees[j][k + 1];
                b[u][v] = b[v][u] = 1;
            }
        }
    }
    build(b);
    return 1;
}