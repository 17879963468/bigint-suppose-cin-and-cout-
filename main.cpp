#include<bits/stdc++.h>
using namespace std;
#include <bits/stdc++.h>
using namespace std;

class bigint {
#define VC vector<char>
#define pb push_back
#define bt bigint
#define f(i, a, b) for(int i=(a);i<=(b);++i)
#define rf(i, a, b) for(int i=(a);i>=(b);--i)
public:
    int symbol = 1;
    std::VC _a;

    int size() const { return _a.size(); }

    char &operator[](int i) { return _a[i]; }

    static bt add(bt A, bt B) {
        if (A.size() < B.size())return add(B, A);
        std::VC C;
        int t = 0;
        f(i, 0, A.size() - 1) {
            t += A[i];
            if (i < B.size()) t += B[i];
            C.pb(t % 10);
            t /= 10;
        }
        if (t) C.pb(t);
        return {C};
    }
    void resize(int size) { _a.reserve(size); }

    static bigint plu(bigint A, bigint B) {
        if (A.symbol == -1 && B.symbol == -1) {
            auto t = add(A, B);
            t.symbol = -1;
            return t;
        }
        if (A.symbol == -1 && B.symbol == 1) { return sub(B, A); }
        if (A.symbol == 1 && B.symbol == -1) { return sub(A, B); }
        return add(A, B);
    }

    template<class T,class Y>
    friend bt operator+(T A, Y B) { return plu(A, B); }

    static bt sub(bt A, bt B) {
        A.symbol = 1, B.symbol = 1;
        std::VC C;
        if (A < B) {
            bt a;
            a = sub(B, A);
            a.symbol = -1;
            return a;
        }
        int t = 0;
        f(i, 0, A.size() - 1) {
            t = A[i] - t;
            if (i < B.size()) t -= B[i];
            C.pb((t + 10) % 10);
            if (t < 0) t = 1; else t = 0;
        }
        while (C.size() > 1 && C.back() == 0) C.pop_back();
        return bigint(C);
    }

    static bt SUB(bt A, bt B) {
        if (A.symbol == -1 && B.symbol == -1) {
            bigint t;
            t = sub(A, B);
            t.symbol *= -1;
            return t;
        }

        if (A.symbol == 1 && B.symbol == -1) { return add(A, B); }
        if (A.symbol == -1 && B.symbol == 1) {
            bigint a = add(A, B);
            a.symbol = -1;
            return a;
        }

        return sub(A, B);
    }

    template<class T,class Y>
    friend bt operator-(T A, Y B) { return SUB(A, B); }

    static bt smilemul(bt &A, char b) {
        if (b == 0)return bt(0);
        if (b == 1)return A;
        std::VC C;
        int t = 0;
        for (int i = 0; i < A.size() || t; i++) {
            if (i < A.size()) t += A[i] * b;
            C.pb(t % 10);
            t /= 10;
        }
        while (C.size() > 1 && C.back() == 0) C.pop_back();
        return {C};
    }

    static bigint mul(bt A, bt B) {
        int len1 = A.size(), len2 = B.size(), cnt = len1 + len2;
        VC x;
        long long *c = new long long[len1 + len2 + 10], t = 0;
        f(i, 0, len1 + len2 + 8)c[i] = 0;
        f(i, 0, len1 - 1)f(j, 0, len2 - 1)c[i + j] += A[i] * B[j];
        f(i, 0, cnt - 1) {
            t += c[i];
            c[i] = t % 10;
            t /= 10;
        }
        while (t) {
            c[++cnt] = t % 10;
            t /= 10;
        }
        while (cnt >= 1 && c[cnt] == 0) cnt--;
        x.assign(c, c + cnt + 1);
        bigint ans(x, x.size() * 2);
        delete[] c;
        return {x, int(x.size() * 2)};
    }

    friend bigint MUL(bt A, bt B) {
        if (A.symbol * B.symbol == 1)return mul(A, B);
        else {
            bt t = mul(A, B);
            t.symbol = -1;
            return t;
        }
    }

    template<class T,class Y>
    friend bt operator*(T A, Y B) { return MUL(A, B); }

    static bigint smilediv(bt A, int b) {
        char *cha = new char[A.size()], *ans = new char[A.size()];
        int l = A.size(), m = l - 1, x = 0;
        std::copy(A._a.begin(), A._a.end(), cha);
        rf(i, l - 1, 0) {
            ans[i] = (x * 10 + cha[i]) / b;
            x = (cha[i] + x * 10) % b;
        }
        while (!ans[m] && m >= 1)m--;
        bigint z(0);
        z._a.assign(ans, ans + m + 1);
        delete []cha;
        delete[]ans;
        return z;
    }

    static bigint div(bt A, bt B) {
        if (A < B)return {0};
        bt l = 1, r = A;
        while (l <= r) {
            if(r.symbol==-1)exit(1);
            bt mid = smilediv(l + r, 2);
            if (A < mid * B)r = mid - 1;
            else l = mid + 1;
        }
        return r;
    }

