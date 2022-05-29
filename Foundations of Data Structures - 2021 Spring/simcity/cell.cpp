#include "cell.h"

Cell::Cell(int x, int y, CellType type)
{
	this->type = type;
    this->xPos = x;
    this->yPos = y; 
    this->population = 0;
    this->pollution = 0;
    this->active = true;
	this->updated = false;
	this->roadAccess = false;
}
Cell::Cell(int x, int y, int pop, int pol, CellType type)
{
	this->type = type;
    this->xPos = x;
    this->yPos = y; 
    this->population = pop;
    this->pollution = pol;
    this->active = true;
	this->updated = false;
	this->roadAccess = false;
}


void Cell::AddPopulation(int val = 1) 
{
    this->population += val;
}
void Cell::AddPollution(int val)
{
	if(this->pollution < val)
		this->pollution = val;
    
}

bool CompareCells(Cell* a, Cell* b)
{
    if(a == b)
        return false;

    //  Utility cells are lowest priority
    if(a->GetType() == UTIL && b->GetType() != UTIL)
        return true;
    if(a->GetType() != UTIL && b->GetType() == UTIL)
        return false;

    // Prioritize commercial zones over industrial
    if(a->GetType() == COM && b->GetType() == IND)
        return false;    
    if(a->GetType() == IND && b->GetType() == COM)
        return true;

    //  Prioritize greater population
    if(a->GetPopulation() != b->GetPopulation())
    {
        return a->GetPopulation() < b->GetPopulation();
    }

    //  Get total adjacent population
    int thisPop = 0;
    int otherPop = 0;
    for (int i = 0; i < a->GetAdjacent().size(); i++) 
    {
        thisPop += a->GetAdjacent()[i]->GetPopulation();
    }
    for (int i = 0; i < b->GetAdjacent().size(); i++)
    {
        otherPop += b->GetAdjacent()[i]->GetPopulation();
    }
    //  Prioritize greater surrounding population
    if(thisPop != otherPop)
        return thisPop < otherPop;

    //  Prioritize smaller x and y values.
	if (a->GetXPos() != b->GetXPos())
		return a->GetXPos() > b->GetXPos();
	
	if(a->GetYPos() != b->GetYPos())
        return a->GetYPos() > b->GetYPos();

    

    return false;
}