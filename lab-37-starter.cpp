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
#include <list> // needed to use std::list
#include <map> // needed to use std::map
#include <string>
using namespace std;

// declaration & initialization of global const variables
const string INPUT_FILE_NAME = "lab-37-data.txt"; // to hold the name of the input file, which contains the string data
const int MODULUS_VALUE = 97; // represents the value that the sum of the ASCII values will be modulo-ed by in the gen_hash_index() function
const int MAP_ENTRY_NUM = 100; // represents the # of map entries that should be displayed to the console

// function prototypes
int gen_hash_index(const string);

int main() 
{
    // creation of the hash table data structure
    // an std::map, in which the key is an int value that represents the hash index
    // - & the value is an std::list, which will contain the codes from the input file that map to a specific hash index
    map<int, list<string> > hash_table;
    
    // declaration & initialization of variables
    string inputFileLine; // to hold a string value from the input file - will be used to read string data from the input file
    int mapEntryCounter = 0; // to keep a track of the map entries being displayed to the console

    ifstream fin(INPUT_FILE_NAME); // creation of an ifstream (input file) object

    if (!fin) // check if there was an error when opening the input file
    {
        cout << "ERROR: Could not open input file. Please make sure the file exists in the correct location & try running the program again." << endl;
        return 1; // exit with an error state
    }

    while (getline(fin, inputFileLine)) // read all of the string values from the input file until the end of the file is reached
    {
        // sending the codes to the gen_hash_index() function as they are being read from the input file
        // receiving the hash index that is being returned from the function & storing it in a variable named hashIndex
        int hashIndex = gen_hash_index(inputFileLine);
        // inputting the pair into the map
        // using .push_back() to add the string value from the input file to the std::list that corresponds to its generated hash index (which is the key of the map)
        hash_table[hashIndex].push_back(inputFileLine);
    }

    fin.close(); // close the input file

    // display the first 100 map entries to the console
    for (auto mapEntry : hash_table) // using a range-based for loop to iterate through the map
    {
        cout << "Hash index: " << mapEntry.first << endl; // use .first to access the hash index (key)
        cout << "Values: ";
        
        for (auto value : mapEntry.second) // using another range-based for loop to access/iterate though the std::lists (values/codes) associated with the hash index by using .second
        {
            cout << value << " "; // output the string values associated with the hash index/key
        }

        cout << endl;
        mapEntryCounter++; // increment the counter, to keep a correct track of the # of map entries being displayed

        if (mapEntryCounter == MAP_ENTRY_NUM) // only display the first 100 (MAP_ENTRY_NUM) map entries and then break from the loop
            break;
    }

    return 0;
}

// int gen_hash_index(const string stringValue) function header
// DESCRIPTION: this function receives a single string & returns the total sum of that string's character's ASCII values modulo-ed by a prime #
// - in short, this function generates a hash index
// ARGUMENTS: const string stringValue, which represents the string whose characters we want to retrieve the ASCII values for
// - using const because the string will not be modified in this function
// RETURNS: int sum % MODULUS_VALUE, which is the generated hash index for the string
int gen_hash_index(const string stringValue)
{
    int sum = 0; // to hold the sum of the string's character's ASCII values

    for (char charValue : stringValue) // creation of a range-based for loop that will iterate through each of the string's characters
        // each of the string's characters will be cast to an int (representing the char's ASCII value) 
        // - & a running total of all the ASCII values for each char will be stored in the sum variable
        sum = sum + (int) charValue;
    
    return sum % MODULUS_VALUE; // the total sum of the ASCII values (modulo-ed by 97 (MODULUS_VALUE), a prime #) will be returned from the function
}