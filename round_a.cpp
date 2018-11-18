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
using ll = long long;
class Solution {
  public:
    ll workload() {
        generate();
        std::sort(data.begin(), data.end());
        string last = "xx";
        ll forbid_count = 0;
        for(const auto& x: data){
            if(x.substr(0, last.size()) == last){
                continue;
            }
            forbid_count += 1LL << (N - x.size()) ;
            last = x;
        }
        return (1LL << N) - forbid_count;
    }

  private:
    void generate() {
        cin >> N >> P;
        data.resize(P);
        for(auto &x : data) {
            cin >> x;
        }
    }
    int N, P;
    vector<string> data;
};
int main() {
//    freopen("/home/mike/workspace/google-codejam/input.txt", "r", stdin);
    int N;
    cin >> N;
    for(int i = 0; i < N; ++i) {
        auto ans = Solution().workload();
        cout << "Case #" << i + 1 << ": " << ans << std::endl;
    }
}
