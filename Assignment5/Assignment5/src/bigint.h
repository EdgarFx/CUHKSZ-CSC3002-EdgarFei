/*
 * File: bigint.h
 * --------------
 * This interface exports the BigInt class, which makes it possible to
 * represent nonnegative integers of arbitrary magnitude.
 */

#ifndef _bigint_h
#define _bigint_h

#include <string>

class BigInt {

public:

/*
 * Constructor: BigInt
 * Usage: BigInt big(str);
 * -----------------------
 * Creates a new BigInt from a string of decimal digits.
 */

   BigInt(std::string str);

/*
 * Destructor: ~BigInt
 * -------------------
 * Frees the memory used by a BigInt when it goes out of scope.
 */

   ~BigInt();

   BigInt(const BigInt & b2);


/*
 * Method: toString
 * Usage: string str = bigint.toString();
 * --------------------------------------
 * Converts a BigInt object to the corresponding string.
 */

   std::string toString() const;

   BigInt operator+(const BigInt & b2) const;
   BigInt operator*(const BigInt & b2) const;
   void operator=(const BigInt & b2);

/* Private section */

/*
 * Implementation notes: BigInt data structure (suggested)
 * -------------------------------------------
 * The BigInt data structure stores the digits in the number in
 * a linked list in which the digits appear in reverse order with
 * respect to the items in the list.  Thus, the number 1729 would
 * be stored in a list like this:
 *
 *     start
 *    +-----+    +-----+    +-----+    +-----+    +-----+
 *    |  o--+--->|  9  |  ->|  2  |  ->|  7  |  ->|  1  |
 *    +-----+    +-----+ /  +-----+ /  +-----+ /  +-----+
 *               |  o--+-   |  o--+-   |  o--+-   | NULL|
 *               +-----+    +-----+    +-----+    +-----+
 *
 * The sign of the entire number is stored in a separate instance
 * variable, which is -1 for negative numbers and +1 otherwise.
 * Leading zeros are not stored in the number, which means that
 * the representation for zero is an empty list.
 */

private:

/*
 * Type: Cell
 * ----------
 * This structure type holds a single digit in the linked list.
 */

   struct Cell {
      Cell *leadingDigits;
      int finalDigit;
   };

/* Instance variables */

   Cell *start;          /* Linked list of digits */

/* Private methods */

   BigInt(Cell *digits) {
      start = digits;
   }

};

#endif
