// Problem definition: https://uva.onlinejudge.org/external/124/12468.pdf
// Accepted 2019-02-01

#include <iostream>

int main()
{
    std::ios_base::sync_with_stdio(false);

    int c1 {0}, c2 {0};
    
    while (std::cin >> c1 >> c2 && !(c1 == -1 && c2 == -1))
    {
        int d1 {c2 - c1};
        int d2 {c1 + 100 - c2};
        int d3 {c1 - c2};
        int d4 {c2 + 100 - c1};

        if (c1 < c2 && d1 <= d2)
        {
            std::cout << d1;
        }
        else if (c1 < c2 && d1 > d2)
        {
            std::cout << d2;
        }
        else if (c1 > c2 && d3 <= d4)
        {
            std::cout << d3;
        }
        else if (c1 > c2 && d3 > d4)
        {
            std::cout << d4;
        }
        else if (c1 == c2)
        {
            std::cout << 0;
        }

        std::cout << "\n";
    }
}
