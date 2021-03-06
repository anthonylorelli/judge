// Problem definition: https://uva.onlinejudge.org/external/117/11799.pdf
// Accepted 2019-01-30

#include <iostream>

int main()
{
    std::ios_base::sync_with_stdio(false);

    int cases {0};
    std::cin >> cases;

    for (int i = 1; i <= cases; ++i)
    {
        int creatures {0};
        std::cin >> creatures;
        int max {0};

        while (creatures--)
        {
            int speed {0};
            std::cin >> speed;
            if (speed > max) { max = speed; }
        }

        std::cout << "Case " << i << ": " << max << "\n";
    }
}
