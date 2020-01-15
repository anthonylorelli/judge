// 1092. Shortest Common Supersequence
// Problem definition: https://leetcode.com/problems/shortest-common-supersequence/
// ?

#define CATCH_CONFIG_RUNNER
#include "../../uva/catch/catch.hpp"

#include <string>
#include <unordered_map>

class Trie {
public:
    Trie() { }

    template <typename It>
    void insert(const It& b, const It& e) {
        if (b != e) {
            bool terminal { b + 1 == e };
            if (!m_children.count(*b)) {
                m_children.insert({*b, std::make_pair(std::make_unique<Trie>(), terminal)});
            } else {
                m_children[*b].second = terminal;
            }
            m_children[*b].first->insert(b + 1, e);
        }
    }

    template <typename It>
    int match(const It& b, const It& e) {
        return match(b, e, 0);
    }

private:
    template <typename It>
    int match(const It& b, const It& e, const int prefix) {
        if (b != e && m_children.count(*b)) {
            int sum {prefix + 1};
            int rest {m_children[*b].first->match(b+1, e, sum)};
            return (m_children[*b].second && !rest) ? sum : rest;
        }
        return 0;
    }

    std::unordered_map<char, std::pair<std::unique_ptr<Trie>,bool>> m_children;
};

class SuffixTree {
public:
    SuffixTree(const std::string& s) {
        auto b {s.begin()};
        auto e {s.end()};
        while (b != e) { m_trie.insert(b++, e); }
    }

    int match(const std::string::iterator& b, const std::string::iterator& e) {
        return m_trie.match(b, e);
    }

    int match(const std::string& s) {
        return m_trie.match(s.begin(), s.end());
    }

private:
    Trie m_trie;
};

class Solution {
public:
    std::string shortestCommonSupersequence(std::string str1, std::string str2) {
        SuffixTree s1 {str1}, s2 {str2};
        auto pre1 {s2.match(str1)};
        auto pre2 {s1.match(str2)};
        return pre1 > pre2 ? str2 + str1.substr(pre1) : str1 + str2.substr(pre2);
    }
};

TEST_CASE("LC test cases", "[Repeated Substring Pattern]") {
    std::vector<std::pair<std::pair<std::string,std::string>,std::string>> input {
        {{"abac","cab"},"cabac"},{{"cab","abac"},"cabac"}
    };

    SECTION("LC test cases") {
        std::for_each(std::begin(input), std::end(input),
            [&input](auto& p) { 
                Solution s;
                auto& [testInput, expected] = p;
                REQUIRE(s.shortestCommonSupersequence(testInput.first, testInput.second) == expected);
            });
    }
}

TEST_CASE("Suffix tree cases", "[Suffix tree cases]") {
    std::vector<std::pair<std::pair<std::string,std::string>,int>> input {
        {{"acab","cab"},3},{{"cab","abac"},2},{{"abac","abacab"},4}
    };

    SECTION("LC test cases") {
        std::for_each(std::begin(input), std::end(input),
            [&input](auto& p) { 
                auto& [testInput, expected] = p;
                SuffixTree tree{testInput.first};
                REQUIRE(tree.match(testInput.second) == expected);
            });
    }
}

int main(int argc, char* argv[]) {
    std::ios_base::sync_with_stdio(false);
    return Catch::Session().run(argc, argv);
}