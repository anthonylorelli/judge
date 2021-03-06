// Problem definition: https://uva.onlinejudge.org/external/115/11507.pdf
// Accepted 2019-02-10

#include <iostream>
#include <string>
#include <unordered_map>

std::unordered_map<std::string,std::unordered_map<std::string,std::string>> table =
    {
        {"+x", { {"+y", "+y"}, {"-y", "-y"}, {"+z", "+z"}, {"-z", "-z"}, }},
        {"-x", { {"+y", "-y"}, {"-y", "+y"}, {"+z", "-z"}, {"-z", "+z"}, }},
        {"+y", { {"+y", "-x"}, {"-y", "+x"}, {"+z", "+y"}, {"-z", "+y"}, }},
        {"-y", { {"+y", "+x"}, {"-y", "-x"}, {"+z", "-y"}, {"-z", "-y"}, }},
        {"+z", { {"+y", "+z"}, {"-y", "+z"}, {"+z", "-x"}, {"-z", "+x"}, }},
        {"-z", { {"+y", "-z"}, {"-y", "-z"}, {"+z", "+x"}, {"-z", "-x"}, }},
    };

std::string Rotate(const std::string& direction, const std::string& move)
{
    return move == "No" ? direction : table[direction][move];
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    int length {0};

    while (std::cin >> length && length != 0)
    {
        std::string direction{"+x"};
        std::string move;
        while (--length)
        {
            std::cin >> move;
            direction = Rotate(direction, move);
        }

        std::cout << direction << "\n";
    }
}
