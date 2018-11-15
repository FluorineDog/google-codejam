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
using std::pair;
using std::set;
using std::string;
using std::vector;

using ll = long long;

static constexpr int MAX = 1 << 20;
class MonoidTree {
  public:
    using T = int;
    MonoidTree() : data(2 * MAX, NIL) {}
    void set(int loc, T value) {
        assert(loc < MAX);
        data[loc + MAX] = value;
        int offset = loc + MAX;
        while(offset >>= 1) {
            data[offset] = FUNC(data[2 * offset], data[2 * offset + 1]);
        }
    }
    inline T FUNC(T a, T b) {
        return a + b;
    }

    T get(int loc){
        return data[loc + MAX];
    }

    T reduce(int beg, int end) {
        int bsize = MAX;
        if(beg == end) {
            return NIL;
        }
        --end;
        if(beg == end) {
            return data[bsize + beg];
        }
        T left_sum = data[bsize + beg];
        T right_sum = data[bsize + end];
        while(end - beg != 1) {
            if(!(beg & 1)) {
                left_sum = FUNC(left_sum, data[bsize + beg + 1]);
            }
            if(end & 1) {
                right_sum = FUNC(data[bsize + end - 1], right_sum);
            }
            beg >>= 1;
            end >>= 1;
            bsize >>= 1;
        }
        return FUNC(left_sum, right_sum);
    }

  private:
    vector<T> data;
    static constexpr int NIL = 0;
};

class Solution {
  public:
    long long workload() {
        generate();
        std::sort(dots.begin(), dots.end());
        ll total_count = 0;
        int last_v = -1;
        int last_v_count = 0;
        MonoidTree tree;
        vector<pair<ll, ll>> record;
        for(auto [this_v, h] : dots) {
            if(this_v == last_v) {
                ++last_v_count;
            } else {
                last_v_count = 0;
                last_v = this_v;
            }
            tree.set(h, tree.get(h) + 1);
            ll up = tree.reduce(0, h) - last_v_count;
            ll down = tree.reduce(h + 1, MAX);
            record.emplace_back(up, down);
        }
        last_v = -1;
        tree = MonoidTree();
        for(int i = dots.size(); i-- > 0;) {
            auto [this_v, h] = dots[i];
            if(this_v == last_v) {
                ++last_v_count;
            } else {
                last_v_count = 0;
                last_v = this_v;
            }
            tree.set(h, tree.get(h) + 1);
            ll r_up = tree.reduce(0, h);
            ll r_down = tree.reduce(h + 1, MAX) - last_v_count;
            auto [up, down] = record[i];
            total_count += r_up * down + r_down * up;
            // cerr << "{" << this_v << ","<< h << "}";
            // cerr << up << "^" << down << "^" << r_up << "^" << r_down << "^";
        }
        // cout << total_count;
        return ((ll)N * (ll)(N - 1) * (N - 2)) / 6 - total_count;
    }

  private:
    void generate() {
        ll v, h;
        cin >> N;
        cin >> v >> h;
        ll a, b, c, d, e, f;
        ll m;
        cin >> a >> b >> c;
        cin >> d >> e >> f;
        cin >> m;
        dots.clear();
        for(int i = 0; i < N; ++i) {
            dots.emplace_back(v, h);
            ll v_new = (a * v + b * h + c) % m;
            ll h_new = (d * v + e * h + f) % m;
            v = v_new;
            h = h_new;
            // cerr << "[" << v << "," << h << "]";
        }
    }

  private:
    vector<pair<int, int>> dots;
    int N;
};

int main() {
    int N;
    cin >> N;
    for(int i = 0; i < N; ++i) {
        auto ans = Solution().workload();
        cout << "Case #" << i + 1
             << ": "                 //
                                     //  << std::fixed << std::setprecision(6) //
             << ans << std::endl;    //
    }
}
