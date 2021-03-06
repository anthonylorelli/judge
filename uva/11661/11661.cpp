// Problem definition: https://uva.onlinejudge.org/external/116/11661.pdf
// Accepted 2019-02-12

#include <iostream>
#include <string>

int findMin(int currentMin, int m, int n)
{
    int d {m - n};
    return d < currentMin ? d : currentMin;
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    constexpr int maxDistance {2000001};
 
    int size {0};
    while (std::cin >> size && size != 0)
    {
        int min {maxDistance};
        int lastR {-1}, lastD {-1};

        char c {'\0'};
        for (int i {0}; i < size; ++i)
        {
            std::cin >> c;
            if (c == 'R')
            {
                lastR = i;
                if (lastD >= 0) { min = findMin(min, lastR, lastD); }
            } 
            else if (c == 'D')
            {
                lastD = i;
                if (lastR >= 0) { min = findMin(min, lastD, lastR); }
            }
            else if (c == 'Z')
            {
                min = 0;
            }
        }
        std::cout << min << "\n";
    }
}
