#include "utility.h"

Utility::Utility(int x, int y, bool pl, bool rd, bool pp) : Cell(x, y, UTIL)
{
    this->powerLine = pl;
    this->road = rd;
    this->powerPlant = pp;
	this->type = UTIL;
}

char Utility::PrintCell()
{
    if(road && powerLine)
        return '#';
    else if(road)
        return '-';
    else if(powerLine)
        return 'T';
    else if(powerPlant)
        return 'P';
    else
        return ' ';
}