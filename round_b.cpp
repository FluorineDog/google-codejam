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
        // score, status
        vector<pair<ll, ll>> source;
        // rank_acc for >= score
        vector<ll> sums;
        // score, height
        vector<tuple<ll, ll>> records;
        // sums.emplace_back(0);
        // records.emplace_back(inf, 0);
        for(auto [l, r] : ranges) {
            source.emplace_back(l - 1, -1);
            source.emplace_back(r, +1);
        }
        std::sort(source.begin(), source.end());
        ll sum = 0;
        ll last_score = inf;
        ll last_height = 0;
        while(!source.empty()) {
            auto [score, diff] = source.back();
            source.pop_back();
            while(!source.empty()) {
                auto [s, d] = source.back();
                if(s == score) {
                    diff += d;
                    source.pop_back();
                } else {
                    break;
                }
                if(diff == 0) {
                    continue;
                }
            }
            sum += (last_score - score) * last_height;
            sums.emplace_back(sum);
            ll height = last_height + diff;
            records.emplace_back(score, height);
            last_score = score;
            last_height = height;
        }
        // find right-most x that rank >= sum
        // calculate
        ll result = 0;
        for(ll k_id = 0; k_id < Ks.size(); ++k_id) {
            ll rank = Ks[k_id] - 1;
            int it = std::upper_bound(sums.begin(), sums.end(), rank) - sums.begin();
            if(it == sums.size()) {
                continue;
            }
            it -= 1;
            auto [score, height] = records[it];
            ll real_score = score - (rank - sums[it]) / height;
            result += (k_id + 1) * real_score;
        }
        return result;
    }

  private:
    void generate() {
        cin >> N >> Q;
        ll x1, x2, a1, b1, c1, m1;
        ll y1, y2, a2, b2, c2, m2;
        ll z1, z2, a3, b3, c3, m3;
        cin >> x1 >> x2 >> a1 >> b1 >> c1 >> m1;
        cin >> y1 >> y2 >> a2 >> b2 >> c2 >> m2;
        cin >> z1 >> z2 >> a3 >> b3 >> c3 >> m3;
        for(int i = 0; i < N; ++i) {
            ll l = std::min(x1, y1) + 1;
            ll r = std::max(x1, y1) + 1;
            ranges.emplace_back(l, r);
            ll new_x = (a1 * x2 % m1 + b1 * x1 % m1 + c1) % m1;
            ll new_y = (a2 * y2 % m2 + b2 * y1 % m2 + c2) % m2;
            x1 = x2;
            x2 = new_x;
            y1 = y2;
            y2 = new_y;
        }
        for(int i = 0; i < Q; ++i) {
            ll new_z = (a3 * z2 % m3 + b3 * z1 % m3 + c3) % m3;
            ll k = z1 + 1;
            Ks.emplace_back(k);
            z1 = z2;
            z2 = new_z;
        }
        // for(auto r : ranges) {
        //     cerr << r.first << "*" << r.second << " ";
        // }
        // cerr << endl;
        // for(auto x : Ks) {
        //     cerr << x << " ";
        // }
        // cerr << endl;
    }
    int N, Q;
    vector<pair<ll, ll>> ranges;
    vector<ll> Ks;
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
