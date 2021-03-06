// Problem definition: https://uva.onlinejudge.org/external/103/10324.pdf
// Accepted 2019-02-07

#include <iostream>
#include <string>
#include <algorithm>

int main()
{
    std::ios_base::sync_with_stdio(false);

    std::string sequence;
    int count {1};

    while (std::cin >> sequence)
    {
        int ranges {0};
        std::cin >> ranges;

        std::cout << "Case " << count++ << ":\n";
        int start {0};
        int end {0};
        while (ranges--)
        {
            std::cin >> start >> end;
            if (start > end) { std::swap(start, end); }
            char first {sequence[start]};
            auto result {std::all_of(std::begin(sequence)+start, std::begin(sequence)+end+1,
                [&](char c) { return c == first; })};
            std::cout << (result ? "Yes\n" : "No\n");
        }
    }
}
