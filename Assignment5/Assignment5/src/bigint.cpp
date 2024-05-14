/*
 * File: bigint.cpp
 * ----------------
 * This file implements the bigint.h interface.
 */

#include <cctype>
#include <string>
#include "bigint.h"
#include "error.h"
using namespace std;

/*
 * Implementation notes: BigInt constructor
 * ----------------------------------------
 * The code for this constructor offers a minimal implementation
 * that matches what we would expect on an exam.  In a more
 * sophisticated implementation, it would make sense to include
 * a test to avoid storing leading zeros in the linked list.  In
 * this implementation, calling BigInt("00042") creates a
 * BigInt with a different internal representation than
 * BigInt("42"), which is probably a bad idea.
 */

BigInt::BigInt(string str) {
    //TODO
    int length=str.length();
    Cell *first=new Cell;
    first->finalDigit=str.at(length-1)-'0';
    first->leadingDigits=nullptr;
    start=first;
    for(int i=length-2;i>=0;i--){
        Cell *pt=new Cell;
        pt->finalDigit=str.at(i)-'0';
        pt->leadingDigits=nullptr;
        first->leadingDigits=pt;
        first=pt;
    }
}

/*
 * Implementation notes: BigInt destructor
 * ---------------------------------------
 * The code for the destructor is similar to that of the other
 * classes that contain a linked list.  You need to store the
 * pointer to the next cell temporarily so that you still have
 * it after you delete the current cell.
 */

BigInt::~BigInt() {
    //TODO
    Cell *pt1=start;
    Cell *pt2;
    while(pt1!=nullptr){
        pt2=pt1;
        pt1=pt1->leadingDigits;
        delete pt2;
    }
}

/*
 * Implementation notes: toString
 * ------------------------------
 * This method could also be written as a wrapper method that
 * calls a recursive function that creates the reversed string
 * one character at a time.
 */

string BigInt::toString() const {
    //TODO
    string str="";
    Cell *pt=start;
    str+=to_string(pt->finalDigit);
    pt=pt->leadingDigits;
    while(pt!=nullptr){
        str.insert(0,to_string(pt->finalDigit));
        pt=pt->leadingDigits;
    }
    return str;
}

/*
 * Implementation notes: operator+ and operator*
 * ------------------------------
 * Implement operator+ and operator*, make BigInt surpport addition and
 * multiplication.
 */

BigInt BigInt::operator+(const BigInt & b2) const {
    //TODO
    string str="";
    Cell *pt1=this->start;
    Cell *pt2=b2.start;
    int carry=0;
    int num=0;
    while (pt1!=nullptr&&pt2!=nullptr){
        if (carry==0){
            num=pt1->finalDigit+pt2->finalDigit;}
        else if (carry==1){
            num=pt1->finalDigit+pt2->finalDigit+1;
            carry=0;
        }
        if (num>=10){
            carry=1;
            num=num%10;
        }
        str.insert(0,to_string(num));
        pt1=pt1->leadingDigits;
        pt2=pt2->leadingDigits;
    }

    while (pt1!=nullptr){
        if (carry==0){
        num=pt1->finalDigit;}
        else if (carry==1){
            num=pt1->finalDigit+1;
            carry=0;
        }
        if (num>=10){
            carry=1;
            num=num%10;
        }else{
            carry=0;
        }
        str.insert(0,to_string(num));
        if (pt1->leadingDigits==nullptr){
            if (carry==1){
                str.insert(0,to_string(1));
                carry=0;
            }
        }
        pt1=pt1->leadingDigits;
    }

    while (pt2!=nullptr){
        if (carry==0){
        num=pt2->finalDigit;}
        else if (carry==1){
            num=pt2->finalDigit+1;
            carry=0;
        }
        if (num>=10){
            carry=1;
            num=num%10;
        }else{
            carry=0;
        }
        str.insert(0,to_string(num));
        if (pt2->leadingDigits==nullptr){
            if (carry==1){
                str.insert(0,to_string(1));
                carry=0;
            }
        }
        pt2=pt2->leadingDigits;
    }
    if (carry==1){
        str.insert(0,to_string(1));
    }

    return BigInt(str);
}

BigInt BigInt::operator*(const BigInt & b2) const {
    //TODO
    Cell *pt=b2.start;
    if (b2.start->leadingDigits!=nullptr&&start->leadingDigits!=nullptr){
        BigInt mid1(BigInt(to_string(pt->finalDigit)) * *this);
        BigInt mid2(BigInt(to_string(pt->finalDigit)) * *this);
        pt=pt->leadingDigits;
        int shift=1;
        while (pt!=nullptr){
            mid2=BigInt(to_string(pt->finalDigit)) * *this;
            for (int i=shift;i>0;i--){
                Cell *zero = new Cell;
                zero->finalDigit=0;
                zero->leadingDigits=mid2.start;
                mid2.start=zero;
            }
            shift++;
            mid1=mid1+mid2;
            pt=pt->leadingDigits;
        }
        return mid1;
    }
    else if (b2.start->leadingDigits==nullptr){
        int num=b2.start->finalDigit;
        BigInt mid(toString());
        if (num==0){
            mid=BigInt(to_string(0));
            return mid;
        }
        while(--num){
            mid=mid+BigInt(toString());
        }
        return mid;
    }
    else{
        int num=start->finalDigit;
        BigInt mid(b2.toString());
        if (num==0){
            mid=BigInt(to_string(0));
            return mid;
        }
        while (--num){
            mid=mid+b2;
        }
        return mid;
    }
}


void BigInt::operator=(const BigInt &b2) {
    this->start=nullptr;
    Cell *nowCell=nullptr;
    Cell *nextCell=nullptr;
    Cell *pt2=b2.start;
    while (pt2!=nullptr){
        nextCell=new Cell;
        nextCell->leadingDigits=nullptr;
        nextCell->finalDigit=pt2->finalDigit;
        pt2=pt2->leadingDigits;
        if (nowCell==nullptr){
            nowCell=nextCell;
            this->start=nowCell;
        }else{
            nowCell->leadingDigits=nextCell;
            nowCell=nextCell;
        }
    }
}


BigInt::BigInt(const BigInt & b2){
    this->start=nullptr;
    Cell *nowCell=nullptr;
    Cell *nextCell=nullptr;
    Cell *pt2=b2.start;
    while (pt2!=nullptr){
        nextCell=new Cell;
        nextCell->leadingDigits=nullptr;
        nextCell->finalDigit=pt2->finalDigit;
        pt2=pt2->leadingDigits;
        if (nowCell==nullptr){
            nowCell=nextCell;
            this->start=nowCell;
        }else{
            nowCell->leadingDigits=nextCell;
            nowCell=nextCell;
        }
    }
}
