#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::end;
using std::string;

long long to_number(string str) {
    return atoll(str.c_str());
}

string find_small(string num_str) {
    for(int i = 0; i < num_str.size(); ++i) {
        char ch = num_str[i];
        auto digit = ch - '0';
        if(digit % 2 == 1) {
            num_str[i] = ch - 1;
            ++i;
            for(; i < num_str.size(); ++i) {
                num_str[i] = '8';
            }
            break;
        }
    }
    return num_str;
}

string find_large(string num_str) {
    for(int i = 0; i < num_str.size(); ++i) {
        char ch = num_str[i];
        auto digit = ch - '0';
        if(digit % 2 == 1) {
            if(digit != 9) {
                num_str[i] = ch + 1;
                ++i;
                for(; i < num_str.size(); ++i) {
                    num_str[i] = '0';
                }
                break;
            } else {
                // impossible
                return "0";
            }
        }
    }
    return num_str;
}

long long workload() {
    string num_str;
    cin >> num_str;
    auto num = to_number(num_str);
    auto la = to_number(find_large(num_str));
    auto sm = to_number(find_small(num_str));
    if(la == 0){
        return num - sm;
    }
    else {
        return std::min(num - sm, la - num);
    }
}

int main() {
    int N;
    cin >> N;
    for(int i = 0; i < N; ++i){
       auto ans = workload();
       cout << "Case #" << i + 1 << ": " << ans << std::endl;
    }
}
