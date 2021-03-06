// Problem definition:
// https://uva.onlinejudge.org/external/6/679.pdf
// Accepted 2018-10-07

#include <iostream>
#include <cmath>

class Tree
{
public:
	Tree(const int depth) : m_depth { depth }, m_maxLabel { pow(2.0, m_depth) } {}
	int Traverse(const int numBalls);

private:
	int Traverse(const int nodeLabel, const int numBalls);

	const int m_depth;
	const double m_maxLabel;
};

int Tree::Traverse(const int numBalls)
{
	return Traverse(1, numBalls);
}

int Tree::Traverse(const int nodeLabel, const int numBalls)
{
    int leftLabel { nodeLabel * 2 };
    int rightLabel { leftLabel + 1 };

    if (leftLabel < m_maxLabel && rightLabel < m_maxLabel)
    {
        return (numBalls % 2) ? Traverse(leftLabel, numBalls / 2 + 1) :
            Traverse(rightLabel, numBalls / 2);
    }
    else
    {
        return nodeLabel;
    }
}

int main()
{
    int total;
    int depth;
    int numBalls;

    std::cin >> total;
    while (total--)
    {
        std::cin >> depth >> numBalls;
        Tree t { depth };
        std::cout << t.Traverse(numBalls) << "\n";
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
