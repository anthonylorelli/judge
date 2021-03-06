// Problem definition: https://uva.onlinejudge.org/external/101/10114.pdf
// Accepted 2019-01-21

#include <iostream>
#include <tuple>
#include <vector>

int main()
{
    std::ios_base::sync_with_stdio(false);

    int duration {0};
    float downPayment {0.0};
    float loan {0.0};
    int records {0};

    while ((std::cin >> duration >> downPayment >> loan >> records) && duration >= 0)
    {
        std::vector<std::pair<int,float>> months;
        int monthNumber {0};
        float depreciation {0.0};

        while (records--)
        {
            std::cin >> monthNumber >> depreciation;
            months.push_back(std::make_pair(monthNumber, depreciation));
        }

        float carValue {loan + downPayment};
        float currentDepreciation {months[0].second};
        carValue -= (carValue * currentDepreciation);
        float monthlyPayment {loan / duration};
        int monthIndex {0};
        size_t depreciationIndex {1};

        while (loan >= carValue)
        {
            ++monthIndex;
            if (depreciationIndex < months.size() && months[depreciationIndex].first == monthIndex)
            {
                currentDepreciation = months[depreciationIndex++].second;
            }

            loan -= monthlyPayment;
            carValue -= (carValue * currentDepreciation);
        }

        std::cout << monthIndex << " month" << ((monthIndex == 1) ? "\n" : "s\n");
    }
}
