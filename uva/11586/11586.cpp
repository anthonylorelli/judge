// Problem definition: https://uva.onlinejudge.org/external/115/11586.pdf
// Accepted 2019-02-10

#include <iostream>
#include <string>
#include <algorithm>

int main()
{
    std::ios_base::sync_with_stdio(false);

    int cases {0};
    std::cin >> cases;

    std::string input;
    std::getline(std::cin, input);

    while (cases--)
    {
        int m {0}, f{0};
        std::getline(std::cin, input);
        std::for_each(input.begin(), input.end(), 
            [&](const char c) { if (c == 'M') { m++; } else if (c == 'F') { f++; }});
        std::cout << ((m == f && m > 1) ? "LOOP" : "NO LOOP") << "\n";
    }
}
