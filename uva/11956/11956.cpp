// Problem definition: https://uva.onlinejudge.org/external/119/11956.pdf
// Accepted 2019-02-16

#include <iostream>
#include <string>
#include <array>
#include <iomanip>

int main()
{
    std::ios_base::sync_with_stdio(false);
    constexpr int size {100};

    int count {1};
    int cases {0};
    std::cin >> cases;

    while (cases--)
    {
        std::array<unsigned char,size> memory{0};
        unsigned int ip {0};

        std::string instructions;
        std::cin >> instructions;

        for (const auto i : instructions)
        {
            switch (i)
            {
                case '>':
                    ip = (ip + 1) % 100;
                    break;
                case '<':
                    ip = (ip == 0) ? 99 : ip - 1;
                    break;
                case '+':
                    memory[ip]++;
                    break;
                case '-':
                    memory[ip]--;
                    break;
                case '.':
                    //std::cout << memory[ip];
                    break;
                default:
                    break;
            }
        }

        std::cout << "Case " << std::dec << count++ << ":";
        std::cout << std::hex << std::uppercase;
        for (const auto b : memory)
        {
            std::cout << " " << std::setfill('0') << std::setw(2) << static_cast<unsigned int>(b);
        }
        std::cout << "\n";
    }
}
