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
#include <cctype>      // Used for isalpha
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
    
    // Location of file on my device
    char filename[] = "/Users/frankbernal/Documents/GitHub/binarySearchCPP/src/binarySearchCPP/binarySearchCPP/phonyListing.txt";
    
    char* ptr;
    int searchCounterSequential;   // Counters for each search
    int searchCounterBinary;
    
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
    
    // Welcome display
    cout << "================================================" << endl;
    cout << "                Directory search                " << endl;
    cout << " This program will ask for a name or phone      " << endl;
    cout << " number and perform a sequential search and a   " << endl;
    cout << " binary search through the directory. Upon      " << endl;
    cout << " completion the program will compare the results" << endl;
    cout << " and display which one was more efficient.      " << endl;
    cout << "================================================" << endl;
    cout << endl;
#if debug_messages == 1
    cout << "There are " << listSize << " Lines in the file." << endl;
#endif
    
    // ---------------------- Request a search string, then find it ----------------------
    
    char searchString[80];   // Char Array for user input
    
    // Prompt for input
    cout << endl;
    cout << "Enter a name or phone number: ";
    // Using getline to read spaces.
    cin.getline(searchString, 80);
    
    // ------------------------------------------------------------
    // --------------------- Sequential Seacrh --------------------
    // ------------------------------------------------------------
    bool found = false;            // Heaven't found it yet
    int index;                     // Use for loop
    searchCounterSequential = 0;   // Initialize counter
    
    // Start loop
    // Iterate through list unti la match is found
    for (index = 0; index < listSize; index++) {
        searchCounterSequential++;   // Keep track of attempts
        
        // Does search match the index for a number?
        if (strstr(List[index].number, searchString)) {
            found = true;   // Fount it
            break;          // exit loop
        } // End of if
        
        // Does the search match the index for a name?
        else if (strstr(List[index].name, searchString)) {
            found = true;
            break;
        }   // End of else
        
    }   // End of for
    
    // Display for sequential search
    cout << endl;
    cout << "================================================" << endl;
    cout << "            Sequential Search Results           " << endl;
    cout << "================================================" << endl;
    // Did we find it?
    if (found) {
        // Display name, number, and tests made
        cout << "Customer name: " << List[index].name << endl;
        cout << "Customer phone: " << List[index].number << endl;
        cout << searchCounterSequential << " tests were made" << endl;
    }   // End of if
    
    // We did not find it
    else
        cout << "Not found" << endl;
    
    // ------------------------------------------------------------------
    // -------------------------- Binary Search -------------------------
    // ------------------------------------------------------------------
    
    searchCounterBinary = 0;        // Keep count of how many searches
    int lowerBound = 0;             // Start of search has range from [0]
    int upperBound = listSize -1;   // to end of array
    int midpoint = 0;
    
    // Display header for binary search
    cout << endl;
    cout << "================================================" << endl;
    cout << "              Starting Binary Search            " << endl;
    cout << "================================================" << endl;
    
    // Not found yet
    found = false;
    
    // Start loop
    // Continue until lowerBound and upperBound meet
    // By the time they meet they should be on the searched
    // item or the search is done
    while (lowerBound <= upperBound) {
        searchCounterBinary++;                      // Update binary counter
        midpoint = (lowerBound + upperBound) / 2;   // Add low and upper and find middle
        
#if debug_messages == 1
        // setw(3) is to format all number data to be 3 chars wide
        cout << setw(3) << searchCounterBinary << " lowerBound = " << setw(3) << lowerBound << " midPoint = "
        << setw(3) << midpoint << " upperBound = " << setw(3) << upperBound << "  " << List[midpoint].name << endl;
#endif
        // All searches use strcasecmp() to be case insensitive
        // Is the search alphabetic?
        if (isalpha(searchString[0])) {
            // Search is greater than midpoint
            if (strcasecmp(List[midpoint].name, searchString) < 0)
                lowerBound = midpoint + 1;   // Cut off lower half
            // Search is lower than midpoint
            else if (strcasecmp(List[midpoint].name, searchString) > 0)
                upperBound = midpoint - 1;   // Cut off upper half
            // Search found a match
            else {
                found = true;   // Set Flag
                break;          // Exit loop
            }   // End of else
        }   // End of alphabetic
        
        // Search is numeric
        else {
            // Search is greater than midpoint
            if (strcasecmp(List[midpoint].number, searchString) < 0)
                lowerBound = midpoint + 1;   // Cut off lower half
            // Search is lower than midpoint
            else if (strcasecmp(List[midpoint].number, searchString) > 0)
                upperBound = midpoint - 1;   // Cut off upper half
            // Search found a match
            else {
                found = true;   // Set flag
                break;          // Exit loop
            }   // End of else
        }   // End of numeric
        
     }   // End of loop
    
    // Results display
    cout << endl;
    cout << "================================================" << endl;
    cout << "              Binary Search Results             " << endl;
    cout << "================================================" << endl;
    
    // Found it
    // Display Name, number, and tests made
    if (found) {
        cout << "Customer name: " << List[midpoint].name << endl;
        cout << "Customer phone: " << List[midpoint].number << endl;
        cout << searchCounterBinary << " tests were made" << endl;
    }   // End of if
    
    // Did not find it
    else
        cout << "Not Found in " << searchCounterBinary << " tries" << endl << endl;
    
    // Efficiency report
    cout << endl;
    cout << "================================================" << endl;
    cout << "                Efficiency Report               " << endl;
    cout << "================================================" << endl;
    // Compare results
    // Display which search was more efficient and by how much
    if (searchCounterSequential < searchCounterBinary) {
        cout << "The sequential search was more efficient by completing " << searchCounterBinary - searchCounterSequential
        << " fewer tests." << endl << endl;
    }   // End of if
    else if (searchCounterSequential > searchCounterBinary) {
        cout << "The binary search was more efficient by completing " << searchCounterSequential - searchCounterBinary
        << " fewer tests." << endl << endl;
    }   // End of if else
    else
        cout << "Both searches were equallt efficient" << endl << endl;
    
    return 0;
}
