// 0214. Shortest Palindrome
// Problem definition: https://leetcode.com/problems/shortest-palindrome/
// Accepted ?
// https://en.wikipedia.org/wiki/List_of_prime_numbers

#define CATCH_CONFIG_RUNNER
#include "../../uva/catch/catch.hpp"

#include <string>
#include <unordered_map>
#include <memory>
#include <numeric>
#include <iostream>
#include <cmath>

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
    template <typename It>
    SuffixTree(const It& b, const It& e) {
        auto i {b};
        while (i != e) { m_trie.insert(i++, e); }
    }

    int match(const std::string::iterator& b, const std::string::iterator& e) {
        return m_trie.match(b, e);
    }

private:
    Trie m_trie;
};

class Solution {
public:
    std::string shortestPalindromeTrueStchurIndexMethod(std::string s) {
        return "";
    }

    std::string shortestPalindromeStchurIndexMethod(std::string s) {
        for (size_t e {s.length()}; e > 0; --e) {
            auto midpoint {e / 2};
            bool even {e % 2 == 0};
            size_t i {0}, j {even ? (midpoint - 1) : midpoint}, k {midpoint}, l {e - 1};
            if (e < 4) { k = i; j = l; }
            while (s[i] == s[l] && s[j] == s[k] && i < j) {
                i++; j--; k++; l--;
            }
            if (i >= j) {
                std::string prefix(s.rbegin(), s.rbegin() + (s.length() - e));
                return prefix + s;
            }
        }
        return s;
    }

    std::string shortestPalindromeBoyerMoore(std::string s) {
        for (auto b {s.rbegin()}; b != s.rend(); ++b) {
            auto length {s.rend() - b};
            auto it = std::search(b, s.rend(),
                std::boyer_moore_searcher(s.begin(), s.begin() + length));
            if (it != s.rend()) {
                std::string prefix(s.rbegin(), b);
                return prefix + s;
            }
        }
        return s;
    }

    std::string shortestPalindromeStephenMethod(std::string s) {
        for (auto b {s.rbegin()}; b != s.rend(); ++b) {
            auto length {s.rend() - b};
            auto midpoint {length / 2};
            if (length >= 5) {
                auto quarter {midpoint / 2};
                bool even {length % 2 == 0};
                auto offset {midpoint + (even ? 0 : 1)};
                if (std::equal(s.begin(), s.begin() + quarter, b) &&
                    std::equal(s.begin() + offset, s.begin() + offset + quarter, b + offset)) {
                    std::string prefix(s.rbegin(), b);
                    return prefix + s;
                }
            } else {
                if (std::equal(b, b + midpoint, s.begin())) {
                    std::string prefix(s.rbegin(), b);
                    return prefix + s;
                }
            }
        }
        return s;
    }

    std::string shortestPalindromeOneWayScan(std::string s) {
        for (auto b {s.rbegin()}; b != s.rend(); ++b) {
            auto midpoint {(s.rend() - b) / 2};
            if (std::equal(b, b + midpoint, s.begin())) {
                std::string prefix(s.rbegin(), b);
                return prefix + s;
            }
        }
        return s;
    }

    std::string shortestPalindromeSuffixTree(std::string s) {
        SuffixTree t(s.rbegin(), s.rend());
        int longestMatch {t.match(s.begin(), s.end())};
        size_t prefixLength {s.length() - longestMatch};
        std::string prefix(s.rbegin(), s.rbegin() + prefixLength);
        return prefix + s;
    }

    static constexpr unsigned int c_base {256};
    static constexpr unsigned int c_mod {7778777};

    template<typename It>
    unsigned int hash(const It& b, const It& e) {
        return std::accumulate(b, e, 0, [&](const unsigned int h, const char c) {
            return ((h * c_base) + c) % c_mod;
        });
    }

    template<typename It>
    unsigned int reverse_hash(const It& b, const It& e) {
        unsigned int place_value {1};
        return std::accumulate(b, e, 0, [&](const unsigned int h, const char c) {
            unsigned int next {(h + c * place_value) % c_mod};
            place_value = (place_value * c_base) % c_mod;
            return next;
        });
    }

