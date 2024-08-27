#pragma once

class BanditStrategy
{
    private:
        uint32_t arm_count;

    public:
        BanditStrategy(uint32_t _arm_count) :
            arm_count(_arm_count) {}

        virtual uint32_t choose_arm() = 0;

        virtual void set_last_reward(double reward) = 0;
};
