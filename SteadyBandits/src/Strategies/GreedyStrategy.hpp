#pragma once

#include <vector>
#include <tuple>

#include "BanditStrategy.hpp"

using namespace std;

class GreedyStrategy : public BanditStrategy
{
    private:
        // for each hand we save the number of its uses and the sample mean
        vector<pair<uint32_t, double>> estimations;

        uint32_t last_arm;

    public:
        GreedyStrategy(uint32_t _arm_count)
            : BanditStrategy(_arm_count),
            estimations(_arm_count)
        {
            for (auto &est : estimations) {
                est = make_pair(0, 10000.);
            }
        }

        virtual uint32_t choose_arm()
        {
            uint32_t max_estimation_index = 0;
            double max_estimation = estimations[0].second;

            for (uint32_t index = 1; index < estimations.size(); ++index) {
                if (estimations[index].second > max_estimation) {
                    max_estimation = estimations[index].second;
                    max_estimation_index = index;
                }
            }

            last_arm = max_estimation_index;
            return max_estimation_index;
        }

        virtual void set_last_reward(double reward) {
            if (estimations[last_arm].first == 0) {
                estimations[last_arm].first = 1;
                estimations[last_arm].second = reward;
            } else {
                uint32_t N = estimations[last_arm].first;
                double last_estimation = estimations[last_arm].second;
                estimations[last_arm].second = last_estimation + ( reward - last_estimation ) / N;
                estimations[last_arm].first += 1;
            }
        }
};
