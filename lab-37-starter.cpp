// COMSC-210 | Lab 37 | Mira Anand
// Module 15, Lesson: Hash Tables, Assignment: Hash Table I
// IDE used: Visual Studio Code for Mac

/* 
These targets are present in the dataset and can be used for testing:
536B9DFC93AF
1DA9D64D02A0
666D109AA22E
E1D2665B21EA
*/

#include <fstream> // needed for file operations
#include <iostream>
#include <string>
using namespace std;

// declaration & initialization of global const variables
const string INPUT_FILE_NAME = "lab-37-data.txt"; // to hold the name of the input file, which contains the string data

// function prototypes
int sum_ascii(const string);

int main() 
{
    // declaration & initialization of variables
    string inputFileLine; // to hold a string value from the input file - will be used to read string data from the input file
    int grandTotal = 0; // represents the sum of all ASCII values in the entire file

    ifstream fin(INPUT_FILE_NAME); // creation of an ifstream (input file) object

    if (!fin) // check if there was an error when opening the input file
    {
        cout << "ERROR: Could not open input file. Please make sure the file exists in the correct location & try running the program again." << endl;
        return 1; // exit with an error state
    }

    while (getline(fin, inputFileLine)) // read all of the string values from the input file until the end of the file is reached
    {
        // call the sum_ascii() function & apply it to inputFileLine
        // store the result of the function (the sum of the ASCII values) in a variable named grandTotal, which will keep a running total of the sum of all ASCII values in the entire file
        grandTotal = grandTotal + sum_ascii(inputFileLine);
    }

    fin.close(); // close the input file

    cout << "The grand total (the sum of all ASCII values in the entire file) is equal to " << grandTotal << endl; // output the grand total, which is the sum of all ASCII values in the entire file

    return 0;
}

// int sum_ascii(const string stringValue) function header
// DESCRIPTION: this function receives a single string & returns the sum of that string's character's ASCII values
// ARGUMENTS: const string stringValue, which represents the string whose characters we want to retrieve the ASCII values for
// - using const because the string will not be modified in this function
// RETURNS: int sum, which is the total sum of the string's character's ASCII values
int sum_ascii(const string stringValue)
{
    int sum = 0; // to hold the sum of the string's character's ASCII values

    for (char charValue : stringValue) // creation of a range-based for loop that will iterate through each of the string's characters
        // each of the string's characters will be cast to an int (representing the char's ASCII value) 
        // - & a running total of all the ASCII values for each char will be stored in the sum variable
        sum = sum + (int) charValue;
    
    return sum; // the total sum of the ASCII values will be returned from the function
}