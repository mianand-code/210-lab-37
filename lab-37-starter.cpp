// COMSC-210 | Lab 38 | Mira Anand
// Module 15, Lesson: Hash Tables, Assignment: Hash Tables II
// IDE used: Visual Studio Code for Mac

// Note: The program trusts that the user will enter strings/codes exactly the same as how they are listed in the input file in order to achieve accurate results when removing, searching for, and modifying keys

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
void print_map_entries(const map<int, list<string>> hash_table);
void search_for_key(const map<int, list<string>> hash_table);
void add_key(map<int, list<string>>& hash_table);
void remove_key(map<int, list<string>>& hash_table);
void modify_key(map<int, list<string>>& hash_table);

int main()
{
    // creation of the hash table data structure
    // this is an std::map, in which the key is an int value that represents the hash index
    // the value is an std::list, which will contain the string data/codes from the input file that will map to a specific hash index
    map<int, list<string>> hash_table;
    
    // declaration of variables section
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
        // cases 2-5 include user input validation within their respective functions, to ensure that a user does not leave a field blank. Further input validation is not needed, since a key string entry can consist of any combination of letters/numbers
        switch (userChoiceMenuNum)
        {
            case 1:
                print_map_entries(hash_table); // print_map_entries() function call, will print the first 100 map (hash_table) entries
                break;

            case 2:
                search_for_key(hash_table); // search_for_key() function call, will search for a user-entered key within the hash table data structure
                break;

            case 3:
                add_key(hash_table); // add_key() function call, will allow the user to enter a key that they would like to add to the hash table data structure
                break;

            case 4:
                remove_key(hash_table); // remove_key() function call, will allow the user to enter a key that they would like to remove from the hash table data structure
                break;

            case 5:
                modify_key(hash_table); // modify_key() function call, will allow the user to enter information to modify a key that exists in the hash table data structure
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

// void print_map_entries(const map<int, list<string>> hash_table) function header
// DESCRIPTION: this function will display the first 100 map (hash_table) entries to the console
// - output will include each hash index (keys) along with their associated values (strings/codes)
// ARGUMENTS: const map<int, list<string>> hash_table, which is the hash table data structure
// - the hash table data structure is an std::map, in which the key is an int value that represents the hash index
// - & the value is an std::list, which will contain the strings/codes that map to a specific hash index
// - using const because the map itself will not be modified in this function
// RETURNS: nothing, void function
void print_map_entries(const map<int, list<string>> hash_table)
{
    int mapEntryCounter = 0; // to keep a track of the map entries being displayed to the console

    // display the first 100 map entries to the console
    for (auto mapEntry : hash_table) // using a range-based for loop to iterate through the map
    {
        cout << endl;
        cout << "Hash index: " << mapEntry.first << endl; // use .first to access & output the hash index (key)
        cout << "Values: ";
        
        for (auto value : mapEntry.second) // using an inner range-based for loop to access/iterate though the std::lists (which contain the string values/codes) associated with each hash index by using .second
        {
            cout << value << " "; // output the string values/codes associated with the hash index/key
        }

        cout << endl;
        mapEntryCounter++; // increment the counter, to keep a correct track of the # of map entries being displayed

        // only display the first 100 (MAP_ENTRY_NUM) map entries and then break from the loop
        if (mapEntryCounter == MAP_ENTRY_NUM)
            break;
    }
}

// void search_for_key(const map<int, list<string>> hash_table) function header
// DESCRIPTION: this function will take a user-entered key (string/code) and search for it in the hash table
// - the user will be notified if the key was found or not
// ARGUMENTS: const map<int, list<string>> hash_table, which is the hash table data structure
// - the hash table data structure is an std::map, in which the key is an int value that represents the hash index
// - & the value is an std::list, which will contain the strings/codes that map to a specific hash index
// - using const because the map itself will not be modified in this function
// RETURNS: nothing, void function
void search_for_key(const map<int, list<string>> hash_table)
{
    string userKey; // will hold user input for the key (string/code) they would like to search for
    // get user input - input validation is included to ensure the user does not leave the field blank
    do
    {
        cout << "Enter the key you would like to search for: ";
        getline(cin, userKey);

        if (userKey.empty())
        {
            cout << "ERROR: Field cannot remain blank. Please enter a key & try again." << endl;
        }
    } while (userKey.empty());

    int hashIndex = gen_hash_index(userKey); // gen_hash_index() function call, to generate the hash index for the user-entered key & store that hash index in a variable
    auto it = hash_table.find(hashIndex); // creation of an iterator to find/point to the generated hash index, using .find to accomplish this

    if (it == hash_table.end()) // if the iterator reaches the end of the hash table, this means that the hash index was not found & the user-entered key does not exist within the hash table
    {
        cout << "The key was not found." << endl;
        return; // exit the function at this point
    }

    auto keyList = it->second; // access the list of strings/codes that are associated with the generated/found hash index, by using second
    bool keyFound = false; // creation of a bool to keep track of whether the key was found or not, setting it to false to start with

    for (auto key : keyList) // creation of a range-based for loop to traverse the list of strings/codes
    {
        if (key == userKey) // if the user-entered key matches a string/code in the list
        {
            cout << "The key has been found with a hash index of " << hashIndex << endl;
            keyFound = true; // set the bool flag to true, to indicate that the key being searched for has been found
            break; // exit the loop since the key has been found
        }
    }

    // if the bool flag is still false at this point, the key has not been found
    // this handles a case where a hash index might be found for a user-entered key, but the key was not found in the list associated with the hash index
    if (!keyFound)
        cout << "The key was not found." << endl;
}

// void add_key(map<int, list<string>>& hash_table) function header
// DESCRIPTION: this function will allow the user to add a key (string/code) to the hash table
// ARGUMENTS: map<int, list<string>>& hash_table, which is the hash table data structure
// - the hash table data structure is an std::map, in which the key is an int value that represents the hash index
// - & the value is an std::list, which will contain the strings/codes that map to a specific hash index
// - passing by reference because the map will be modified in this function
// RETURNS: nothing, void function
void add_key(map<int, list<string>>& hash_table)
{
    string userKey; // will hold user input for the key they would like to add
    // get user input - input validation is included to ensure the user does not leave the field blank
    do
    {
        cout << "Enter the key that you would like to add: ";
        getline(cin, userKey);

        if (userKey.empty())
        {
            cout << "ERROR: Field cannot remain blank. Please enter a key & try again." << endl;
        }
    } while (userKey.empty());

    int hashIndex = gen_hash_index(userKey); // gen_hash_index() function call, to generate the hash index for the user-entered key & store that hash index in a variable
    // using .push_back() to add the user-entered key to the std::list that corresponds to its generated hash index
    hash_table[hashIndex].push_back(userKey);

    cout << "The key has been added." << endl;
}

// void remove_key(map<int, list<string>>& hash_table) function header
// DESCRIPTION: this function will allow the user to remove a key (string/code) from the hash table
// ARGUMENTS: map<int, list<string>>& hash_table, which is the hash table data structure
// - the hash table data structure is an std::map, in which the key is an int value that represents the hash index
// - & the value is an std::list, which will contain the strings/codes that map to a specific hash index
// - passing by reference because the map will be modified in this function
// RETURNS: nothing, void function
void remove_key(map<int, list<string>>& hash_table)
{
    string userKey; // will hold user input for the key they would like to remove
    // get user input - input validation is included to ensure the user does not leave the field blank
    do
    {
        cout << "Enter the key you would like to remove: ";
        getline(cin, userKey);

        if (userKey.empty())
        {
            cout << "ERROR: Field cannot remain blank. Please enter a key & try again." << endl;
        }
    } while (userKey.empty());

    int hashIndex = gen_hash_index(userKey); // gen_hash_index() function call, to generate the hash index for the user-entered key & store that hash index in a variable
    auto it = hash_table.find(hashIndex); // creation of an iterator to find/point to the generated hash index, using .find to accomplish this

    if (it == hash_table.end()) // if the iterator reaches the end of the hash table, this means that the hash index was not found & the user-entered key does not exist within the hash table
    {
        cout << "The key was not found. Removal cannot be performed." << endl;
        return; // exit the function at this point
    }

    // access the list of strings/codes that are associated with the generated/found hash index, by using second
    // - using auto& because the list will be modified if the key is present
    auto& keyList = it->second;
    bool keyFound = false; // creation of a bool to keep track of whether the key was found or not, setting it to false to start with

    for (auto key : keyList) // creation of a range-based for loop to traverse the list of strings/codes
    {
        if (key == userKey) // if the user-entered key matches a string/code in the list
        {
            cout << "The key has been found. Removal in progress..." << endl;
            keyFound = true; // set the bool flag to true, to indicate that the key wanting to be removed has been found
            break; // exit the loop since the key has been found
        }
    }

    // if the bool flag is still false at this point, the key has not been found and therefore cannot be removed
    // this handles a case where a hash index might be found for a user-entered key, but the key was not found in the list associated with the hash index
    if (!keyFound)
    {
        cout << "The key was not found. Removal cannot be performed." << endl;
        return; // exit function since removal cannot be performed
    }

    keyList.remove(userKey); // use .remove to remove the user-entered key from the list that corresponds to the generated hash index
    cout << "The key has been removed." << endl;

    // if the list is empty after key removal, this means we have to erase the hash index too, since no values are associated with it anymore
    if (keyList.empty())
    {
        hash_table.erase(it); // use .erase to erase the hash index if the list is empty - this extra step ensures clean removal of the map key-value pairs
        cout << "The hash index has also been removed, since there are no values associated with it." << endl;
    }
}

// void modify_key(map<int, list<string>>& hash_table) function header
// DESCRIPTION: this function will allow the user to modify a key (string/code) in the hash table
// - modification occurs by first removing the old key & then adding the new one
// ARGUMENTS: map<int, list<string>>& hash_table, which is the hash table data structure
// - the hash table data structure is an std::map, in which the key is an int value that represents the hash index
// - & the value is an std::list, which will contain the strings/codes that map to a specific hash index
// - passing by reference because the map will be modified in this function
// RETURNS: nothing, void function
void modify_key(map<int, list<string>>& hash_table)
{
    string userKey; // will hold user input for the key they would like to modify
    string userNewKey; // will hold user input for the new modified key they want to add

    // get user input - input validation is included to ensure the user does not leave the field blank
    do
    {
        cout << "Enter the key you would like to modify: ";
        getline(cin, userKey);

        if (userKey.empty())
        {
            cout << "ERROR: Field cannot remain blank. Please enter a key & try again." << endl;
        }
    } while (userKey.empty());

    int hashIndex = gen_hash_index(userKey); // gen_hash_index() function call, to generate the hash index for the user-entered key & store that hash index in a variable
    auto it = hash_table.find(hashIndex); // creation of an iterator to find/point to the generated hash index, using .find to accomplish this

    if (it == hash_table.end()) // if the iterator reaches the end of the hash table, this means that the hash index was not found & the user-entered key does not exist within the hash table
    {
        cout << "The key was not found. Modification cannot be performed." << endl;
        return; // exit the function at this point
    }

    // access the list of strings/codes that are associated with the generated/found hash index, by using second
    // - using auto& because the list will be modified if the key is present
    auto& keyList = it->second;
    bool keyFound = false; // creation of a bool to keep track of whether the key was found or not, setting it to false to start with

    for (auto key : keyList) // creation of a range-based for loop to traverse the list of strings/codes
    {
        if (key == userKey) // if the user-entered key matches a string/code in the list
        {
            cout << "The key has been successfully found & modification can occur..." << endl;
            keyFound = true; // set the bool flag to true, to indicate that the key wanting to be modified has been found
            break; // exit the loop since the key has been found
        }
    }

    // if the bool flag is still false at this point, the key has not been found and therefore cannot be modified
    // this handles a case where a hash index might be found for a user-entered key, but the key was not found in the list associated with the hash index
    if (!keyFound)
    {
        cout << "The key was not found. Modification cannot be performed." << endl;
        return; // exit function since modification cannot be performed
    }

    keyList.remove(userKey); // if we reach this point, that means that the key was found, so we start the modification process by removing the user-entered key from the list

    // get user input for the new modified key they want to add
    // input validation is included to ensure the user does not leave the field blank
    do
    {
        cout << "Enter the new modified key you would like to add: ";
        getline(cin, userNewKey);

        if (userNewKey.empty())
        {
            cout << "ERROR: Field cannot remain blank. Please enter a key & try again." << endl;
        }
    } while (userNewKey.empty());
    
    int newKeyHashIndex = gen_hash_index(userNewKey); // gen_hash_index() function call, to generate a fresh hash index for the new modified key that the user has entered - store that in a variable
    hash_table[newKeyHashIndex].push_back(userNewKey); // using .push_back() to add the user-entered key to the std::list that corresponds to its generated hash index

    cout << "The key has been modified." << endl;

    // if the list is empty after key removal, this means we have to erase the hash index too, since no values are associated with it anymore
    if (keyList.empty())
    {
        hash_table.erase(it); // use .erase to erase the hash index if the list is empty - this extra step ensures clean removal of the map key-value pairs
        cout << "The old hash index has also been removed, since there are no values associated with it." << endl;
    }
}