    unsigned int hash(const std::string& s) {
        unsigned int place_value {1};
        unsigned int index {0};
        unsigned int fh {0}, rh {0};
        for (unsigned int i {0}; i < s.length(); ++i, place_value = (place_value * c_base) % c_mod) {
            fh = ((fh * c_base) + s[i]) % c_mod;
            rh = (rh + (s[i] * place_value)) % c_mod;
            if (fh == rh) { index = i; }
        }
        return s.length() - (index + 1);
    }

    std::string shortestPalindrome(std::string s) {
        if (s.length() > 0) {
            unsigned int length {hash(s)};
            std::string prefix(s.rbegin(), s.rbegin() + length);
            return prefix + s;
        } else {
            return s;
        }
    }

    unsigned int subtract_left(const unsigned int h, const int exp, const char c) const {
        return ((h + c_mod) - (static_cast<unsigned int>(std::pow(c_base, exp)) * c) % c_mod) % c_mod;
    }
};

TEST_CASE("Hash test cases", "[Shortest Palindrome]") {
    Solution s;    
    SECTION("Create hash") {
        std::vector<std::pair<std::string,int>> input {
            {"a", 97}, {"b", 98}, {"ab", 24930}, {"bc", 25187}, {"abc", 6382179} 
        };
        std::for_each(std::begin(input), std::end(input),
            [&s, &input](const auto& p) { 
                REQUIRE(s.hash(p.first.begin(), p.first.end()) == p.second); 
            });
    }
    SECTION("Hash symmetry") {
        std::vector<std::string> input {
            "abcba", "bbbb", "c", ""
        };
        std::for_each(std::begin(input), std::end(input),
            [&s, &input](const auto& p) { 
                REQUIRE(s.hash(p.begin(), p.end()) == s.hash(p.rbegin(), p.rend()));
            });
    }
    SECTION("Reverse hash") {
        std::vector<std::string> input {
            "abc", "bbbb", "c", "", "aaacecaaa"
        };
        std::for_each(std::begin(input), std::end(input),
            [&s, &input](const auto& p) { 
                REQUIRE(s.hash(p.begin(), p.end()) == s.reverse_hash(p.rbegin(), p.rend()));
            });
    }
}

TEST_CASE("LC test cases", "[Shortest Palindrome]") {
    Solution s;
    std::vector<std::pair<std::string,std::string>> input {
        {"aacecaaa", "aaacecaaa"}, {"abcd", "dcbabcd"},
        {"ababbbabbaba", "ababbabbbababbbabbaba"} 
    };

    SECTION("LC test cases") {
        std::for_each(std::begin(input), std::end(input),
            [&s, &input](const auto& p) { 
                REQUIRE(s.shortestPalindrome(p.first) == p.second); 
            });
    }
}

TEST_CASE("Local test cases", "[Shortest Palindrome]") {
    Solution s;
    std::vector<std::pair<std::string,std::string>> input {
        {"aaaa", "aaaa"}, {"aaa", "aaa"}, {"d", "d"},
        {"abcdefghijklmnopqrstuvwxyz", "zyxwvutsrqponmlkjihgfedcbabcdefghijklmnopqrstuvwxyz"},
        {"bbcd", "dcbbcd"}, {"", ""}, {"dad", "dad"}
    };

    SECTION("Local test cases") {
        std::for_each(std::begin(input), std::end(input),
            [&s, &input](const auto& p) { 
                REQUIRE(s.shortestPalindrome(p.first) == p.second); 
            });
    }
}

TEST_CASE("TLE test cases", "[Shortest Palindrome]") {
    Solution s;
    std::vector<std::pair<std::string,std::string>> input {
        {"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaacdaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
         "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaadcaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaacdaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"}
    };

    SECTION("Local test cases") {
        std::for_each(std::begin(input), std::end(input),
            [&s, &input](const auto& p) { 
                REQUIRE(s.shortestPalindrome(p.first) == p.second); 
            });
    }
}

int main(int argc, char* argv[]) {
    std::ios_base::sync_with_stdio(false);
    return Catch::Session().run(argc, argv);
}
