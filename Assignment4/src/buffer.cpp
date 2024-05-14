/*
 * File: buffer.cpp (list version without dummy cell)
 * --------------------------------------------------
 * This file implements the EditorBuffer class using a linked
 * list to represent the buffer.
 */

#include <iostream>
#include "buffer.h"
#include <string>
using namespace std;

/*
 * Implementation notes: EditorBuffer constructor
 * ----------------------------------------------
 * This function initializes an empty editor buffer, represented
 * as a doubly linked list.  In this implementation, the ends of
 * the linked list are joined to form a ring, with the dummy cell
 * at both the beginning and the end.  This representation makes
 * it possible to implement the moveCursorToEnd method in constant
 * time, and reduces the number of special cases in the code.
 */

EditorBuffer::EditorBuffer() {
   start = cursor = new Cell;
   start->next = start;
   start->prev = start;
}

/*
 * Implementation notes: EditorBuffer destructor
 * ---------------------------------------------
 * The destructor must delete every cell in the buffer.  Note
 * that the loop structure is not exactly the standard idiom for
 * processing every cell within a linked list, because it is not
 * legal to delete a cell and later look at its next field.
 */

EditorBuffer::~EditorBuffer() {
   //TODO
    Cell *cp=start;
    while (cp!=start){
        cp=cp->next;
        delete cp->prev;
    }
    delete cp;
}

/*
 * Implementation notes: cursor movement
 * -------------------------------------
 * In a doubly linked list, each of these operations runs in
 * constant time.
 */

void EditorBuffer::moveCursorForward() {
    if (cursor->next != start) {
      cursor = cursor->next;
   }
}

void EditorBuffer::moveCursorBackward() {
   //TODO
    if (cursor != start) {
        cursor = cursor->prev;
    }
}

void EditorBuffer::moveCursorToStart() {
   //TODO
    cursor = start;
}

void EditorBuffer::moveCursorToEnd() {
   //TODO
    cursor = start->prev;
}

/*
 * Implementation notes: insertCharacter, deleteCharacter
 * ------------------------------------------------------
 * This code is much like that used for the traditional linked
 * list except that more pointers need to be updated.
 */

void EditorBuffer::insertCharacter(char ch) {
    //TODO
    Cell *cp=new Cell;
    cp->ch=ch;
    cp->next=cursor->next;
    cp->prev=cursor;
    cursor->next->prev=cp;
    cursor->next=cp;
    cursor=cp;
}

void EditorBuffer::deleteCharacter() {
    //TODO
    if (cursor->next!=start){
    cursor->next=cursor->next->next;
    delete cursor->next->prev;
    cursor->next->prev=cursor;
    }
}

/*
 * Implementation notes: getText and getCursor
 * -------------------------------------------
 * The getText method uses the standard linked-list pattern to loop
 * through the cells in the linked list.  The getCursor method counts
 * the characters in the list until it reaches the cursor.
 */

string EditorBuffer::getText() const {
    //TODO
    string res="";
    Cell *cp=start->next;
    while (cp!=start){
        res+=cp->ch;
        cp=cp->next;
    }
    return res;
}

int EditorBuffer::getCursor() const {
   //TODO
    int i=0;
    Cell *cp=start;
    while (cp!=cursor){
        i++;
        cp=cp->next;
    }
    return i;
}
