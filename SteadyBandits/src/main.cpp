#include <iostream>
#include <memory>

#include "Bandit.hpp"
#include "BanditStrategy.hpp"
#include "Strategies/GreedyStrategy.hpp"
#include "Strategies/EpsilonGreedyStrategy.hpp"
#include "BanditSimulator.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2) {
        cout << "Provide bandit filename" << endl;
        return 1;
    }

    string filename = argv[1];
    cout << "opening file " << filename << endl;

    Bandit b = load_bandit_from_file(filename);

    uint32_t turns_count = 100;

    BanditSimulator sim(b);

    sim.simulate(make_shared<GreedyStrategy>(b.get_arms_count()), turns_count);
    sim.save_data_to_file("greedy.txt");
    sim.clear_data();

    sim.simulate(make_shared<EpsilonGreedyStrategy>(b.get_arms_count()), turns_count);
    sim.save_data_to_file("epsilongreedy.txt");
    sim.clear_data();
}
