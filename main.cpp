#include<bits/stdc++.h>
using namespace std;
template<class T>std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec){
    for (size_t i = 0; i < vec.size(); ++i) {os << vec[i];if (i != vec.size() - 1) {os << " ";}}return os;
}
class bigint {
public:
    int symbol = 1;
    std::vector<char> _a;
    int _maxsize = 0;

    int size() const { return _a.size(); }

    char &operator[](int i)
    {
        while(i>=_a.size())_a.push_back(0);
        return _a[i];
    }

    static bigint add(bigint A, bigint B) {
        if (A.size() < B.size())return add(B, A);
        std::vector<char> C;
        int t = 0;
        for (int i = 0; i < A.size(); i++) {
            t += A[i];
            if (i < B.size()) t += B[i];
            C.push_back(t % 10);
            t /= 10;
        }
        if (t) C.push_back(t);
        return bigint(C, A._maxsize);
    }

    void resize(int size) { _a.reserve(size); }

    friend bigint operator+(bigint A, bigint B)
    {
        if(A.symbol==-1&&B.symbol==-1)
        {
            auto t= add(A, B);
            t.symbol=-1;
            return t;
        }
        if(A.symbol==-1&&B.symbol==1)
        {
            return sub(B,A);
        }
        if(A.symbol==1&&B.symbol==-1)
        {
            return sub(A,B);
        }
        if(A.symbol==1&&B.symbol==1)
        {
            return add(A,B);
        }
    }

    friend bigint operator+(bigint A, int b) {
        bigint B(b);
        return add(A, B);
    }

    friend bigint operator+(int b, bigint A) {
        bigint B(b);
        return add(A, B);
    }

    static bigint sub(bigint A, bigint B) {
        A.symbol = 1, B.symbol = 1;
        if (A < B) {
            bigint a;
            a = sub(B, A);
            a.symbol = -1;
            return a;
        }
        std::vector<char> C;
        for (int i = 0, t = 0; i < A.size(); i++) {
            t = A[i] - t;
            if (i < B.size()) t -= B[i];
            C.push_back((t + 10) % 10);
            if (t < 0) t = 1; else t = 0;
        }
        while (C.size() > 1 && C.back() == 0) C.pop_back();
        return bigint(C, A._maxsize);
    }

    friend bigint operator-(bigint A, bigint B) {
        if (A.symbol == -1 && B.symbol == -1) { return sub(B, A); }
        if (A.symbol == 1 && B.symbol == -1) { return add(A, B); }
        if (A.symbol == -1 && B.symbol == 1) {
            bigint a = add(A, B);
            a.symbol = -1;
            return a;
        }
        if (A.symbol == 1 && B.symbol == 1) { return sub(A, B); }
    }

    static bigint smilemul(bigint &A, char b) {
        if(b==0)return bigint(0);
        if(b==1)return A;
        std::vector<char> C;
        int t = 0;
        for (int i = 0; i < A.size() || t; i++) {
            if (i < A.size()) t += A[i] * b;
            C.push_back(t % 10);
            t /= 10;
        }
        while (C.size() > 1 && C.back() == 0) C.pop_back();
        return bigint(C, A._maxsize);
    }
    static bigint mul(bigint A, bigint B) {
        //从a[]的最低位开始,每一位都乘以b[]的最低位
        int len1=A.size();
        int len2=B.size();
        char *a=new char[len1];
        char *b=new char[len2];
        long long *c=new long long[len1+len2+10];
        for(int i=0;i<len1+len2+9;i++)c[i]=0;
        for(int i=0;i<len1;i++)a[i]=A[i];
        for(int i=0;i<len1;i++)b[i]=B[i];
        for (int i = 0; i < len1; i++)
            for (int j = 0; j < len2; j++)
                c[i + j] += a[i] * b[j];
        //接下来处理进位
        int cnt = len1 + len2;
        long long t = 0;
        //因为i+j最小值为2,所以从下标2开始进位
        for (int i = 0; i <= cnt-2; i++) {
            t += c[i];
            c[i] = t % 10;
            t /= 10;
        }
        while (t) {
            c[++cnt] = t % 10;
            t /= 10;
        }
        while (cnt >= 1 && c[cnt] == 0) cnt--;
        vector<char>x;
        x.assign(c,c+cnt+1);
        bigint ans(x,int(x.size()*2));
        return ans;
    }
    friend bigint operator*(bigint A, bigint B) {
        if (A.symbol * B.symbol == 1)return mul(A, B);
        else {
            bigint t = mul(A, B);
            t.symbol = -1;
            return t;
        }
    }
    static bigint div(bigint A,bigint B)
    {
        if(A<B)return bigint(0,A._maxsize);

    }
    void init() { _a.reserve(_maxsize); }

    bigint(vector<char> c, int maxsize) : _maxsize(maxsize), _a(std::move(c)) { init(); }

    bigint(vector<char> c) : _maxsize(100), _a(std::move(c)) { init(); }

    bigint() {}

    bigint(int x, int maxsize) : _maxsize(maxsize) {
        init();
        string s = to_string(x);
        for (int i = s.size() - 1; i >= 0; i--)_a.push_back(s[i] - '0');
    }

    bigint(int x) {
        string s = to_string(x);
        _maxsize = min(int(s.size() * 2), 40);
        init();
        for (int i = s.size() - 1; i >= 0; i--)_a.push_back(s[i] - '0');
    }

    bigint operator=(int x) {
        _maxsize = 100;
        init();
        string s = to_string(x);
        if (s[0] == '-') {
            symbol = -1;
            for (int i = s.size() - 1; i >= 1; i--)_a.push_back(s[i] - '0');
        }
        else for (int i = s.size() - 1; i >= 0; i--)_a.push_back(s[i] - '0');
    }

    bigint operator=(long long x) {
        _maxsize = 100;
        init();
        string s = to_string(x);
        for (int i = s.size() - 1; i >= 0; i--)_a.push_back(s[i] - '0');
    }

    friend std::ostream &operator<<(std::ostream &os, bigint cc) {
        if (cc.symbol == -1 && !(cc._a.size() == 1 && cc[0] == 0))
            os << '-';
        for (int i = cc.size() - 1; i >= 0; i--)os << int(cc[i]);
        return os;
    }

    friend std::istream &operator>>(std::istream &is, bigint &cc) {
        std::string x;
        is >> x;
        if (cc._maxsize == 0)cc._maxsize = max(40, int(x.size() * 2));
        cc.init();
        if (x[0] == '-') {
            cc.symbol = -1;
            for (int i = x.size() - 1; i >= 1; i--)cc._a.push_back(x[i] - '0');
        }
        else for (int i = x.size() - 1; i >= 0; i--)cc._a.push_back(x[i] - '0');
        return is;
    }

    bool operator<(bigint other) {
        if (this->size() < other.size()||this->symbol==-1&&other.symbol==1&&!(*this==other))return 1;
        for (int i = this->size() - 1; i >= 0; i--) { if ((*this)[i] < other[i])return 1; }
        return 0;
    }

    bool operator==(bigint other) {
        if (other._a == this->_a&&other.symbol==this->symbol||(this->size()==1&&this->symbol==-1&&other.symbol==1&&other.size()==1&&(*this)[0]==0&&other[0]==0))return 1;
        return 0;
    }

    bool operator>(bigint other) {
        if (*this < other == 0 && (*this == other) == 0)return true;
        return false;
    }
    bigint operator-()
    {
        auto t=*this;
        t.symbol*=-1;
        return t;
    }
};

signed main()
{
    bigint a,b;
    std::cin>>a>>b;
    cout<<a*b;
}