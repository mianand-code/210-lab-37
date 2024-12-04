// COMSC-210 | Lab 38 | Mira Anand
// Module 15, Lesson: Hash Tables, Assignment: Hash Tables II
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
const string INPUT_FILE_NAME = "lab-37-data.txt"; // to hold the name of the input file, which contains the string data/codes
const int MODULUS_VALUE = 100003; // represents the value that the sum of the string's ASCII values will be modulo-ed by in the gen_hash_index() function - this should be a large prime # since our dataset is large
const int MAP_ENTRY_NUM = 100; // represents the # of map entries that should be displayed to the console

// function prototypes
int gen_hash_index(const string);
void print_map_entries(const map<int, list<string> > hash_table);

int main()
{
    // creation of the hash table data structure
    // this is an std::map, in which the key is an int value that represents the hash index
    // the value is an std::list, which will contain the string data/codes from the input file that map to a specific hash index
    map<int, list<string> > hash_table;
    
    // declaration & initialization of variables section
    string inputFileLine; // to hold a string value/code from the input file - will be used to read string data from the input file
    int userChoiceMenuNum; // to hold the user's choice for the menu option # they would like to select

    ifstream fin(INPUT_FILE_NAME); // creation of an ifstream (input file) object

    if (!fin) // check if there was an error when opening the input file
    {
        cout << "ERROR: Could not open input file. Please make sure the file exists in the correct location & try running the program again." << endl;
        return 1; // exit with an error state
    }

    while (getline(fin, inputFileLine)) // read all of the string values/codes from the input file until the end of the file is reached
    {
        // sending the codes to the gen_hash_index() function as they are being read from the input file
        // receiving the hash index that is being returned from the function & storing it in a variable named hashIndex
        int hashIndex = gen_hash_index(inputFileLine);
        // inputting the pair (hash index & string/code) into the map
        // using .push_back() to add the string value/code from the input file to the std::list that corresponds to its generated hash index (which is the key of the map)
        hash_table[hashIndex].push_back(inputFileLine);
    }

    fin.close(); // close the input file

    // creation of an interactive menu with new features
    do  // creation of a do-while loop so that the user can continue to select options until they wish to quit
    {
        // output the menu of choices that the user can select from
        cout << endl << "Hash Table Menu:" << endl;
        cout << "[1] Print the first 100 map entries" << endl;
        cout << "[2] Search for a key" << endl;
        cout << "[3] Add a key" << endl;
        cout << "[4] Remove a key" << endl;
        cout << "[5] Modify a key" << endl;
        cout << "[6] Exit" << endl;
        cout << endl;

        // user input for menu option # they would like to choose
        cout << "Enter your choice: "; 
        cin >> userChoiceMenuNum;
        cin.ignore(); // needed before reading string user input

        // creation of a switch statement that handles cases of each numbered option based on userChoiceMenuNum
        switch (userChoiceMenuNum)
        {
            case 1:
                print_map_entries(hash_table); // print_map_entries() function call, will print the first 100 map (hash_table) entries
                break;

            case 2:

                break;

            case 3:

                break;

            case 4:

                break;

            case 5:

                break;
            
            // menu option #6 means the user wants to exit the program
            case 6:
                cout << "Thank you for using this program. Now exiting..." << endl;
                break;
            
            // user input validation for menu option # (has to be 1-6)
            default:
                cout << "ERROR: Invalid entry. Please enter a valid menu option number (1-6) and try again." << endl;
        }

    } while (userChoiceMenuNum != 6); // userChoiceMenuNum = 6 means user wants to quit program

    return 0;
}

// int gen_hash_index(const string stringValue) function header
// DESCRIPTION: this function receives a single string & returns the total sum of that string's character's ASCII values modulo-ed by a prime #
// - in short, this function generates a hash index
// ARGUMENTS: const string stringValue, which represents the string whose ASCII values will be summed up & modulo-ed - therefore generating a hash index for the string
// - using const because the string itself will not be modified in this function
// RETURNS: int sum % MODULUS_VALUE, which is the generated hash index for the string
int gen_hash_index(const string stringValue)
{
    int sum = 0; // to hold the sum of the string's character's ASCII values

    for (char charValue : stringValue) // creation of a range-based for loop that will iterate through each of the string's characters
        // each of the string's characters will be cast to an int (representing the char's ASCII value) 
        // a running total of the ASCII values for each char in the string will be stored in the sum variable
        sum = sum + (int) charValue;
    
    // the total sum of the string's ASCII values (modulo-ed by 100003 (MODULUS_VALUE), a prime #) will be returned from the function
    // in other words, the generated hash index for the string will be returned from the function
    return sum % MODULUS_VALUE;
}

// void print_map_entries(const map<int, list<string> > hash_table) function header
// DESCRIPTION: this function will display the first 100 map (hash_table) entries to the console
// - output will include hash indexes (keys) along with their associated values (strings/codes)
// ARGUMENTS: const map<int, list<string> > hash_table, which is the hash table data structure
// - the hash table data structure is an std::map, in which the key is an int value that represents the hash index
// - & the value is an std::list, which will contain the strings/codes that map to a specific hash index
// RETURNS: nothing, void function
void print_map_entries(const map<int, list<string> > hash_table)
{
    int mapEntryCounter = 0; // to keep a track of the map entries being displayed to the console

    // display the first 100 map entries to the console
    for (auto mapEntry : hash_table) // using a range-based for loop to iterate through the map
    {
        cout << endl;
        cout << "Hash index: " << mapEntry.first << endl; // use .first to access & output the hash index (key)
        cout << "Values: ";
        
        for (auto value : mapEntry.second) // using another range-based for loop to access/iterate though the std::lists (string values/codes) associated with the hash index by using .second
        {
            cout << value << " "; // output the string values/codes associated with the hash index/key
        }

        cout << endl;
        mapEntryCounter++; // increment the counter, to keep a correct track of the # of map entries being displayed

        if (mapEntryCounter == MAP_ENTRY_NUM) // only display the first 100 (MAP_ENTRY_NUM) map entries and then break from the loop
            break;
    }
}