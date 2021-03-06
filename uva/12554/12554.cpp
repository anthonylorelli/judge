// Problem definition: https://uva.onlinejudge.org/external/125/12554.pdf
// Accepted ?

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::ios_base::sync_with_stdio(false);

    std::vector<std::string> song { "Happy", "birthday", "to", "you", "Happy", 
        "birthday", "to", "you", "Happy",  "birthday", "to", "Rujia", "Happy", 
        "birthday", "to", "you"};

    int participants {0};
    std::cin >> participants;
    std::vector<std::string> names(participants);
    std::for_each(std::begin(names), std::end(names), [](std::string& s) { std::cin >> s; });

    size_t songLoops {(song.size() >= names.size()) ? 1 :
        (names.size() / song.size()) + 1};

    for (size_t i {0}, currentName {0}; i < songLoops; ++i)
    {
        for (auto& w : song)
        {
            std::cout << names[currentName] << ": " << w << "\n";
            currentName = (currentName + 1) % names.size();
        }
    }
}
