// Problem definition: https://uva.onlinejudge.org/external/122/12250.pdf
// Accepted 2019-01-15

#include <iostream>
#include <string>

int main()
{
    std::ios_base::sync_with_stdio(false);

    std::string s;
    int count {1};

    while (std::cin >> s && s[0] != '#')
    {
        std::string language = (s == "HELLO") ? "ENGLISH" :
            (s == "HOLA") ? "SPANISH" : (s == "HALLO") ? "GERMAN" :
            (s == "BONJOUR") ? "FRENCH" : (s == "CIAO") ? "ITALIAN" :
            (s == "ZDRAVSTVUJTE") ? "RUSSIAN" : "UNKNOWN";
        std::cout << "Case " << count++ << ": " << language << "\n";
    }
}
