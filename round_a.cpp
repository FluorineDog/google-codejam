#include <algorithm>
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
class Solution {
  public:
    ll workload() {
        generate();
        ll total_count = 0;
        vector<ll> count_map(200001, 0);
        std::sort(data.begin(), data.end());
        // data[beg+] >= 2
        int beg = std::upper_bound(data.begin(), data.end(), 1) - data.begin();
        std::cerr << beg << endl;
        for(int i = 0; i < N; ++i) {
            count_map[data[i]]++;
        }
        for(int i = beg; i < N; ++i) {
            for(int j = i + 1; j < N; ++j) {
                ll product = (ll)data[i] * data[j];
                if(product >= 200001) break;
                total_count += count_map[product];
            }
        }
        auto C_n_2 = [](ll n) { return n * (n - 1) / 2; };
        auto C_n_3 = [](ll n) { return n * (n - 1) * (n - 2) / 6; };

        ll count_1 = count_map[1];
        ll count_0 = count_map[0];
        // 1 * n = n
        for(int i = 2; i < count_map.size(); ++i) {
            total_count += count_1 * C_n_2(count_map[i]);
        }
        // 1 * 1 = 1
        total_count += C_n_3(count_1);
        // 0 * (1/n) = 0
        total_count += C_n_2(count_0) * (N - count_0);
        // 0 * 0 = 0
        total_count += C_n_3(count_0);
        return total_count;
    }

  private:
    void generate() {
        cin >> N;
        data.resize(N);
        for(auto &x : data) {
            cin >> x;
        }
    }
    int N;
    vector<int> data;
};
int main() {
    // freopen("input.txt", "r", stdin);
    int N;
    cin >> N;
    for(int i = 0; i < N; ++i) {
        auto ans = Solution().workload();
        cout << "Case #" << i + 1 << ": " << ans << std::endl;
    }
}