    friend bigint DIV(bt A, bt B) {
        bt t = div(A, B);
        if (A.symbol * B.symbol == -1)t.symbol = -1;
        return t;
    }

    template<class T,class Y>
    friend bt operator/(T A, Y B) { return DIV(A, B); }

    static bigint mod(bt A, bt B) {
        bt x = A / B;
        return A - x * B;
    }

    friend bigint MOD(bt A, bt B) { return mod(mod(A, B) + B, B); }

    template<class T,class Y>
    friend bt operator%(T A, Y B) { return MOD(A, B); }


    bigint(VC c, int maxsize) : _a(std::move(c)) {  }

    bigint(VC c) :_a(std::move(c)) { }

    bigint() { _a.assign({0}); }

    template<class T>
    bigint(T z, int maxsize)  {
        _a.clear();
        unsigned long long x = z;
        string s = to_string(x);
        if (s[0] != '-')rf(i, s.size() - 1, 0)_a.pb(s[i] - '0');
        else {
            rf(i, s.size() - 1, 1)_a.pb(s[i] - '0');
            symbol = -1;
        }
    }

    template<class T>
    bigint(T z) {
        _a.clear();
        string s;
        if (typeid(z) != typeid(const char *) && typeid(z) != typeid(string))s = to_string((long long) z); else s = z;
        if (s[0] != '-') { rf(i, s.size() - 1, 0)_a.pb(s[i] - '0'); }
        else {
            rf(i, s.size() - 1, 1)_a.pb(s[i] - '0');
            symbol = -1;
        }
    }

    friend std::ostream &operator<<(std::ostream &os, bt cc) {
        if (cc.symbol == -1 && !(cc._a.size() == 1 && cc[0] == 0))os << '-';
        rf(i, cc.size() - 1, 0)os << int(cc[i]);
        return os;
    }

    friend std::istream &operator>>(std::istream &is, bt &cc) {
        cc._a.clear();
        std::string x;
        is >> x;
        if (x[0] == '-') {
            cc.symbol = -1;
            rf(i, x.size() - 1, 1)cc._a.pb(x[i] - '0');
        }
        else
            rf(i, x.size() - 1, 0)cc._a.pb(x[i] - '0');
        return is;
    }

    template<class T>
    bool operator<(T A) {
        bigint other = A;
        if (this->symbol == -1 && other.symbol == 1 && !(*(this) == other))return 1;
        if (this->size() < other.size())return 1;
        else if (this->size() > other.size())return 0;
        else if (this->size() == other.size())rf(i, this->size() - 1, 0) { if ((*this)[i] < other[i])return 1; }
        return 0;
    }
    bool operator<(bigint A) {
        bigint other = A;
        if (this->symbol == -1 && other.symbol == 1 && !(*(this) == other))return 1;
        if (this->size() < other.size())return 1;;
       if (this->size() > other.size())return 0;
        if (this->size() == other.size())rf(i, this->size() - 1, 0) { if ((*this)[i] < other[i])return 1;else if((*this)[i] > other[i])return 0; }
        return 0;
    }
    template<class T>
    bool operator==(T A) {
        bigint other(A);
        if (other._a == this->_a && other.symbol == this->symbol ||
            (this->size() == 1 && this->symbol == -1 && other.symbol == 1 && other.size() == 1 && (*this)[0] == 0 &&other[0] == 0))return 1;
        return 0;
    }

    template<class T>
    bool operator>(T A) {
        bigint other(A);
        if (*this < other == 0 && (*this == other) == 0)return true;
        return false;
    }

    template<class T>
    bool operator<=(T A) {
        bigint other(A);
        if (*(this) < other || *this == other)return 1;
        return 0;
    }

    template<class T>
    bool operator>=(T A) {
        bigint other(A);
        if (*(this) > other || *this == other)return 1;
        return 0;
    }

    bigint operator-() {
        auto t = *this;
        t.symbol *= -1;
        return t;
    }

    bigint operator+=(bt other) {
        *this = *this + other;
        return *this;
    }

    bigint operator-=(bt other) {
        *this = *this - other;
        return *this;
    }

    bigint operator*=(bt other) {
        *this = *this * other;
        return *this;
    }

    bigint operator/=(bt other) {
        *this = *this / other;
        return *this;
    }

    bigint operator%=(bt other) {
        *this = *this % other;
        return *this;
    }

    bigint operator++(int) {
        bt t = *this;
        *this = *this + 1;
        return t;
    }

    bigint operator++() {
        *this = *this + 1;
        return *this;
    }

    operator int() const {
        int t = 0;
        for (int i = _a.size() - 1; i >= 0; i--) { t = t * 10 + _a[i]; }
        return t;
    }
};
#define int bigint
int ans = 1, mod = 1e9 + 7;
string s;
signed main()
{
    bigint n,m,mod;
    n=1530837320,m= 5120960151,mod= 9;
    cin>>n>>m>>mod;

    cout<<(n*m)%mod;
}

