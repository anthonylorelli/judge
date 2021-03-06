// Problem definition: https://uva.onlinejudge.org/external/5/573.pdf
// Accepted 2019-02-04

#include <iostream>
#include <tuple>

class Simulation
{
public:
    Simulation(int height, double fatigue) : m_height{height}, m_fatigue{fatigue} {}
    std::pair<bool,int> Climb(double dayDistance, int nightDistance);

private:
    int m_height;
    double m_fatigue;
};

std::pair<bool,int> Simulation::Climb(double dayDistance, int nightDistance)
{
    double cumulative {0.0};
    double currentSpeed {dayDistance};
    
    for (int day {1}; ; ++day)
    {
        cumulative += currentSpeed;
        if (cumulative > m_height)
        {
            return std::make_pair(true, day);
        }

        cumulative -= nightDistance;
        if (cumulative < 0)
        {
            return std::make_pair(false, day);
        }

        currentSpeed -= (m_fatigue);
        if (currentSpeed < 0.0) { currentSpeed = 0.0; }
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    int height {0};
    double dayDistance {0.0};
    int nightDistance {0};
    double fatigue {0.0};

    while (std::cin >> height >> dayDistance >> nightDistance >> fatigue && height != 0)
    {
        double loss {dayDistance * (fatigue / 100.0)};
        Simulation s(height, loss);
        auto result {s.Climb(dayDistance, nightDistance)};

        const char* condition {result.first ? "success" : "failure"};
        std::cout << condition << " on day " << result.second << "\n";
    }
}
