#pragma once
#include <vector>
#include <string>
#include <fstream>

#include <memory>

#include "BanditArm.hpp"

using namespace std;

class Bandit
{
    private:
        vector<shared_ptr<BanditArm>> arms;

        uint32_t time;

    public:
        Bandit() {}

        void add_arm(shared_ptr<BanditArm> arm) 
        {
            arms.push_back(arm);

            // cout << arms[arms.size() - 1]->get_mean() << "; "
            //     << arms[arms.size() - 1]->get_reward() << endl;
        }

        uint32_t get_arms_count() const
        {
            return arms.size();
        }

        double get_reward(uint32_t arm_index)
        {
            return arms[arm_index]->get_reward();
        }

        void save_to_file(string filename) const
        {
            ofstream file(filename);

            file << get_arms_count() << endl;
            
            for (auto &arm : arms)
                file << arm->get_mean() << " " << arm->get_stddev() << endl;
        }
};

Bandit load_bandit_from_file(string filename)
{
    Bandit out;

    ifstream file(filename);
    if (not file.is_open()) {
        cout << "Error: cannot open the file" << endl;
        return out;
    }

    uint32_t arms_count;
    file >> arms_count;

    double mean, stddev;
    for (uint32_t i = 0; i < arms_count; ++i) {
        file >> mean;
        file >> stddev;
        out.add_arm(make_shared<BanditArm>(mean, stddev));
    }

    return out;
}
