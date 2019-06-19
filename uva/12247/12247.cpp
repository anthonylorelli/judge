// Jollo
// Problem definition: https://uva.onlinejudge.org/external/122/12247.pdf
// Accepted ?

#define CATCH_CONFIG_RUNNER
#include "../catch/catch.hpp"

#include <algorithm>
#include <array>
#include <iostream>
#include <set>

class JolloGame
{
public:
    JolloGame(std::istream& i) {
        for (auto& n : m_sister) { i >> n; m_cards.emplace(n); }
        for (auto& n : m_son) { i >> n; m_cards.emplace(n); }
        std::sort(m_sister.begin(), m_sister.end());
        std::sort(m_son.begin(), m_son.end());
    }

    const int card() const {
        // Both cards are smaller or both are larger
        if (m_son[1] < m_sister[2] && m_son[0] < m_sister[1])  {
            return noAnswer;
        } else if (m_son[1] > m_sister[2] && m_son[0] > m_sister[1]) {
            // return lowest available card in deck
            return noAnswer;
        }
        return noAnswer;
    }

    static constexpr int noAnswer{-1};

    const int next(const int n) const {
        int next{n};
        while (m_cards.find(next) != m_cards.end()) { ++next; }
        return next;
    }

private:
    std::array<int,3> m_sister;
    std::array<int,2> m_son;
    std::set<int> m_cards;
};

int execute(std::istream& in, std::ostream& out) {
    return 0;
}

int main(int argc, char* argv[]) {
    std::ios_base::sync_with_stdio(false);

    return Catch::Session().run(argc, argv);
    //return execute(std::cin, std::cout);
}

TEST_CASE("Card tests", "[Jollo]") {
    std::istringstream i{"1 2 3 4 5"};
    SECTION("Simple") {
        JolloGame g{i};
        REQUIRE(g.card() == JolloGame::noAnswer);
    }
}

TEST_CASE("Next tests", "[Jollo]") {
    SECTION("Simple") {
        std::istringstream i{"1 3 5 7 9"};
        JolloGame g{i};
        REQUIRE(g.next(1) == 2);
        REQUIRE(g.next(2) == 2);
        REQUIRE(g.next(3) == 4);
        REQUIRE(g.next(4) == 4);
        REQUIRE(g.next(5) == 6);
        REQUIRE(g.next(6) == 6);
        REQUIRE(g.next(7) == 8);
        REQUIRE(g.next(8) == 8);
        REQUIRE(g.next(9) == 10);
        REQUIRE(g.next(0) == 0);
        REQUIRE(g.next(10) == 10);
    }
}

TEST_CASE("Execute unit tests", "[Jollo]") {
    std::istringstream i{""};
    std::ostringstream o;
    REQUIRE(execute(i, o) == 0);
}
