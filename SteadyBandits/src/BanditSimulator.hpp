#pragma once

#include <fstream>
#include <vector>
#include <string>

#include "Bandit.hpp"
#include "BanditStrategy.hpp"

using namespace std;

class BanditSimulator
{
    private:
        Bandit bandit;

        vector<double> rewards;

    public:
        BanditSimulator(Bandit _bandit) :
            bandit(_bandit) {}

        void simulate(shared_ptr<BanditStrategy> strategy, uint32_t steps)
        {
            for (uint32_t time_step = 0; time_step < steps; ++time_step) {
                uint32_t action_t = strategy->choose_arm();
                double reward_t = bandit.get_reward(action_t);
                strategy->set_last_reward(reward_t);

                rewards.push_back(reward_t);
            }
        }

        void save_data_to_file(string filename)
        {
            ofstream file(filename);

            file << rewards.size() << endl;
            
            for (auto &reward_t : rewards)
                file << reward_t << endl;
        }

        void clear_data()
        {
            rewards.clear();
        }
};
