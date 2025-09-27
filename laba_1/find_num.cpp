#include "find_num.h"

long long find_num(std::string s) {
    std::string tmp_str;
    for (char c : s) {
        if (c > 47 && c < 58) {
            tmp_str += c;
            // std::cout << tmp_str << std::endl;
        }
    }
    long long ans = 0;
    int n = tmp_str.length();
    for (int i = n; i > 0; --i) {
        char num = tmp_str[n - i] - 48;
        ans += num * pow(10, i - 1);
        // std::cout << ans << std::endl;
    }
    return ans;
}
