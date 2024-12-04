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

#include <iostream>
#include <string>
using namespace std;

// function prototypes
int sum_ascii(const string);

int main() 
{
    // declaration & initialization of variables
    string testString = "My name is Mira"; // to hold the string that we want to test with the sum_ascii() function

    // call the sum_ascii() function & apply it to testString
    // store the result of the function (the sum of the char's ASCII values) in a variable named testResult
    int testResult = sum_ascii(testString);
    cout << "The sum is equal to " << testResult << endl; // output the results

    return 0;
}

// int sum_ascii(const string stringValue) function header
// DESCRIPTION: this function receives a single string & returns the sum of that string's character's ASCII values
// ARGUMENTS: const string stringValue, which represents the string whose characters we want to calculate the ASCII values for
// - using const because the string will not be modified in this function
// RETURNS: int sum, which is the total sum of the string's character's ASCII values
int sum_ascii(const string stringValue)
{
    int sum = 0; // to hold the sum of the string's character's ASCII values

    for (char charValue : stringValue) // creation of a range-based for loop that will iterate through each of the string's characters
        // each of the string's characters will be cast to an int (representing the char's ASCII value) 
        // - & a running total of all the ASCII values for each char will be stored in the sum variable
        sum = sum + (int) charValue;
    
    return sum; // the total sum will be returned from the function
}