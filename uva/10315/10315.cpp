// Problem definition: https://uva.onlinejudge.org/external/103/10315.pdf
// Accepted ?

#define CATCH_CONFIG_RUNNER
#include "../catch/catch.hpp"

#include <array>
#include <tuple>
#include <iostream>
#include <algorithm>
#include <initializer_list>
#include <unordered_map>
#include <memory>

std::unordered_map<char,int> rankToValue{
    {'2',2}, {'3',3}, {'4',4},{'5',5}, {'6',6}, {'7',7}, {'8',8}, 
    {'9',9}, {'T',10},{'J',11}, {'Q',12}, {'K',13}, {'A', 14}
};

std::unordered_map<int,char> valueToRank{
    {2,'2'}, {3,'3'}, {4,'4'},{5,'5'}, {6,'6'}, {7,'7'}, {8,'8'}, 
    {9,'9'}, {10,'T'}, {11,'J'}, {12,'Q'}, {13,'K'}, {14,'A'}
};

constexpr size_t handSize{5};
using card = std::pair<int,char>;
using card_list = std::initializer_list<std::initializer_list<char>>;

class PokerHand
{
public:
    PokerHand(const card_list& hand)
    {
        std::transform(hand.begin(), hand.end(), cards.begin(), 
            [](const std::initializer_list<char>& c) { return std::make_pair(rankToValue[*c.begin()], *(c.begin()+1)); });
    }
    std::array<card,handSize> cards;
};

class HighCard : public PokerHand
{
public:
    HighCard(const card_list& hand) : PokerHand{hand} {}
};

class Pair : public PokerHand
{
public:
    Pair(const card_list& hand, const int i) : PokerHand{hand}, m_i{i} {}

private:
    int m_i;
};

class TwoPairs : public PokerHand
{
public:
    TwoPairs(const card_list& hand, const int i, const int j) : PokerHand{hand}, m_i{i}, m_j{j} {}

private:
    int m_i;
    int m_j;
};

class ThreeOfAKind : public PokerHand
{
public:
    ThreeOfAKind(const card_list& hand, const int i) : PokerHand{hand}, m_i{i} {}

private:
    int m_i;
};

class Straight : public PokerHand
{
public:
    Straight(const card_list& hand) : PokerHand{hand} {}
};

class Flush : public PokerHand
{
public:
    Flush(const card_list& hand) : PokerHand{hand} {}
};

class FullHouse : public PokerHand
{
public:
    FullHouse(const card_list& hand, const int three, const int pair) : PokerHand{hand}, m_three{three}, m_pair{pair} {}

private:
    int m_three;
    int m_pair;
};

class FourOfAKind : public PokerHand
{
public:
    FourOfAKind(const card_list& hand) : PokerHand{hand} {}
};

class StraightFlush : public PokerHand
{
public:
    StraightFlush(const card_list& hand) : PokerHand{hand} {}
};

bool operator==(const PokerHand& p1, const PokerHand& p2)
{
    return std::equal(p1.cards.begin(), p1.cards.end(),
        p2.cards.begin(), p2.cards.end(), 
        [](const card& c1, const card& c2) { return c1.first == c2.first && c1.second == c2.second; });
}

template <typename T>
bool operator>(const HighCard& hc, const T& t) { return false; }

bool operator>(const Pair& p, const HighCard& hc) { return true; }
template <typename T>
bool operator>(const Pair& p, const T& t) { return false; }

bool operator>(const TwoPairs& tp, const HighCard& hc) { return true; }
bool operator>(const TwoPairs& tp, const Pair& p) { return true; }
template <typename T>
bool operator>(const TwoPairs& tp, const T& t) { return false; }

bool operator>(const ThreeOfAKind& toak, const HighCard& hc) { return true; }
bool operator>(const ThreeOfAKind& toak, const Pair& p) { return true; }
bool operator>(const ThreeOfAKind& toak, const TwoPairs& tp) { return true; }
template <typename T>
bool operator>(const ThreeOfAKind& toak, const T& t) { return false; }

template <typename T>
bool operator>(const Straight& s, const T& t) { return true; }
bool operator>(const Straight& s1, const Straight& s2) 
{ 
    return s1.cards.rbegin()->first > s2.cards.rbegin()->first;
}
bool operator>(const Straight& s, const Flush& f2) { return false; }
bool operator>(const Straight& s, const FullHouse& fh) { return false; }
bool operator>(const Straight& s, const FourOfAKind& foak) { return false; }
bool operator>(const Straight& s, const StraightFlush& sf) { return false; }

