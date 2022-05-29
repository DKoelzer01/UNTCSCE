/**
 * Author:    Daniel Koelzer
 * Created:   11/1/2020
 **/
 
#include "fastmaxheap.hpp"
#include <stdio.h>
#include <iostream>

MaxHeap::MaxHeap() {}
MaxHeap::~MaxHeap() {}

void MaxHeap::swap(vector<int> &target,int a, int b){
	int temp = target[a];
	target[a] = target[b];
	target[b] = temp;
}

void MaxHeap::heapify(vector<int> &target,int index, int s) {
	int max, i, l, r;
	max = index;
	while(true) {
	i = max;
	l = ((max * 2) + 1);
	r = ((max * 2) + 2);
	if(l < s && target[l] > target[max])
		max = l;
	if(r < s && target[r] > target[max])
		max = r;
	if(max != i) {
		swap(target,i,max);
		continue;
	}
	return;
	}
	
}

void MaxHeap::heapsort(vector<int>& A,int n) {
	for(int i = (n / 2) - 1; i >= 0; i--) {
		heapify(A,i,n);
	}
	for(int i = n - 1; i > 0; i--) {
		swap(A,0,i);
		heapify(A,0,i);
	}
}
