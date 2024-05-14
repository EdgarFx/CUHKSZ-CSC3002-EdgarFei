/*
 * File: pqueue.h
 * --------------
 * This file exports the PriorityQueue class, a collection in which values
 * are processed in priority order.
 */

#ifndef _pqueue_h
#define _pqueue_h

#include "vector.h"
#include "error.h"
using namespace std;

/*
 * Class: PriorityQueue<ValueType>
 * -------------------------------
 * This class models a structure called a priority queue in which values
 * are processed in order of priority.  As in conventional English usage,
 * lower priority numbers correspond to higher effective priorities, 
 * so that a priority 1 item takes precedence over a priority 2 item.
 */
int PriorityQueueTest();

template <typename ValueType>
class PriorityQueue {

public:

/*
 * Constructor: PriorityQueue
 * Usage: PriorityQueue<ValueType> pq;
 * -----------------------------------
 * Initializes a new priority queue, which is initially empty.
 */

   PriorityQueue();

/*
 * Destructor: ~PriorityQueue
 * --------------------------
 * Frees any heap storage associated with this priority queue.
 */

   virtual ~PriorityQueue();



/*
 * Method: size
 * Usage: int n = pq.size();
 * -------------------------
 * Returns the number of values in the priority queue.
 */

   int size() const;

/*
 * Method: isEmpty
 * Usage: if (pq.isEmpty()) ...
 * ----------------------------
 * Returns true if the priority queue contains no elements.
 */

   bool isEmpty() const;

/*
 * Method: clear
 * Usage: pq.clear();
 * ------------------
 * Removes all elements from the priority queue.
 */

   void clear();

/*
 * Method: enqueue
 * Usage: pq.enqueue(value, priority);
 * -----------------------------------
 * Adds value to the queue with the specified priority.  
 * Lower priority numbers correspond to higher priorities, 
 * which means that all 
 * priority 1 elements are dequeued before any priority 2 elements.
 */

   void enqueue(ValueType value, double priority);

/*
 * Method: dequeue
 * Usage: ValueType first = pq.dequeue();
 * --------------------------------------
 * Removes and returns the highest priority value.  
 * If multiple entries in
 * the queue have the same priority, 
 * those values are dequeued in the same
 * order in which they were enqueued.
 */

   ValueType dequeue();

/*
 * Method: peek
 * Usage: ValueType first = pq.peek();
 * -----------------------------------
 * Returns the value of highest priority in the queue, without removing it.
 */

   ValueType peek() const;

/*
 * Method: peekPriority
 * Usage: double priority = pq.peekPriority();
 * -------------------------------------------
 * Returns the priority of the first element in the queue, 
 * without removing it.
 */

   double peekPriority() const;

/*
 * Method: toString
 * Usage: string str = pq.toString();
 * ----------------------------------
 * Converts the queue to a printable string representation.
 */

   std::string toString();

/* Private section */

/**********************************************************************/
/* Note: Everything below this point in the file is logically part    */
/* of the implementation and should not be of interest to clients.    */
/**********************************************************************/

/*
 * Implementation notes: PriorityQueue data structure
 * --------------------------------------------------
 * The PriorityQueue class is implemented using a data structure called a
 * heap.
 */

private:

/* Type used for each heap entry */

   struct HeapEntry {
      ValueType value;

      double priority;

      long sequence; 
      /* order of enqueue, which used for recording the order of which the elements are inserted, 
       * i.e.: when two elements are of the same priority,
       * it depends on the order of the sequence that
       * the first inserted element should be dequeued first
       */ 

   };

/* Instance variables */

   Vector<HeapEntry> heap;
   long enqueueCount; // to record the sequence
   int count;         // to record the number of elements in the PriorityQueue
   int capacity;      // capacity of the heap

/* Private function prototypes */

   void enqueueHeap(ValueType & value, double priority); 
   ValueType dequeueHeap();
   bool takesPriority(int i1, int i2);
   void swapHeapEntries(int i1, int i2);

};