template <typename T>
bool operator>(const Flush& f, const T& t) { return true; }
bool operator>(const Flush& f1, const Flush& f2) { return false; }
bool operator>(const Flush& f1, const FullHouse& fh) { return false; }
bool operator>(const Flush& f1, const FourOfAKind& foak) { return false; }
bool operator>(const Flush& f1, const StraightFlush& sf) { return false; }

template <typename T>
bool operator>(const FullHouse& f, const T& t) { return true; }
bool operator>(const FullHouse& f, const FullHouse& t) { return false; }
bool operator>(const FullHouse& f, const FourOfAKind& t) { return false; }
bool operator>(const FullHouse& f, const StraightFlush& t) { return false; }

template <typename T>
bool operator>(const FourOfAKind& f, const T& t) { return true; }
bool operator>(const FourOfAKind& f1, const FourOfAKind& f2) { return false; }
bool operator>(const FourOfAKind& f, const StraightFlush& sf) { return false; }

template <typename T>
bool operator>(const StraightFlush& sf, const T& t) { return true; }
bool operator>(const StraightFlush& sf1, const StraightFlush& sf2) 
{ 
    return sf1.cards.rbegin()->first > sf2.cards.rbegin()->first;
}

std::ostream& operator<<(std::ostream& o, std::array<card,handSize> hand)
{
    o << "Hand: ";
    std::for_each(hand.begin(), hand.end(), [&o](card& c) { o << " " << valueToRank[c.first] << c.second; });
    o << "\n";
    return o;
}

enum class HandType
{
    HighCard,
    Pair,
    TwoPairs,
    ThreeOfAKind,
    Straight,
    Flush,
    FullHouse,
    FourOfAKind,
    StraightFlush
};

PokerHand MakeHand(const card_list& hand)
{
    return HighCard(hand);
}

bool IsNOfAKind(const std::array<card,handSize>& hand, const int n)
{
    bool result{false};
    int count{1};
    int rank{hand[0].first};
    std::for_each(hand.begin()+1, hand.end(), [&](const std::pair<int,char>& c) 
        { if (c.first == rank) { count++; if (count == n) { result = true; }} else { rank = c.first; count = 1; }});

    return result;
}

bool IsTwoPairs(const std::array<card,handSize>& hand)
{
    auto findPair{[](const card& c1, const card& c2) { return c1.first == c2.first; }};
    auto first{std::adjacent_find(hand.begin(), hand.end(), findPair)};
    auto second{(first != hand.end() && first + 2 != hand.end()) ?
        std::adjacent_find(first+2, hand.end(), findPair) : hand.end()};
    return second != hand.end();
}

bool IsStraight(const std::array<card,handSize>& hand)
{
    int rank{hand[0].first + 1};
    return std::all_of(hand.begin()+1, hand.end(), 
        [&rank](const card& c) { return c.first == rank++; });
}

bool IsStraightFlush(const std::array<card,handSize>& hand)
{
    int rank{hand[0].first + 1};
    const char suit{hand[0].second};
    return std::all_of(hand.begin()+1, hand.end(),
        [&rank, &suit](const card& c) { return c.first == rank++ && c.second == suit; });
}

card GetHighCard(const std::array<card,handSize>& hand)
{
    return hand[handSize - 1];
}

bool IsPair(const std::array<card,handSize>& hand)
{
    return IsNOfAKind(hand, 2);
}

bool IsThreeOfAKind(const std::array<card,handSize>& hand)
{
    return IsNOfAKind(hand, 3);
}

bool IsFullHouse(const std::array<card,handSize>& hand)
{
    return (hand[0].first == hand[1].first && hand[1].first == hand[2].first && hand[3].first == hand[4].first) ||
        (hand[0].first == hand[1].first && hand[2].first == hand[3].first && hand[3].first == hand[4].first);
}

bool IsFourOfAKind(const std::array<card,handSize>& hand)
{
    return IsNOfAKind(hand, 4);
}

bool IsFlush(const std::array<card,handSize>& hand)
{
    const char suit{hand[0].second};
    return std::all_of(hand.begin()+1, hand.end(), 
        [&suit](const card& c) { return c.second == suit; });
}



