/*
 * File: PriorityQueueUnitTest.cpp
 * -------------------------------
 * This file implements a simple test of the PriorityQueue class.
 */

#include <cassert>
#include <iostream>
#include <string>
#include "pqueue.h"
using namespace std;

/* pqueue test program */

int PriorityQueueUnitTest() {
   PriorityQueue<string> pq;
   assert(pq.size() == 0);
   assert(pq.isEmpty());
   pq.enqueue("A", 1);
   assert(!pq.isEmpty());
   assert(pq.peek() == "A");
   pq.enqueue("D", 3);
   pq.enqueue("C", 2);
   pq.enqueue("B", 1);
   assert(pq.peek() == "A");
   assert(pq.size() == 4);
   assert(pq.dequeue() == "A");
   assert(pq.peek() == "B");
   assert(pq.dequeue() == "B");
   assert(pq.dequeue() == "C");
   assert(pq.dequeue() == "D");
   assert(pq.isEmpty());
   cout << "Priority queue test succeeded" << endl;
   return 0;
}
