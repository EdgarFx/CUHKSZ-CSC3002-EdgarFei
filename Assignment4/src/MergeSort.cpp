/*
 * File: MergeSort.cpp
 * -------------------
 * This file implements the merge sort algorithm using arrays rather
 * than vectors.
 */

#include <iostream>
using namespace std;

/* Function prototypes */

void sort(int array[], int n);
void printArray(int array[], int n);

/* Test program */

int test3() {
   int array[] = { 56, 25, 37, 58, 95, 19, 73, 30 };
   sort(array, 8);
   printArray(array, 8);
   return 0;
}

/*
 * Function: sort
 * Usage: sort(array, n);
 * ----------------------
 * Sorts the first n elements of the vector into increasing order using
 * the merge sort algorithm, which consists of the following steps:
 *
 * 1. Copy the array into an array allocated on the stack.
 * 2. Divide the new array into two halves by manipulating the indices.
 * 3. Sort each half of the array recursively
 * 4. Merge the two halves back into the original one.
 */

void sort(int array[], int n) {
   //TODO
    if (n<=1) {return;}
    int mid=n/2;
    int temp[n];
    for (int i=0;i<n;i++){
        temp[i]=array[i];
    }
    sort(temp,mid);
    sort(&temp[mid],n-mid);
    int s1=0, s2=mid, i=0;
    while (s1<mid && s2<n){
        if (temp[s1]<temp[s2]){
            array[i++]=temp[s1++];
        }else{
            array[i++]=temp[s2++];
        }
    }
    while (s1<mid) {array[i++]=temp[s1++];}
    while (s2<n) {array[i++]=temp[s2++];}
}

/*
 * Function: printArray
 * Usage: printArray(array, n);
 * ----------------------------
 * Prints the elements of the array on a single line with the elements
 * enclosed in braces and separated by commas.
 */

void printArray(int array[], int n) {
   cout << "{ ";
   for (int i = 0; i < n; i++) {
      if (i > 0) cout << ", ";
      cout << array[i];
   }
   cout << " }" << endl;
}
