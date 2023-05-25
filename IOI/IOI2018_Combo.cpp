#include "combo.h"
#include <bits/stdc++.h>
using namespace std;

string guess_sequence(int n) {
    char first;
    string s;
    int x = press("AB");
    if (x == 2) {
        s = "AB";
        first = 'A';
    } else if (x) {
        int y = press("A");
        if (y) first = 'A', s = "A";
        else first = 'B', s = "B";
    } else {
        int y = press("X");
        if (y) first = 'X', s = "X";
        else first = 'Y', s = "Y";
    }
    while (1) {
        if (s.size() == n) return s;
        else if (s.size() <= n - 2) {
            if (first == 'A') {
                string p = s + "BB" + s + "BX" + s + "BY" + s + "X";
                int y = press(p), sz = s.size();
                if (y == sz + 2) {
                    s.push_back('B');
                } else if (y == sz + 1) {
                    s.push_back('X');
                } else s.push_back('Y');
            } else if (first == 'B') {
                string p = s + "AA" + s + "AX" + s + "AY" + s + "X";
                int y = press(p), sz = s.size();
                if (y == sz + 2) {
                    s.push_back('A');
                } else if (y == sz + 1) {
                    s.push_back('X');
                } else s.push_back('Y');
            } else if (first == 'X') {
                string p = s + "BB" + s + "BA" + s + "BY" + s + "A";
                int y = press(p), sz = s.size();
                if (y == sz + 2) {
                    s.push_back('B');
                } else if (y == sz + 1) {
                    s.push_back('A');
                } else s.push_back('Y');
            } else {
                string p = s + "BB" + s + "BA" + s + "BX" + s + "A";
                int y = press(p), sz = s.size();
                if (y == sz + 2) {
                    s.push_back('B');
                } else if (y == sz + 1) {
                    s.push_back('A');
                } else s.push_back('X');
            }
        } else {
            if (first == 'A') {
                string p = s + "B" + s + "X";
                int y = press(p);
                if (y == n - 1) {
                    s.push_back('Y');
                } else {
                    p = s + "B";
                    y = press(p);
                    if (y == n - 1) {
                        s.push_back('X');
                    } else s.push_back('B');
                }
            } else if (first == 'B') {
                string p = s + "A" + s + "X";
                int y = press(p);
                if (y == n - 1) {
                    s.push_back('Y');
                } else {
                    p = s + "A";
                    y = press(p);
                    if (y == n - 1) {
                        s.push_back('X');
                    } else s.push_back('A');
                }

            } else if (first == 'X') {
                string p = s + "B" + s + "A";
                int y = press(p);
                if (y == n - 1) {
                    s.push_back('Y');
                } else {
                    p = s + "B";
                    y = press(p);
                    if (y == n - 1) {
                        s.push_back('A');
                    } else s.push_back('B');
                }
            } else {
                string p = s + "B" + s + "A";
                int y = press(p);
                if (y == n - 1) {
                    s.push_back('X');
                } else {
                    p = s + "B";
                    y = press(p);
                    if (y == n - 1) {
                        s.push_back('A');
                    } else s.push_back('B');
                }
            }
        }
    }
}
