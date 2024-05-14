/*
 * File: BigIntTest.cpp
 * --------------------
 * This file calculates a table of factorials.
 */

#include <iostream>
#include <string>
#include "bigint.h"
#include "strlib.h"
using namespace std;

BigInt fact(int n) {
   BigInt result("1");
   for (int i = 1; i <= n; i++) {
      result = result * BigInt(integerToString(i));
   }
   return result;
}

int BigIntTest() {
   for (int i = 0; i <= 52; i++) {
      if (i < 10) cout << " ";
      cout << i << "! = " << fact(i).toString() << endl;
   }
   return 0;
}
