// Problem definition: https://uva.onlinejudge.org/external/122/12289.pdf
// Accepted 2019-01-20

#include <iostream>
#include <string>

int main()
{
    std::ios_base::sync_with_stdio(false);

    int cases {0};
    std::cin >> cases;

    while (cases--)
    {
        std::string word;
        std::cin >> word;

        int value {0};

        if (word.size() == 5)
        {
            value = 3;
        }
        else if ((word[0] == 'o' && word[1] == 'n') ||
            (word[0] == 'o' && word[2] == 'e') ||
            (word[1] == 'n' && word[2] == 'e'))
        {
            value = 1;
        }
        else
        {
            value = 2;
        }

        std::cout << value << '\n';
    }
}
