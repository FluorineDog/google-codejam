#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

std::tuple<double, int> new_expected(const vector<double>& prefix_sum,
                                     const vector<double>& sorted_data, int N,
                                     double expected, int hint) {
    while(sorted_data[hint] < expected) {
        hint++;
    }
    double right_sum = prefix_sum[N] - prefix_sum[hint];
    double left_sum = expected * hint;
    double aver = (right_sum + left_sum) / N;
    return std::make_tuple(aver, hint);
}

double workload() {
    int N, K;
    cin >> N >> K;
    vector<double> vec(N);
    for(auto& x : vec) {
        cin >> x;
    }
    std::sort(vec.begin(), vec.end());
    vector<double> prefix_sum(N + 1);
    prefix_sum[0] = 0;
    for(int i = 0; i < N; ++i) {
        prefix_sum[i + 1] = prefix_sum[i] + vec[i];
    }

    double expected = 0;
    int hint = 0;
    for(int i = 0; i < K + 1; ++i) {
        std::tie(expected, hint) = new_expected(prefix_sum, vec, N, expected, hint);
    }
    return expected;
}

int main() {
    // freopen("build/input.txt",  "r", stdin);
    int N;
    cin >> N;
    for(int i = 0; i < N; ++i) {
        auto ans = workload();
        cout << "Case #" << i + 1 << ": " << std::fixed << std::setprecision(6) << ans << std::endl;
    }
}
