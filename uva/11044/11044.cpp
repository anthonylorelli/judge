// Problem definition: https://uva.onlinejudge.org/external/110/11044.pdf
// Accepted 2018-12-31

#include <iostream>

int main()
{
    std::ios_base::sync_with_stdio(false);

    int cases {0};
    int rows {0};
    int columns {0};

    std::cin >> cases;

    while (cases--)
    {
        std::cin >> rows >> columns;
        int sonarCount { (rows / 3) * (columns / 3) };
        std::cout << sonarCount << "\n";
    }
}
