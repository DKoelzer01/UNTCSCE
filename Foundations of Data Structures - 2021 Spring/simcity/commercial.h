#include "cell.h"
#include "utility.h"


class Commercial : public Cell 
{
    private:

    public: 

        Commercial(int x, int y) : Cell (x, y, COM) {}
        Commercial(int, int, int, int);

        void AttemptGrowth(int&, int&) override;
        char PrintCell() override;

};