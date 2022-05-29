/**
 * Author:    Daniel Koelzer
 * Created:   11/1/2020
 **/

#include <vector>
using namespace std;

class MaxHeap {
private:
  vector<int> arr;
  void heapify(vector<int> &target,int index,int s);
  
public:
  MaxHeap();
  ~MaxHeap();
  void swap(vector<int> &target,int a, int b);
  void heapsort(vector<int>& A,int n);
};
