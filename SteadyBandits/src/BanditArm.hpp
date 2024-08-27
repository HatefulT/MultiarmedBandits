#pragma once
#include <random>

using namespace std;

/* Let all bandit arms be normal distributed */

class BanditArm
{
    private:
        random_device rd;
        mt19937 gen;
        normal_distribution<> dist;

        double mean, stddev;

    public:
        BanditArm(double _mean, double _stddev)
            : rd(), gen(rd()), mean(_mean), stddev(_stddev)
        {
            dist = normal_distribution<>(mean, stddev);
            // cout << mean << " " << stddev << "; " << dist.mean() << " " << dist.stddev() << endl;
        }

        // BanditArm(const BanditArm &arm)
        //     : rd(), gen(rd()),
        //     mean(arm.mean), stddev(arm.stddev), dist(mean, stddev) {
        // }

        double get_reward()
        {
            // cout << dist.mean() << " " << dist.stddev() << endl;
            return dist(gen);
        }

        double get_mean() const
        {
            return dist.mean();
        }

        double get_stddev() const
        {
            return dist.stddev();
        }
};
