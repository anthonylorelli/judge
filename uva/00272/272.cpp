// Problem definition: https://uva.onlinejudge.org/external/2/272.pdf
// Accepted 2018-12-24

#include <iostream>

int main()
{
    std::ios_base::sync_with_stdio(false);

    char c {0};
    bool closePair {false};

    while (std::cin.get(c))
    {
        if (c == '"')
        {
            std::cout << (closePair ? "''" : "``");
            closePair = !closePair;
        }
        else
        {
            std::cout << c;
        }
    }
}