HandType ClassifyHand(const std::array<card,handSize>& hand)
{
    auto type = IsStraightFlush(hand) ? HandType::StraightFlush :
        IsFourOfAKind(hand) ? HandType::FourOfAKind :
        IsFullHouse(hand) ? HandType::FullHouse :
        IsFlush(hand) ? HandType::Flush :
        IsStraight(hand) ? HandType::Straight :
        IsThreeOfAKind(hand) ? HandType::ThreeOfAKind :
        IsTwoPairs(hand) ? HandType::TwoPairs :
        IsPair(hand) ? HandType::Pair : HandType::HighCard;

    return type;
}

enum class Winner
{
    Black,
    White,
    Tie
};

const Winner BreakTie(const HandType type, const std::array<card,handSize>& blackHand, 
    const std::array<card,handSize>& whiteHand)
{
    Winner winner;

    if (type == HandType::Straight || type == HandType::StraightFlush)
    {
        const card blackHighCard{GetHighCard(blackHand)};
        const card whiteHighCard{GetHighCard(whiteHand)};
        winner = blackHighCard == whiteHighCard ? Winner::Tie :
            blackHighCard > whiteHighCard ? Winner::Black : Winner::White;
    }

    return winner;
}

const Winner ChooseWinner(const HandType blackType, const std::array<card,handSize>& blackHand, 
    const HandType whiteType, const std::array<card,handSize>& whiteHand)
{
    return (blackType == whiteType) ? BreakTie(blackType, blackHand, whiteHand) :
        (blackType > whiteType) ? Winner::Black : Winner::White;
}

int execute(std::istream& in, std::ostream& out)
{
    std::array<card,handSize> blackHand;
    std::array<card,handSize> whiteHand;

    char rank, suit;
    auto assignCard{[&in, &rank](card& c) 
    { 
        in >> rank >> c.second; 
        c.first = rankToValue[rank];
    }};
    auto sortHand([](const card& c1, const card& c2) { return c1.first < c2.first; });

    while (in >> rank >> suit)
    {
        blackHand[0].first = rankToValue[rank];
        blackHand[0].second = suit;
        std::for_each(blackHand.begin() + 1, blackHand.end(), assignCard);
        std::for_each(whiteHand.begin(), whiteHand.end(), assignCard);
        std::sort(blackHand.begin(), blackHand.end(), sortHand);
        std::sort(whiteHand.begin(), whiteHand.end(), sortHand);
        auto blackType{ClassifyHand(blackHand)};
        auto whiteType{ClassifyHand(whiteHand)};
        const auto winner{ChooseWinner(blackType, blackHand, whiteType, whiteHand)};
        out << blackHand << whiteHand;
    }

    return 0;
}

int main(int argc, char* argv[])
{
    std::ios_base::sync_with_stdio(false);

    return Catch::Session().run(argc, argv);
    //return execute(std::cin, std::cout);
}

TEST_CASE("Hand recognition", "[PokerHands]")
{
    card_list hand{{'2','H'},{'3','H'},{'4','H'},{'5','H'},{'6','H'}};

    REQUIRE(hand.size() == handSize);

    SECTION("Straight flush")
    {
        REQUIRE(true);
    }
    SECTION("Four of a kind")
    {
        REQUIRE(true);
    }
    SECTION("Full house")
    {
        REQUIRE(true);
    }
}

