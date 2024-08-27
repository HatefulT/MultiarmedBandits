#pragma once

#include <vector>
#include <tuple>
#include <random>

#include "BanditStrategy.hpp"

using namespace std;

class EpsilonGreedyStrategy : public BanditStrategy
{
    private:
        random_device rd;
        mt19937 gen;
        uniform_real_distribution<> uniform0_1;
        uniform_int_distribution<> uniform_int;

        double epsilon;

        // for each hand we save the number of its uses and the sample mean
        vector<pair<uint32_t, double>> estimations;

        uint32_t last_arm;

    public:
        EpsilonGreedyStrategy(uint32_t _arm_count, double _epsilon = 0.1)
            : BanditStrategy(_arm_count), epsilon(_epsilon),
            rd(), gen(rd()), uniform0_1(0., 1.), uniform_int(0, _arm_count - 1),
            estimations(_arm_count)
        {
            for (auto &est : estimations) {
                est = make_pair(0, 10000.);
            }
        }

        virtual uint32_t choose_arm()
        {
            double random_double = uniform0_1(gen);
            if (random_double > epsilon) {
                uint32_t max_estimation_index = 0;
                double max_estimation = estimations[0].second;

                for (uint32_t index = 1; index < estimations.size(); ++index) {
                    if (estimations[index].second > max_estimation) {
                        max_estimation = estimations[index].second;
                        max_estimation_index = index;
                    }
                }

                last_arm = max_estimation_index;
            } else {
                last_arm = static_cast<uint32_t>( uniform_int(gen) );
            }
            return last_arm;
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
