// Problem definition: https://uva.onlinejudge.org/external/105/10550.pdf
// Accepted ?

#include <iostream>

int main()
{
    std::ios_base::sync_with_stdio(false);

    int position {0};
    int cA {0};
    int cB {0};
    int cC {0};

    while ((std::cin >> position >> cA >> cB >> cC) &&
        !(position == 0 && cA == 0 && cB == 0 && cC == 0))
    {
        std::cout << position << " " << cA << " " << cB << " " << cC << "\n";
    }
}
