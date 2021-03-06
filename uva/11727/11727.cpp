// Problem definition: https://uva.onlinejudge.org/external/117/11727.pdf
// Accepted 2019-01-15

#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::ios_base::sync_with_stdio(false);

    int caseNum {1};
    int limit {0};
    std::cin >> limit;

    while (caseNum <= limit)
    {
        int n {0};
        std::vector<int> salaries;
        for (int i = 0; i < 3; ++i) 
        {
            std::cin >> n;
            salaries.push_back(n);
        }        

        std::sort(salaries.begin(), salaries.end());
        std::cout << "Case " << caseNum++ << ": " << salaries[1] << "\n";
    }
}
