// Problem definition: https://uva.onlinejudge.org/external/6/661.pdf
// Accepted 2019-02-05

#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <numeric>

int main()
{
    std::ios_base::sync_with_stdio(false);

    int devices {0};
    int operations {0};
    int capacity {0};
    int count {1};

    while (std::cin >> devices >> operations >> capacity && 
        !(devices == 0 && operations == 0 && capacity == 0))
    {
        std::vector<std::pair<int,bool>> state(devices);
        std::for_each(state.begin(), state.end(), [](std::pair<int,bool>& i) { std::cin >> i.first; i.second = false; });

        int toggle {0};
        int max {0};
        for (int i {0}; i < operations; ++i)
        {
            std::cin >> toggle;
            state[toggle-1].second = !state[toggle-1].second;
            auto total {std::accumulate(state.begin(), state.end(), 0, 
                [](int total, std::pair<int,bool>& i) { return i.second ? total + i.first : total; })};
            if (total > max) { max = total; }
        }

        std::cout << "Sequence " << count++ << "\n";
        if (max > capacity)
        {
            std::cout << "Fuse was blown.\n\n";
        }
        else
        {
            std::cout << "Fuse was not blown.\nMaximal power consumption was " << max << " amperes.\n\n";
        }
    }
}
