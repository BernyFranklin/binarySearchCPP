/*
 * binarySearchCPP Version#1.0
 * Frank Bernal
 * CIS 054 C/C++ Programming
 * Input: Name or Phone number
 * Output: Name or Phone number
 * 31 Mar 2022
 *
 * This program searches a data file
 * a) By sequential search, then
 * b) By binary search
 * NOTE: Data file must be sorted for the binary search to be successful
 */


#include <iostream>    // Used for standard input output
#include <fstream>     // Used to bring in files
#include <cstdlib>     // Used for general utilities

using namespace std;   // Used for std::cin&cout

#define debug_messages 1

// Define the max number of records on the file
const int LIST_LENGTH = 256;

// Define the lengths of each character array
const int NAME_SIZE = 40;
const int NUMBER_SIZE = 13;
const int LINE_SIZE = 80;

// Define the structure for the array of records
typedef struct S_REC {
    char name[NAME_SIZE];
    char number[NUMBER_SIZE];
} PhoneRec;

// Start Main
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
