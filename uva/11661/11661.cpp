// Problem definition: https://uva.onlinejudge.org/external/116/11661.pdf
// Accepted ?

#include <iostream>
#include <string>

int main()
{
    std::ios_base::sync_with_stdio(false);

    constexpr int maxDistance {2000001};
 
    int size {0};
    while (std::cin >> size && size != 0)
    {
        int min {maxDistance};
        int lastR {-1}, lastD {-1};

        for (int i {0}; i < size; ++i)
        {
            char c;
            std::cin >> c;
            if (c == 'R')
            {
                lastR = i;
                if (lastD >= 0)
                {
                    int d {lastR - lastD};
                    if (d < min) { min = d; }
                }
            } 
            else if (c == 'D')
            {
                lastD = i;
                if (lastR >= 0)
                {
                    int d {lastD - lastR};
                    if (d < min) { min = d; }
                }
            }
            else if (c == 'Z')
            {
                min = 0;
            }
        }
        std::cout << min << "\n";
    }
}
