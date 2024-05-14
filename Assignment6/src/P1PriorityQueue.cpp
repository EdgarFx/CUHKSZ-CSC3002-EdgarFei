/*
 * File: P1PriorityQueue.cpp
 * ---------------------------
 * This file contains a unit test of the PriorityQueue class.
 */

#include <iostream>
#include <sstream>
#include <string>
#include "P1PriorityQueue.h"
#include "strlib.h"
using namespace std;

int PriorityQueueTest() {
   PriorityQueue<string> pq;
   cout<<(pq.size()==0)<<endl;
   cout<<(pq.isEmpty())<<endl;
   pq.enqueue("A",1);
   cout<<(pq.isEmpty())<<endl;
   cout<<(pq.peek()=="A")<<endl;
   pq.enqueue("D", 3);
   pq.enqueue("C", 2);
   pq.enqueue("B", 1);
   cout<<(pq.peek()=="A")<<endl;
   cout<<(pq.size()==4)<<endl;
   cout<<pq.toString()<<endl;
   cout<<(pq.dequeue()=="A")<<endl;
   cout<<(pq.peek()=="B")<<endl;
   cout<<(pq.dequeue()=="B")<<endl;
   cout<<(pq.dequeue()=="C")<<endl;
   cout<<(pq.dequeue()=="D")<<endl;
   cout<<(pq.isEmpty())<<endl;
   return 0;
}
