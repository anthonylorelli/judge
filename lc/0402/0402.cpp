// 0402. Remove K Digits
// Problem definition: https://leetcode.com/problems/remove-k-digits/
// Accepted ?
// Cf. https://github.com/sstchur/coding_practice/tree/master/RemoveKDigits

#define CATCH_CONFIG_RUNNER
#include "../../uva/catch/catch.hpp"

#include <string>
#include <stack>

class Solution {
public:
    std::string removeKdigits(std::string num, int k) {
        if (k >= num.length()) { return "0"; }
        std::stack<char> hand;
        int count {0};
        for (const auto c : num) {
            if (hand.size() > 0 && c >= hand.top()) {
                hand.push(c);
            } else {
                hand.pop();
                count++;
                hand.push(c);
            }
        }
    }
};

TEST_CASE("LC test cases", "[Remove K Digits]") {
    std::vector<std::pair<std::pair<std::string,int>,std::string>> input {
        {{{"1432219",3},"1219"},{{"10200",1},"200"},{{"10",2},"0"}},{{"123",2},"1"}
    };

    SECTION("LC test cases") {
        std::for_each(std::begin(input), std::end(input),
            [&input](auto& p) { 
                Solution s;
                auto& [testInput, expected] = p;
                REQUIRE(s.removeKdigits(testInput.first, testInput.second) == expected);
            });
    }
}

int main(int argc, char* argv[]) {
    std::ios_base::sync_with_stdio(false);
    return Catch::Session().run(argc, argv);
}
