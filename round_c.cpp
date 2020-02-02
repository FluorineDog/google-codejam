#include <algorithm>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <tuple>
#include <vector>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::make_tuple;
using std::map;
using std::pair;
using std::set;
using std::string;
using std::vector;

using ll = long long;

constexpr ll mod = 1000000007;
class Solution {
public:
    Solution() {
    }

    void gen_twos(ll max){
        if(twos.size() == 0){
            twos.push_back(1);
        }
        while(twos.size() <= max){
            ll acc = twos.back() * 2 % mod;
            twos.push_back(acc);
        }
    }
    void gen_facts(ll max){
        if(facts.size() == 0){
            facts.push_back(1);
        }
        while(facts.size() <= max){
            ll acc = facts.back() * (ll)facts.size() % mod;
            facts.push_back(acc);
        }
    }
    ll fact(ll i){
        return facts[i];
    }
    static ll power(ll base, ll exp){
        if(exp == 0){
            return 1;
        }
        else {
            ll next = power(base, exp / 2);
            next = next * next % mod;
            if(exp % 2) return base * next % mod;
            else return next;
        }
    }

    ll modinv(ll a){
        return power(a, mod - 2);
    }

    long long workload() {
        generate();
        gen_facts(N * 2);
        gen_twos(couple_count);
        ll up = 0;
        ll down = fact(couple_count);
        ll flag = 1;
        for(ll pair = 0; pair <= couple_count; ++pair){
            ll acc = fact(2 * N - pair) * modinv(fact(pair) * fact(couple_count - pair) % mod) % mod * twos[pair] % mod;
            up = (up + flag * acc + mod) % mod;
//            cerr << up * modinv(down) % mod << " ";
            flag *=-1;
        }
//        cerr << endl;
        return  up * down  % mod;
    }

private:
    void generate() {
        cin >> N >> couple_count;
    }

private:
    vector<ll> twos;
    vector<ll> facts;
private:
    ll couple_count, N;

};

int main() {

//    freopen("/home/mike/workspace/google-codejam/build/input.txt", "r", stdin);

    int N;
    cin >> N;
    Solution sol;
    for (int i = 0; i < N; ++i) {
        auto ans = sol.workload();
        cout << "Case #" << i + 1
             << ": "                 //
             //  << std::fixed << std::setprecision(6) //
             << ans << std::endl;    //
    }
}
