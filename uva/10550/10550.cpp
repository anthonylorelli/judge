// Problem definition: https://uva.onlinejudge.org/external/105/10550.pdf
// Accepted 2018-12-28

#include <iostream>

int main()
{
    std::ios_base::sync_with_stdio(false);

    int start {0};
    int cA {0};
    int cB {0};
    int cC {0};

    while ((std::cin >> start >> cA >> cB >> cC) &&
        !(start == 0 && cA == 0 && cB == 0 && cC == 0))
    {
        // Turn the dial clockwise two full turns
        // Stop at the first number of the combination
        // Turn the dial counter clockwise one full turn
        // Continue turning until the second number is reached
        // Turn the dial back clockwise until the third number is reached
        // Pull the shank and the lock will open
        int totalDegrees {1080};
        int ticksMoved {0};
        constexpr int scaleFactor {9};
        constexpr int dialSize {40};

        ticksMoved += (start > cA) ? start - cA : (dialSize - cA + start);
        ticksMoved += (cA <= cB) ? cB - cA : (dialSize - cA + cB);
        ticksMoved += (cB > cC) ? cB - cC : (dialSize - cC + cB);
        totalDegrees += ticksMoved * scaleFactor;

        std::cout << totalDegrees << "\n";
    }
}
