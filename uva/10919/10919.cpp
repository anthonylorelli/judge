// Problem definition: https://uva.onlinejudge.org/external/109/10919.pdf
// Accepted 2019-02-09

#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <iterator>

int main()
{
    std::ios_base::sync_with_stdio(false);

    int courses {0};
    int categories {0};

    while (std::cin >> courses >> categories)
    {
        std::unordered_set<int> schedule;
        std::generate_n(std::inserter(schedule, schedule.end()), courses,
            []() { int n; std::cin >> n; return n; });

        bool qualified {true};
        int count {0}, min {0};
        while (categories--)
        {
            int taken {0}, id {0};
            std::cin >> count >> min;
            while (count--)
            {
                std::cin >> id;
                if (schedule.count(id) > 0) { taken++; }
            }

            if (taken < min) { qualified = false; }
        }

        std::cout << (qualified ? "yes" : "no") << "\n";
    }
}
