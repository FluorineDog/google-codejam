#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::make_tuple;

using ll = long long;


string get_seq(){
    char ch2, ch1;
    int N;
    ll A, B, C, D;
    auto gen_next = [&](ll x1, ll x2) {
        return (A * x1 + B * x2 + C) % D;
    };
    ll x2,  x1;
    string str;
    cin >> ch2 >> ch1;
    cin >> N;
    cin >> A >> B >> C >> D;
    x2 = (ll)ch2;
    x1 = (ll)ch1;
    str += x2;
    str += x1;
    for(int i = 2; i < N; ++i){
        int next = gen_next(x1, x2);
        std::tie(x2, x1) = make_tuple(x1, next);
        str += (char)(97 + next % 26);
    }
    return str;
}

long long workload() {
    int str_count;
    cin >> str_count;
    vector<string> strs(str_count);
    for(auto &str: strs) {
        cin >> str;
    }
    auto seq = get_seq();
    cout << seq;
    return 0; 
}

int main() {
    // freopen("build/input.txt",  "r", stdin);
    int N;
    cin >> N;
    for(int i = 0; i < N; ++i) {
        auto ans = workload();
        cout << "Case #" << i + 1
             << ": "    //
            //  << std::fixed << std::setprecision(6) //
             << ans << std::endl;    //
    }
}
