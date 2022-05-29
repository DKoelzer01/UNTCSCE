#include "cell.h"
#include "utility.h"


class Industrial : public Cell 
{
    private:
        int availableGoods;

    public: 

        Industrial(int x, int y) : Cell (x, y, IND) {}
        Industrial(int, int, int, int, int);

        void AttemptGrowth(int&, int&) override;
        char PrintCell() override;
        void Pollute(int, int, Cell***);

};