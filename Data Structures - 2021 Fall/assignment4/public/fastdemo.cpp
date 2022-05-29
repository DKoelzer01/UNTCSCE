/**
 * Author:    Daniel Koelzer
 * Created:   11/1/2020
 **/

#include "fastmaxheap.hpp"
#include <stdio.h>
#include <iostream>

int main(int argc, char*argv[]) {
  vector<int> A;
  if(argc!=2) {
    cout<<"Provide an input file as argument";
  } else {
    FILE *file = fopen(argv[1], "r");
    if(file == 0){
      cout << "ERROR: file does not exist" << endl;
      return -1;
    }
    else {
      int x;
      fscanf(file, "%d", &x);
      while(!feof(file)) {
	A.push_back(x);
	fscanf(file, "%d", &x);
      }
      fclose(file);
    }
  }
  
  int n = A.size();

  MaxHeap *myheap2 = new MaxHeap();
  myheap2->heapsort(A,n);

  delete myheap2;
  return 0;
}
