#include "major1.h"

void rotateRight(unsigned int x, int y)
{
	unsigned int rotated_final_value = (x >> y) | (x << (32 - y));
	printf("%u rotated by %d position(s) gives: %u\n", x, y, rotated_final_value);
}