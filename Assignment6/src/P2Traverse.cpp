/*
 * File: TraverseTest.cpp
 * ------------------
 * This program reimplements the depth-first search algorithm using an
 * explicit stack
 * or
 * reimplements the breadth-first search algorithm using an
 * explicit queue.
 */

#include <iostream>
#include <fstream>
#include <string>
#include "set.h"
#include "simplegraph.h"
#include "stack.h"
#include "queue.h"
#include "foreach.h"
#include "vector.h"

using namespace std;

/* Main program */
void dfs(Node *start);
void bfs(Node *start);

int TraverseTest() {
   SimpleGraph airline;
   ifstream infile("AirlineGraph.txt");
   readGraph(airline, infile);
   dfs(airline.nodeMap.get("Portland"));
   bfs(airline.nodeMap.get("Portland"));
   return 0;
}

void dfs(Node *start) {
   /* TODO */
   /* make sure that your implemantation is based on an explicit Stack */
    Stack<Node> s;
    s.push(*start);
    Vector<string> v;
    v.push_back((*start).name);
    while(!s.isEmpty()){
        Node temp=s.pop();
        if(!temp.arcs.isEmpty()){
            for (Set<Arc *>::iterator it=temp.arcs.begin();it!=temp.arcs.end();it++){
                Node *now=(*it)->finish;
                if(std::find(v.begin(),v.end(),now->name)==v.end()){
                    s.push(*now);
                    v.push_back(now->name);
                }
            }
        }
        cout<<temp.name<<endl;
    }
}

void bfs(Node *start) {
    /* TODO */
   /* make sure that your implemantation is based on an explicit Queue */
    Queue<Node> q;
    q.enqueue(*start);
    Vector<string> v;
    v.push_back((*start).name);
    while(!q.isEmpty()){
        Node temp=q.dequeue();
        if(!temp.arcs.isEmpty()){
            for (Set<Arc *>::iterator it=temp.arcs.begin();it!=temp.arcs.end();it++){
                Node *now=(*it)->finish;
                if(std::find(v.begin(),v.end(),now->name)==v.end()){
                    q.enqueue(*now);
                    v.push_back(now->name);
                }
            }
        }
        cout<<temp.name<<endl;
    }
}
