#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <vector>
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::tuple;
using std::vector;
using ll = long long;
int check(tuple<int, int> rule, int prefix) {
    auto [len, count] = rule;
    auto old_count = __builtin_popcount(prefix & ((1 << len) - 1));
    return count - old_count;
}

constexpr int max_diff = 8;
constexpr int max_diff_count = 1 << max_diff;
constexpr int MASK = max_diff_count - 1;
ll counter(string preload, int str_len, map<int, vector<tuple<int, int>>>& constraints) {
    vector<ll> record(max_diff_count, 0);
    vector<ll> new_record(max_diff_count, 0);
    int checkpoint = preload.size();
    if(preload.size() > max_diff) {
        preload = preload.substr(preload.size() - max_diff, max_diff);
    }
    int init_substr = 0;
    for(auto ch : preload) {
        if(ch == '1') {
            init_substr = 2 * init_substr + 1;
        } else {
            init_substr = 2 * init_substr + 0;
        }
    }

    for(auto rule : constraints[checkpoint]) {
        if(check(rule, init_substr) != 0) {
            cerr << "@";
            return 0;
        }
    }

    init_substr = MASK & (init_substr << 1);
    ++checkpoint;

    record[init_substr] = 1;
    for(; checkpoint < str_len; checkpoint++) {
        new_record.clear();
        new_record.resize(max_diff_count, 0);
        for(int substr = 0; substr < max_diff_count; substr++) {
            bool flag_1 = true;
            bool flag_0 = true;
            for(auto rule : constraints[checkpoint]) {
                int digit = check(rule, substr);
                flag_1 = flag_1 && digit == 1;
                flag_0 = flag_0 && digit == 0;
            }
            if(flag_1) {
                new_record[MASK & ((substr << 1) | 1)] += record[substr];
            }
            if(flag_0) {
                new_record[MASK & (substr << 1) | 0] += record[substr];
            }
        }
        new_record.swap(record);
    }
    ll sum = 0;
    for(int i = 0; i < max_diff_count; ++i) {
        sum += record[i];
    }
    return sum;
}

string shortcut(int n, map<int, vector<tuple<int, int>>>& limit, int rank) {
    string str(n, ' ');
    for(auto [k, vs] : limit) {
        for(auto [_, c] : vs) {
            str[k] = c + '0';
        }
    }
    for(int i = str.size(); i-- > 0; ) {
        if(str[i] != ' ') {
            continue;
        } else {
        }
        str[i] = '0' + (rank % 2);
        rank >>= 1;
    }
    return str;
}

string workload() {
    int str_len, constraint_count;
    ll rank;
    cin >> str_len >> constraint_count >> rank;
    rank--;
    ll raw_rank = rank;
    map<int, vector<tuple<int, int>>> limits;
    for(int i = 0; i < constraint_count; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        limits[b - 1].emplace_back(b - a, c);
    }
    string prefix = "";
    int sum = 0;
    for(int i = 0; i < str_len; ++i) {
        ll count = counter(prefix, str_len, limits);
        cerr << i << "  %%" << rank << "$" << count << "#" << prefix << endl;
        if(rank >= count) {
            prefix += "1";
            rank -= count;
        } else {
            prefix += "0";
        }
    }
    prefix = shortcut(str_len, limits, raw_rank);
    return prefix;
}

int main() {
    // freopen("build/input.txt",  "r", stdin);
    int N;
    cin >> N;
    for(int i = 0; i < N; ++i) {
        auto ans = workload();
        cerr << "checking case" << i << endl;
        cout << "Case #" << i + 1 << ": " << std::fixed << std::setprecision(6) << ans
             << std::endl;
    }
}
