#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <tuple>
#include <vector>
using std::cin;
using std::cerr;
using std::cout;
using std::endl;
using std::make_tuple;
using std::pair;
using std::set;
using std::string;
using std::vector;

using ll = long long;

class Solution {
  public:
    long long workload() {
        generate();
        return 0;
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
        }
        cerr << "[" << N << "]";
        for(auto [v, w]: dots){
            cerr << "(" << v <<  ',' << w << ")";
        }
        cerr << endl;
    }

  private:
    vector<pair<int, int>> dots;
    int N;
};

int main() {
    // freopen("build/input.txt",  "r", stdin);
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
