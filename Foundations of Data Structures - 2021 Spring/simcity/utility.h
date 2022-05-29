#ifndef UTILITY_H
#define UTILITY_H

#include "cell.h"

class Utility : public Cell
{
    private:
        bool powerLine;
        bool road;
        bool powerPlant;
    public:
        bool IsPowerLine() { return powerLine; }
        bool IsRoad() { return road; }
        bool IsPowerPlant() { return powerPlant; }

        Utility(int, int, bool, bool, bool);
        void AttemptGrowth(int&, int&) override{};
        char PrintCell() override;
};
#endif