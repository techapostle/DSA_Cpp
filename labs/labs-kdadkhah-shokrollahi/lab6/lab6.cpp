#include <cstdlib>
#include <iostream>
#include <fstream>


using namespace std;

void push_heap(int a[], int size) {
  for (auto i = size - 1;;) {
    const auto parent = (i - 1) / 2;
    const auto ai = a[i], ap = a[parent];
    if (ap <= ai)
      break;
    a[parent] = ai;
    a[i] = ap;
    if (parent == 0)
      break;
    i = parent;
  }
}

template<typename It>
void make_heap(const It a, int size) {
  int firstParent = (size - 3) / 2;
  int firstRightChild = (firstParent + 1) * 2;
  for (;; --firstParent, firstRightChild -= 2) {
    const auto lucifer = a[firstParent];
    auto parent = firstParent;
    auto rightChild = firstRightChild;
    for (;;) {
     const auto jr = rightChild - (a[rightChild-1] <= a[rightChild]);
     const auto crt = a[jr];
     if (lucifer <= crt)
       break;
     a[parent] = crt;
     parent = jr;
     rightChild = (jr + 1) * 2;
     if (rightChild >= size)
       goto write;
    }
    if (parent != firstParent)
      write: a[parent] = lucifer;
    if (firstParent == 0)
      break;
  }
  if (size & 1)
    return;
  push_heap(a, size);
}

void insertionSortStandard(int [], int);

/*Only modify this function*/
void insertionSortModified(int arr[],int size){
  if (size < 3) {
    insertionSortStandard(arr, size);
    return;
  }
  make_heap(arr, size);
  insertionSortStandard(arr, size);
}


/*performs the insertion sort algorithm on array from index
left to index right inclusive.  You don't need to change this function*/
void insertionSortStandard(int arr[], int size){
   int curr;
   int i, j;
   for(i=1;i<size;i++){
      curr=arr[i];
      for(j=i;j>0 && arr[j-1] > curr;j--){
         arr[j]=arr[j-1];
      }
      arr[j]=curr;
   }
}

