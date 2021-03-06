// Problem definition: https://uva.onlinejudge.org/external/122/12279.pdf
// Accepted 2019-01-15

#include <iostream>
#include <vector>

int main()
{
    std::ios_base::sync_with_stdio(false);

    int cases {0};
    int count {1};

    while (std::cin >> cases && cases != 0)
    {
        std::vector<int> events;
        while (cases--)
        {
            int n {0};
            std::cin >> n;
            events.push_back(n);
        }

        int balance {0};
        for (const auto e : events)
        {
            balance += (e) ? 1 : -1;
        }

        std::cout << "Case " << count++ << ": " << balance << "\n";
    }
}
