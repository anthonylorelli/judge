// Problem definition: https://uva.onlinejudge.org/external/125/12577.pdf
// Accepted 2019-01-21

#include <iostream>
#include <string>

int main()
{
    std::ios_base::sync_with_stdio(false);

    std::string input;
    std::string type;
    int count {1};

    while (std::cin >> input && input[0] != '*')
    {
        type = input == "Hajj" ? "Hajj-e-Akbar" : "Hajj-e-Asghar";
        std::cout << "Case " << count++ << ": " << type << "\n";
    }
}
