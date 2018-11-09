#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <tuple>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::make_tuple;
using std::set;
using std::string;
using std::vector;

using ll = long long;

string get_seq() {
    char ch2, ch1;
    int N;
    ll A, B, C, D;
    auto gen_next = [&](ll x1, ll x2) { return (A * x1 + B * x2 + C) % D; };
    ll x2, x1;
    string str;
    cin >> ch2 >> ch1;
    cin >> N;
    cin >> A >> B >> C >> D;
    x2 = (ll)ch2;
    x1 = (ll)ch1;
    str += x2;
    str += x1;
    for(int i = 2; i < N; ++i) {
        int next = gen_next(x1, x2);
        std::tie(x2, x1) = make_tuple(x1, next);
        str += (char)(97 + next % 26);
    }
    return str;
}

auto create_prefix(const string& seq) {
    int N = seq.size();
    vector<vector<int>> prefix(26, vector<int>(N + 1));
    vector<vector<int>> container(26);
    for(int i = 0; i < 26; ++i) {
        prefix[i][0] = 0;
    }

    for(int loc = 0; loc < N; ++loc) {
        for(int i = 0; i < 26; ++i) {
            prefix[i][loc + 1] = prefix[i][loc];
        }
        int cur = seq[loc] - 'a';
        prefix[cur][loc + 1] += 1;
        container[cur].push_back(loc);
    }
    // int ch = 0;
    // for(auto& vec : prefix) {
    //     for(auto x : vec) {
    //         cout << x;
    //     }
    //     cout << "--" << ch++ << endl;
    // }
    // ch = 0;
    // for(auto& vec: container){
    //     for(auto x : vec) {
    //         cout << x << ":";
    //     }
    //     cout << "--" << ch << char(ch + 97) << endl;
    //     ch++;
    // }
    return make_tuple(std::move(prefix), std::move(container));
}

long long workload() {
    int str_count;
    cin >> str_count;
    vector<string> strs(str_count);
    for(auto& str : strs) {
        cin >> str;
    }
    auto seq = get_seq();
    auto [prefix, container] = create_prefix(seq);
    int N = seq.size();
    auto range_reduce = [&](int cur, int begin, int end) {
        return prefix[cur][end] - prefix[cur][begin];
    };
    int total_valid = 0;
    for(const auto& str : strs) {
        int L = str.size();
        int char_table[26] = {};
        for(auto x : str) {
            char_table[x - 'a']++;
        }
        int cur_first = str[0] - 'a';
        int cur_last = str[L - 1] - 'a';
        for(auto beg_loc : container[cur_first]) {
            int end_loc = beg_loc + L;
            if(end_loc > N) {
                continue;
            }
            if(seq[end_loc - 1] - 'a' != cur_last) {
                continue;
            }
            if(str.size() < 26) {
                for(int i = 1; i < str.size() - 1; ++i) {
                    int cur = str[i] - 'a';
                    if(range_reduce(cur, beg_loc, end_loc) != char_table[cur]) {
                        goto failed;
                    }
                }
            } else {
                for(int cur = 0; cur < 26; ++cur) {
                    if(range_reduce(cur, beg_loc, end_loc) != char_table[cur]) {
                        goto failed;
                    }
                }
            }
            ++total_valid;
            break;
            // cout << str               //
            //      << ":" << beg_loc    //
            //      << ":" << end_loc;
        failed:;
        }
    }
    // cout << seq;
    return total_valid;
}

int main() {
    // freopen("build/input.txt",  "r", stdin);
    int N;
    cin >> N;
    for(int i = 0; i < N; ++i) {
        auto ans = workload();
        cout << "Case #" << i + 1
             << ": "                 //
                                     //  << std::fixed << std::setprecision(6) //
             << ans << std::endl;    //
    }
}
