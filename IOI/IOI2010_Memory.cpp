#include "grader.h"
#include "memory.h"
#include <bits/stdc++.h>
using namespace std;

void play() {
    map<char, vector<int>> mp;
    for (int i = 1; i <= 50; i++) mp[faceup(i)].push_back(i);
    for (char x = 'A'; x < 'Z' ; x++) {
        faceup(mp[x][0]);
        faceup(mp[x][1]);
    }
}
