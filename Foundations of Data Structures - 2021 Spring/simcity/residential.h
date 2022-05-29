#include "cell.h"
#include "utility.h"

class Residential : public Cell 
{
    private:
        int activeWorkers;

    public: 

        Residential(int x, int y) : Cell (x, y, RES) {}
        Residential(int, int, int, int, int);

        void AttemptGrowth(int&, int&) override;
        char PrintCell() override;

};