template <typename ValueType>
PriorityQueue<ValueType>::PriorityQueue() {
   clear();
}

/*
 * Implementation notes: ~PriorityQueue destructor
 * -----------------------------------------------
 * All of the dynamic memory is allocated in the Vector class, so no work
 * is required at this level.
 */

template <typename ValueType>
PriorityQueue<ValueType>::~PriorityQueue() {
   /* Empty */
}

template <typename ValueType>
int PriorityQueue<ValueType>::size() const {
   /* TODO */
    return heap.size();
}

template <typename ValueType>
bool PriorityQueue<ValueType>::isEmpty() const {
   /* TODO */
    return heap.size()==0;
}

template <typename ValueType>
void PriorityQueue<ValueType>::clear() {
   /* TODO */
    heap.clear();
}

template <typename ValueType>
void PriorityQueue<ValueType>::enqueue(ValueType value, double priority) {
   /* TODO */
    int now=heap.size();
    HeapEntry element;
    element.value=value;
    element.priority=priority;
    this->enqueueCount++;
    this->count++;
    element.sequence=this->enqueueCount;
    heap.push_back(element);
    while (takesPriority(now,(now-1)/2)&&now!=0){
        swapHeapEntries(now,(now-1)/2);
        now=(now-1)/2;
    }
}

/*
 * Implementation notes: dequeue, peek, peekPriority
 * -------------------------------------------------
 * These methods must check for an empty queue and report an error if there
 * is no first element.
 */

template <typename ValueType>
ValueType PriorityQueue<ValueType>::dequeue() {
   /* TODO */
    if(heap.size()==0){
        throw "The queue is empty!";
    }
    HeapEntry first=heap[0];
    heap[0]=heap.back();
    heap.pop_back();
    int now=0;
    while(true){
        if((2*now+1)>=heap.size()||(2*now+2)>=heap.size()){
            break;
        }
        if(takesPriority(2*now+1,2*now+2)){
            if(!takesPriority(now,2*now+1)){
                swapHeapEntries(now,2*now+1);
                now=2*now+1;
            }else{
                break;
            }
        }else{
            if(!takesPriority(now,2*now+2)){
                swapHeapEntries(now,2*now+2);
                now=2*now+2;
            }else{
                break;
            }
        }
    }
    this->count--;
    return first.value;
}

template <typename ValueType>
ValueType PriorityQueue<ValueType>::peek() const {
  /* TODO */
    if(heap.size()==0){
        throw "The queue is empty!";
    }
    return heap[0].value;
}

template <typename ValueType>
double PriorityQueue<ValueType>::peekPriority() const {
   /* TODO */
    if(heap.size()==0){
        throw "The queue is empty!";
    }
    return heap[0].priority;
}

template <typename ValueType>
bool PriorityQueue<ValueType>::takesPriority(int i1, int i2) {
   /* compare the priority of two elements，
    * when their priorities are equal, comparing based on the sequence */
   /* TODO */
    if(heap[i1].priority<heap[i2].priority){
        return true;
    }else if(heap[i1].priority==heap[i2].priority){
        return heap[i1].sequence<heap[i2].sequence;
    }else{
        return false;
    }
}

template <typename ValueType>
void PriorityQueue<ValueType>::swapHeapEntries(int i1, int i2) {
   /* TODO */
    HeapEntry temp;
    temp=heap[i2];
    heap[i2]=heap[i1];
    heap[i1]=temp;
}

template <typename ValueType>
std::string PriorityQueue<ValueType>::toString() {
  /* convert the PriorityQueue into a printable String */
  /* TODO */
    string res="";
    for(int i=0;i<heap.size();i++){
        res+=heap[i].value;
    }
    return res;
}

template <typename ValueType>
std::ostream & operator<<(std::ostream & os,
                          const PriorityQueue<ValueType> & pq) {
   /* give the output of all the elements in queue(not dequeue)
    * i.e.: cout << pq gives the output of all the content in current queue without change pq */
   /* TODO */
    string res=pq.toString();
    return os << res << endl;
}

#endif
