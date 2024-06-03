#ifndef POLAND_H
#define POLAND_H
#include <bits/stdc++.h>

using namespace std;

const long double eps = 0.00000001;

struct Stack {
    long double num;
    char zn;
    Stack *next;
};

void push(Stack *&t, long double x, char ch) {
    Stack *h = (Stack *) malloc(sizeof(Stack));
    (*h).zn = ch;
    (*h).num = x;
    (*h).next = t;
    t = h;
}

Stack pop(Stack *&t) {
    Stack h = *t;
    t = (*t).next;
    return h;
}

int prior(char ch) {
    if (ch == '(') {
        return 0;
    }
    if (ch == '+' || ch == '-') {
        return 1;
    }
    if (ch == '*' || ch == '/') {
        return 2;
    }
    if (ch == '^'){
        return 3;
    }
    return 4;
}

bool op(char ch) {
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^') {
        return true;
    } else {
        return false;
    }
}

bool prr(char ch) {
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == '(' || ch == ')') {
        return true;
    } else {
        return false;
    }
}

void apply(Stack *&t, char ch) {
    if(op(ch)) {
        long double b = (pop(t)).num;
        long double a = (pop(t)).num;
        if (ch == '+') push(t, a + b, '#');
        if (ch == '-') push(t, a - b, '#');
        if (ch == '*') push(t, a * b, '#');
        if (ch == '/') {
            if (b == 0.0) {
//                cout << "Error.";
                exit(0);
            } else {
                push(t, a / b, '#');
            }
        }
        if(ch == '^') {
            push(t, pow(a, b), '#');
        }
    }
    else{
        long double a = (pop(t)).num;
        if(ch == 'q') {
            if (a < 0.0) {
//                cout << "Error.";
                exit(0);
            }
            else{
                push(t, sqrt(a), '#');
            }
        }
        if(ch == 's'){
            push(t, sin(a), '#');
        }
        if(ch == 'c'){
            push(t, cos(a), '#');
        }
        if(ch == 't') {
            if (cos(a) == 0.0) {
//                cout << "Error.";
                exit(0);
            }
            else{
                push(t, sin(a) / cos(a), '#');
            }
        }
        if(ch == 'l'){
            if(a <= 0.0){
//                cout << "Error.";
                exit(0);
            }
            push(t, log(a), '#');
        }
        if(ch == 'a') {
            push(t, abs(a), '#');
        }
    }
}

bool f(char ch){
    if(ch == 'q' || ch == 's' || ch == 'c' || ch == 't' || ch == 'l'){
        return true;
    }
    else{
        return false;
    }
}

int err(string s) {
    int sz = s.size() - 1;
    if (op(s[0]) && s[0] != '-') {
        return 1;
    }
    if (op(s[sz])) {
        return 1;
    }
    int p = 0;
    for (auto i : s) {
        if (i == '(') {
            p++;
        }
        if (i == ')') {
            p--;
        }
        if (p < 0) {
            return 1;
        }
    }
    if (p != 0) {
        return 1;
    }
    for (int i = 0; i < sz; i++) {
        if (op(s[i]) && op(s[i + 1])) {
            return 1;
        }
    }
    for (int i = 0; i < sz; i++) {
        if (s[i] == '(' && op(s[i + 1]) && s[i + 1] != '-') {
            return 1;
        }
    }
    for (int i = 0; i < sz; i++) {
        if (s[i + 1] == ')' && op(s[i])) {
            return 1;
        }
    }
    for(int i = 0; i < sz; i++){
        if(f(s[i]) && f(s[i + 1])){
            return 1;
        }
    }
    for(int i = 0; i < sz; i++){
        if(f(s[i]) && s[i + 1] != '('){
            return 1;
        }
    }
    for(int i = 0; i < sz; i++){
        if(s[i] == '(' && s[i + 1] == ')'){
            return 1;
        }
    }
    return 0;
}


string iz(string s){
    string s1;
    for(int i = 0; i < s.size(); i++){
        if(s[i] >= 'a' && s[i] <= 'z'){
            if(s[i] == 's' && s[i + 1] == 'q' ){
                s1 += 'q';
            }
            if(s[i] == 's' && s[i + 1] == 'i'){
                s1 += 's';

            }
            if(s[i] == 'c' && s[i + 1] == 'o'){
                s1 += 'c';

            }
            if(s[i] == 't' && s[i + 1] == 'g'){
                s1 += 't';

}
            if(s[i] == 'l' && s[i + 1] == 'n'){
                s1 += 'l';
            }
            if(s[i] == 'a' && s[i + 1] == 'b') {
                s1 += 'a';
            }

        }
        else{
            if(s[i] == '-' && s[i - 1] == '('){
                s1 += "0-";
            }
            else{
                s1 += s[i];
            }
        }
    }
    return s1;
}

int check(string s){
    int d = 0;
    for (int i = 0; i < s.size(); i++) {
        if (d == 0) {
            if (!prr(s[i]) && !(s[i] >= '0' && s[i] <= '9')) {
                if (s[i] == 's' && s[i + 1] == 'i' && s[i + 2] == 'n') {
                    d = 2;
                    continue;
                }
                if (s[i] == 'c' && s[i + 1] == 'o' && s[i + 2] == 's') {
                    d = 2;
                    continue;
                }
                if (s[i] == 't' && s[i + 1] == 'g') {
                    d = 1;
                    continue;
                }
                if (s[i] == 'l' && s[i + 1] == 'n') {
                    d = 1;
                    continue;
                }
                if (s[i] == 's' && s[i + 1] == 'q' && s[i + 2] == 'r' && s[i + 3] == 't') {
                    d = 3;
                    continue;
                }
                if(s[i] == 'a' && s[i + 1] == 'b' && s[i + 2] == 's') {
                    d = 2;
                    continue;
                }
                return 1;
            }
        }
        if(d > 0){
            d--;
        }
    }
    return 0;
}

int pr;
long double n;

int mainP(string s) {
    if(check(s) == 1){
//        cout << "Error.";
        return 0;
    }
    s = '(' + s + ')';
    s = iz(s);
    if (err(s) == 1) {
//        cout << "Error.";
        return 0;
    }
    Stack *top1 = nullptr, *top2 = nullptr;
    char c;
    for (int i = 0; i < s.size(); i++) {
        c = s[i];
        if (c >= '0' && c <= '9') {
            n *= 10;
            n += (c - '0');
            pr = 1;
            continue;
        } else {
            if (pr == 1) {
                push(top1, n, '#');
            }
            n = 0;
            pr = 0;
        }
        if (c == '(') {
            push(top2, 0.0, c);
            continue;
        }
        if (c == ')') {
            char h = (pop(top2)).zn;
            while (h != '(') {
                apply(top1, h);
                h = (pop(top2)).zn;
            }
        } else {
            while (top2 != nullptr && prior(c) <= prior((*top2).zn)) {
                apply(top1, (pop(top2)).zn);
            }
            push(top2, 0.0, c);
        }
    }
    while (top2 != nullptr) {
        apply(top1, (pop(top2)).zn);
    }
//    cout << fixed << setprecision(6);
//    cout << (*top1).num;
    return (*top1).num;
}
#endif // POLAND_H
