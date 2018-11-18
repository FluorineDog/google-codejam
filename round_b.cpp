#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::make_pair;
using std::map;
using std::pair;
using std::priority_queue;
using std::string;
using std::tuple;
using std::vector;
using ll = long long;
constexpr ll inf = 1LL << 44;

class Solution {
public:
    ll workload() {
        generate();
        vector<ll> sums;
        {
            ll sum = 0;
            for (auto ch: nums) {
                sums.push_back(sum);
                ll digit = ch - '0';
                sum += digit;
            }
            sums.push_back(sum);
        }
        int len = (N + 1)/2;
        ll max = 0;
        for(int i = 0;  i +len < N + 1; ++i){
            max = std::max(max, sums[i + len] - sums[i]);
        }
        return max;
    }

private:
    void generate() {
        cin >> N;
        cin >> nums;
    }

    int N;
    string nums;

};

int main() {
    // freopen("input.txt", "r", stdin);
    int N;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        auto ans = Solution().workload();
        cout << "Case #" << i + 1 << ": " << ans << std::endl;
    }
}
