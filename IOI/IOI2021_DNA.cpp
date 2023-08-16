#include "dna.h"

#include<bits/stdc++.h>

using namespace std;
 
vector<int> AC, AT, CA, CT, TA, TC;
 
void init(string a, string b){
    int n = a.size();
    AC = AT = CA = CT = TA = TC = vector<int> (n + 1);
    for(int i = 1; i <= n; i++) {
        AC[i] = AC[i - 1] + (a[i - 1] == 'A' && b[i - 1] == 'C');
        AT[i] = AT[i - 1] + (a[i - 1] == 'A' && b[i - 1] == 'T');
        CA[i] = CA[i - 1] + (a[i - 1] == 'C' && b[i - 1] == 'A');
        CT[i] = CT[i - 1] + (a[i - 1] == 'C' && b[i - 1] == 'T');
        TA[i] = TA[i - 1] + (a[i - 1] == 'T' && b[i - 1] == 'A');
        TC[i] = TC[i - 1] + (a[i - 1] == 'T' && b[i - 1] == 'C');
    }
}
 
int get_distance(int l, int r) {
    l++, r++;
    int ac = AC[r] - AC[l - 1], at = AT[r] - AT[l - 1], ca = CA[r] - CA[l - 1], ct = CT[r] - CT[l - 1], ta = TA[r] - TA[l - 1], tc = TC[r] - TC[l - 1];
    int x = min(ac, ca), y = min(at, ta), z = min(ct, tc);
    ac -= x, ca -= x, at -= y, ta -= y, ct -= z, tc -= z;
    if (ac == ta && ac == ct && at == tc && ca == tc) return x + y + z + ac + ca + at + ta;
    return -1;
}
