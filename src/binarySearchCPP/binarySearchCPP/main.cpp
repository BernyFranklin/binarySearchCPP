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
    // Declare variables and arrays
    PhoneRec List[LIST_LENGTH];   // [length][width]
    char line[LINE_SIZE];         // Line of text from the disk
    char filename[] = "/Users/frankbernal/Documents/GitHub/binarySearchCPP/src/binarySearchCPP/binarySearchCPP/phonyListing.txt";
    char* ptr;
    int searchCounter;
    
    // ===============================================
    // ----- Read the file into the List[] array -----
    // ===============================================
    
    ifstream PhoneFile(filename);
    
    // Did filename work?
    if (!PhoneFile) {
        cerr << "Unable to open" << filename << endl;
        return 1;
    }   // End of file check
    
    // Variables for loop to load file into array
    int listSize = 0;
    line[0] = 0;                          // Clear the line buffer
    PhoneFile.getline(line, LINE_SIZE);   // Read the 1st line in the file
    
    // Start loop
    while (!PhoneFile.eof() && listSize < LIST_LENGTH && line[0]) {
        // If string length in line is > 1
        if (strlen(line) > 1) {
            // The following lines of are specific for xCode
            ptr = strtok(line, ".");               // Find name separated by "." char
            strcpy(List[listSize].name, ptr);      // Copy name to array, position[listSize]
            ptr = strtok(NULL, ".\r\n");           // Find Phone number
            strcpy (List[listSize].number, ptr);   // Copy number to array
            listSize++;                            // Update listSize
        }   // End of if statement
        
        line[0] = 0;                          // Clear the line buffer
        PhoneFile.getline(line, LINE_SIZE);   // Read the next line
    }   // End of loop
    
#if debug_messages == 1
    cout << "There are " << listSize << " Lines in the file." << endl;
#endif
    
    // ---------------------- Request a search string, then find it ----------------------
    char searchString[80];   // Char Array for user input
    // Prompt for input
    cout << "Enter a name or phone number: ";
    // Using getline to read spaces.
    cin.getline(searchString, 80);
    
    // ------------------------------------------------------------
    // --------------------- Sequential Seacrh --------------------
    // ------------------------------------------------------------
    bool found = false;   // Heaven't found it yet
    int index;            // Use for loop
    
    // Start loop
    for (index = 0; index < listSize; index++) {
        searchCounter++;   // Keep track of attempts
        
        // Does search match the index for a number?
        if (strstr(List[index].number, searchString)) {
            found = true;   // Fount it
            break;          // exit loop
        } // End of if
        
        // Does the search match the index for a name?
        else if (strstr(List[index].name, searchString)) {
            found = true;
            break;
        }
        
    }   // End of for
    
    // Display for sequential search
    cout << endl;
    cout << "================================================" << endl;
    cout << "              Sequential Search Data            " << endl;
    cout << "================================================" << endl;
    // Did we find it?
    if (found) {
        cout << "Customer name: " << List[index].name << endl;
        cout << "Customer phone: " << List[index].number << endl;
        cout << searchCounter << " tests were made" << endl;
    }   // End of if
    else
        cout << "Not found" << endl;
    
    // Test output
    cout << "=================================" << endl;
    cout << "This is test output, delete later" << endl;
    cout << "=================================" << endl;
    cout << "List size = " << listSize <<endl;
    cout << "Name at index [" << index << "] is: " << List[184].name << endl;
    
    return 0;
}
