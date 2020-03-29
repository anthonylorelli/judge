// 1296. Divide Array in Sets of K Consecutive Numbers
// Problem definition: https://leetcode.com/problems/divide-array-in-sets-of-k-consecutive-numbers/
// Accepted ?

#define CATCH_CONFIG_RUNNER
#include "../../uva/catch/catch.hpp"

#include <vector>
#include <algorithm>
#include <set>
#include <iterator>

class Solution {
public:
    bool isPossibleDivide(std::vector<int>& nums, int k) {
        if (nums.size() % k > 0) { return false; }
        std::multiset<int> set;
        std::copy(nums.begin(), nums.end(), std::inserter(set, set.end()));
        while (nums.size() > 0) {
            auto current {*set.begin()};
            for (int i {1}; i < k; ++i) {
                if (set.count(current + 1)) {
                    set.extract(current);
                    current++;
                } else {
                    return false;
                }
            }
        }
        return true;
    }
};

TEST_CASE("LC test cases", "[Divide Array in Sets of K Consecutive Numbers]") {
    std::vector<std::pair<std::pair<std::vector<int>,int>,bool>> input {
        {{{1,2,3,3,4,4,5,6},4},true},{{{3,2,1,2,3,4,3,4,5,9,10,11},3},true},
        {{{3,3,2,2,1,1},3},true},{{{1,2,3,4},3},false}
    };

    SECTION("LC test cases") {
        std::for_each(std::begin(input), std::end(input),
            [&input](auto& p) { 
                Solution s;
                auto& [testInput, expected] = p;
                REQUIRE(s.isPossibleDivide(testInput.first, testInput.second) == expected);
            });
    }
}

int main(int argc, char* argv[]) {
    std::ios_base::sync_with_stdio(false);
    return Catch::Session().run(argc, argv);
}
