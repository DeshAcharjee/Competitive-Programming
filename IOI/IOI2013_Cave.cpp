#include "cave.h"
#include <bits/stdc++.h>
using namespace std;

void exploreCave(int n) {
    int v[n], d[n];
    for (int i = 0; i < n; i++) v[i] = d[i] = -1;
    int f = 0;
    while (f != n) {
        int l = 0, r = n - 1;
        int s[n];
        for (int i = 0; i < n; i++) {
            if (d[i] != -1) s[i] = v[i];
            else s[i] = 0;
        }
        int x = tryCombination(s), to_check;
        if (x > f || x == -1) to_check = 0;
        else to_check = 1;
        for (int i = 0; i < n; i++)
            if (d[i] == -1) s[i] = to_check;
        while (l < r) {
            int m = l + r >> 1;
            for (int i = l; i <= m; i++)
                if (d[i] == -1) s[i] ^= 1;
            x = tryCombination(s);
            if (x <= f && x != -1) {
                for (int i = l; i <= m; i++)
                    if (d[i] == -1) s[i] ^= 1;
                r = m;
            } else l = m + 1;
        }
        v[l] = to_check, d[l] = f++;
    }
    answer(v, d);
}
