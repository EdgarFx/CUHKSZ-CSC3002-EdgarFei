/*
 * File: RemoveComments.h
 * ----------------------
 * Prints out a file after removing comments.
 */

#ifndef _RemoveComments_h
#define _RemoveComments_h

/*
 * Function: removeComments
 * Usage: removeComments(is, os);
 * ------------------------------
 * Copies characters from the input stream is to the output stream os,
 * removing any comments it finds.  This program eliminates both the
 * /* and // comment forms but does not check to see if those characters
 * are embedded within strings.
 */

void removeComments(istream & is, ostream & os);

#endif
