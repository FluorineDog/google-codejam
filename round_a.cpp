#include <iostream>
#include <map>
#include <string>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::make_pair;
using std::map;
using std::pair;
using std::string;
using std::vector;
// record is to represent
// N-digit number that satify the requirement
using ll = long long;
ll record[20][9] = {0};

void init() {
    for(int i = 0; i < 9; ++i) {
        record[0][0] = 0;
    }
    record[0][0] = 1;
    for(int i = 1; i < 20; ++i) {
        for(int digit = 0; digit < 9; ++digit) {
            for(int mod = 0; mod < 9; ++mod) {
                record[i][(mod + digit) % 9] += record[i - 1][mod];
            }
        }
    }
    // for(int i = 0; i < 20; ++i){
    //     for(int j = 0; j < 9; ++j){
    //         cout << record[i][j] << " ";
    //     }
    //     cout << endl;
    // }
}

long long count(ll limit_num) {
    if(limit_num == 0 || limit_num == 1) {
        return 0;
    }
    auto limit = std::to_string(limit_num);
    int N = limit.size();
    ll total_count = 0;
    int prefix_sum = 0;
    // cout << "$" <<limit << endl;
    for(int prefix_len = 0; prefix_len < N; ++prefix_len) {
        int cur_digit = limit[prefix_len] - '0';
        for(int digit = 0; digit < cur_digit; ++digit) {
            for(int mod = 0; mod < 9; ++mod) {
                if((mod + prefix_sum + digit) % 9 == 0) continue;
                // cout << "<"  << N - 1 - prefix_len << "," << mod << ">";
                total_count += record[N - 1 - prefix_len][mod];
            }
        }
        prefix_sum += cur_digit;
    }
    return total_count;
}

long long workload() {
    ll left, right;
    cin >> left >> right;
    return count(right + 1) - count(left);
}

int main() {
    // freopen("input.txt", "r", stdin);
    int N;
    cin >> N;
    init();
    for(int i = 0; i < N; ++i) {
        auto ans = workload();
        cout << "Case #" << i + 1 << ": " << ans << std::endl;
    }
}