TEST_CASE("Hand greater than comparisons", "[PokerHands]")
{
    StraightFlush sf{{'2','H'},{'3','H'},{'4','H'},{'5','H'},{'6','H'}};
    FourOfAKind foak{{'2','C'},{'2','D'},{'2','H'},{'2','S'},{'6','H'}};
    FullHouse fh{{{'2','C'},{'2','D'},{'2','C'},{'5','H'},{'5','S'}}, 0, 3};
    Flush f{{'2','H'},{'6','H'},{'9','H'},{'J','H'},{'K','H'}};
    Straight s{{'2','H'},{'3','S'},{'4','D'},{'5','C'},{'6','C'}};
    ThreeOfAKind toak{{{'2','H'},{'3','H'},{'4','D'},{'4','H'},{'4','S'}}, 2};
    TwoPairs tp{{{'2','H'},{'3','H'},{'3','S'},{'6','H'},{'6','S'}}, 1, 3};
    Pair p{{{'2','H'},{'2','S'},{'4','H'},{'5','H'},{'6','H'}}, 0};
    HighCard hc{{'2','S'},{'5','H'},{'6','D'},{'9','H'},{'J','S'}};

    SECTION("Straight flush")
    {
        StraightFlush sf1{{'3','H'},{'4','H'},{'5','H'},{'6','H'},{'7','H'}};
        StraightFlush sf2{{'2','H'},{'3','H'},{'4','H'},{'5','H'},{'6','H'}};
        StraightFlush sf3{{'2','H'},{'3','H'},{'4','H'},{'5','H'},{'6','H'}};

        REQUIRE(sf1 > sf2);
        REQUIRE(!(sf2 > sf1));
        REQUIRE(!(sf2 > sf3));
        REQUIRE(sf2 == sf3);
        REQUIRE(sf > foak);
        REQUIRE(sf > fh);
        REQUIRE(sf > f);
        REQUIRE(sf > s);
        REQUIRE(sf > toak);
        REQUIRE(sf > tp);
        REQUIRE(sf > p);
        REQUIRE(sf > hc);
    }
    SECTION("Four of a kind")
    {
        REQUIRE(!(foak > sf));
        REQUIRE(!(foak > foak));
        REQUIRE(foak > fh);
        REQUIRE(foak > f);
        REQUIRE(foak > s);
        REQUIRE(foak > toak);
        REQUIRE(foak > tp);
        REQUIRE(foak > p);
        REQUIRE(foak > hc);
    }
    SECTION("Full house")
    {
        REQUIRE(!(fh > sf));
        REQUIRE(!(fh > foak));
        REQUIRE(!(fh > fh));
        REQUIRE(fh > f);
        REQUIRE(fh > s);
        REQUIRE(fh > toak);
        REQUIRE(fh > tp);
        REQUIRE(fh > p);
        REQUIRE(fh > hc);
    }
    SECTION("Flush")
    {
        REQUIRE(!(f > sf));
        REQUIRE(!(f > foak));
        REQUIRE(!(f > fh));
        REQUIRE(!(f > f));
        REQUIRE(f > s);
        REQUIRE(f > toak);
        REQUIRE(f > tp);
        REQUIRE(f > p);
        REQUIRE(f > hc);
    }
    SECTION("Straight")
    {
        REQUIRE(!(s > sf));
        REQUIRE(!(s > foak));
        REQUIRE(!(s > fh));
        REQUIRE(!(s > f));
        REQUIRE(!(s > s));
        REQUIRE(s > toak);
        REQUIRE(s > tp);
        REQUIRE(s > p);
        REQUIRE(s > hc);
    }
    SECTION("Three of a kind")
    {
        REQUIRE(!(toak > sf));
        REQUIRE(!(toak > foak));
        REQUIRE(!(toak > fh));
        REQUIRE(!(toak > f));
        REQUIRE(!(toak > s));
        REQUIRE(!(toak > toak));
        REQUIRE(toak > tp);
        REQUIRE(toak > p);
        REQUIRE(toak > hc);
    }
    SECTION("Two pairs")
    {
        REQUIRE(!(tp > sf));
        REQUIRE(!(tp > foak));
        REQUIRE(!(tp > fh));
        REQUIRE(!(tp > f));
        REQUIRE(!(tp > s));
        REQUIRE(!(tp > toak));
        REQUIRE(!(tp > tp));
        REQUIRE(tp > p);
        REQUIRE(tp > hc);
    }
    SECTION("Pair")
    {
        REQUIRE(!(p > sf));
        REQUIRE(!(p > foak));
        REQUIRE(!(p > fh));
        REQUIRE(!(p > f));
        REQUIRE(!(p > s));
        REQUIRE(!(p > toak));
        REQUIRE(!(p > tp));
        REQUIRE(!(p > p));
        REQUIRE(p > hc);
    }
    SECTION("High card")
    {
        REQUIRE(!(hc > sf));
        REQUIRE(!(hc > foak));
        REQUIRE(!(hc > fh));
        REQUIRE(!(hc > f));
        REQUIRE(!(hc > s));
        REQUIRE(!(hc > toak));
        REQUIRE(!(hc > tp));
        REQUIRE(!(hc > p));
        REQUIRE(!(hc > hc));
    }
}
