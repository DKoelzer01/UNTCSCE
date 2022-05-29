/* 
 Author: Daniel Koelzer (danielkoelzer@my.unt.edu)
 Date: 3/2/2020
 Description: God has abandoned us.
*/

#include <iostream>
#include <cstring>
using namespace std;int main() {int i = 0;a: if(i < 100) { if(i%5 == 0) { cout << "Fives " << i << endl; i++; goto b; } else if ( i % 2 == 0) { cout << "Evens " << i << endl; i++; goto a; } else { cout << i << endl; i++; goto a; }}goto c;b: do{cout << "1 2 3 4 5\n";goto a;}while(0==1);c:return 0;}
