/**
 * This program uses a "getch" function which means "get character".
 * However, getch does not print the character to the terminal, it 
 * lets you decide what to do based on what character you are pressing.
 * 
 * You can test which characters are being pressed using thier ascii values. 
 * 
 * An ascii table here should be helpful 
 *      http://www.asciitable.com/
 * 
 * Some integer values for some keys:
 *      LowerCase Letters   = 97(a) -> 122(z)
 *      UpperCase Letters   = 65(A) -> 90(Z)
 *      Enter Key           = 10
 *      Space Bar           = 32
 *      
 *      Arrow Keys          = Have same values as some letters
 *                            so we can't distinguish between 
 *                            the two (in this context).
 * 
 * Code below is a basic example of using a "getch" function along with
 * searching an array of words for partial matches. 
 * 
 * https://repl.it/@rugbyprof/getchexample#main.cpp
 */

#include "mygetch.hpp"
#include "termcolor.hpp"
#include "timer.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "JsonFacade.hpp"

using namespace std;

#define RED termcolor::red

#define CHAR_SIZE 26

bool isUpper(char letter) {
    int l = letter;
    return (l >= 65 && l <= 90);
}

bool isLower(char letter) {
    int l = letter;
    return (l >= 97 && l <= 122);
}

bool isLetter(char letter) {
    int l = letter;
    return isUpper(l) || isLower(l);
}

bool isAlphaOnly(string word) {
    for (int i = 0; i < word.length(); i++) {
        if (!isLetter(word[i])) {
            return false;
        }
    }
    return true;
}

void makeUpper(string &word) {
    for (int i = 0; i < word.length(); i++) {
        if (isLower(word[i])) {
            word[i] -= 32;
        }
    }
}

struct TrieNode {
    bool isLeaf;
    TrieNode *character[CHAR_SIZE];
    TrieNode() {
        this->isLeaf = false;

        for (int i = 0; i < CHAR_SIZE; i++) {
            this->character[i] = nullptr;
        }
    }
};

vector<char> countLetters(string filename) {
    ifstream fin;
    vector<char> alph;

    fin.open(filename);

    string word;
    while (!fin.eof()) {
        fin >> word;
        for (int j = 0; j < word.size(); j++) {
            if (std::find(alph.begin(), alph.end(), word[j]) == alph.end()) {
                alph.push_back(word[j]);
            }
        }
    }
    return alph;
}

// A class to store a Trie node
class Trie {
    TrieNode *root;
    bool deletion(TrieNode *&, string);
    void find_all(TrieNode *&, string);
    vector<string> results;

public:
    Trie() {
        root = new TrieNode;
    }
    void insert(string);
    bool deletion(string);
    bool search(string);
    bool haveChildren(TrieNode const *);
    vector<string> find_all(string);
    int isBuilt(TrieNode* root) {
      int count = 0;
      // We check if root node has all childs
      // if None of them is NULL then we return true
      for (int i = 0; i < CHAR_SIZE; i++) {
        // If there is no word in the trie starting
        // from the current alphabet
        if (root->character[i] != NULL)
          count++;
      }
      return count;
    }
};


void Trie::find_all(TrieNode *&curr,string key){
    if(curr->isLeaf){
        results.push_back(key);
    }

    for (int i = 0; i < 26; i++) {
        if(curr->character[i] != nullptr){
            find_all(curr->character[i],key+char(i+65));
        }
    }
}

vector<string> Trie::find_all(string key){
    TrieNode* curr = root;
    makeUpper(key);

    //[0][1][2]......[25]  
  
    results.clear();
    
    for (int i = 0; i < key.length(); i++) {
        // go to the next node
      curr = curr->character[key[i] - 65];
      if (curr==nullptr) {
        return results;
      }
    }

    find_all(curr,key);
    return results;
}

// Iterative function to insert a key into a Trie
void Trie::insert(string key) {
    makeUpper(key);

    //cout<<key<<endl;

    // start from the root node
    TrieNode *curr = root;
    for (int i = 0; i < key.length(); i++) {

        // create a new node if the path doesn't exist
        if (curr->character[key[i] - 65] == nullptr) {
            curr->character[key[i] - 65] = new TrieNode();
        }

        // go to the next node
        curr = curr->character[key[i] - 65];
    }

    // mark the current node as a leaf
    curr->isLeaf = true;
}

// Iterative function to search a key in a Trie. It returns true
// if the key is found in the Trie; otherwise, it returns false
bool Trie::search(string key) {
    makeUpper(key);

    TrieNode *curr = root;
    // return false if Trie is empty
    if (curr == nullptr) {
        return false;
    }

    for (int i = 0; i < key.length(); i++) {

        // go to the next node
        curr = curr->character[key[i] - 65];

        // if the string is invalid (reached end of a path in the Trie)
        if (curr == nullptr) {
            return false;
        }
    }

    // return true if the current node is a leaf and the
    // end of the string is reached
    return curr->isLeaf;
}

// Returns true if a given node has any children
bool Trie::haveChildren(TrieNode const *curr) {
    for (int i = 0; i < CHAR_SIZE; i++) {
        if (curr->character[i]) {
            return true; // child found
        }
    }

    return false;
}


bool Trie::deletion(string key) {
    makeUpper(key);
    return deletion(root, key);
}

// Recursive function to delete a key in the Trie
bool Trie::deletion(TrieNode *&curr, string key) {

    // return if Trie is empty
    if (curr == nullptr) {
        return false;
    }

    // if the end of the key is not reached
    if (key.length()) {
        // recur for the node corresponding to the next character in the key
        // and if it returns true, delete the current node (if it is non-leaf)

        if (curr != nullptr &&
            curr->character[key[0] - 65] != nullptr &&
            deletion(curr->character[key[0] - 65], key.substr(1)) && curr->isLeaf == false) {
            if (!haveChildren(curr)) {
                delete curr;
                curr = nullptr;
                return true;
            } else {
                return false;
            }
        }
    }

    // if the end of the key is reached
    if (key.length() == 0 && curr->isLeaf) {
        // if the current node is a leaf node and doesn't have any children
        if (!haveChildren(curr)) {
            // delete the current node
            delete curr;
            curr = nullptr;

            // delete the non-leaf parent nodes
            return true;
        }

        // if the current node is a leaf node and has children
        else {
            // mark the current node as a non-leaf node (DON'T DELETE IT)
            curr->isLeaf = false;

            // don't delete its parent nodes
            return false;
        }
    }

    return false;
}

/**
 * Description:
 *      Originally wrote this to count size of input file so
 *      I could allocate enough memory for an array of strings
 *      but I went with a vector below. But I'm keeping it and
 *      using it anyway!
 * Params:
 *      string file_name - file to get the line count
 * 
 * Returns:
 *      int - line count
 */
/*int CountLines(string file_name) {
    ifstream inFile(file_name);
    return count(istreambuf_iterator<char>(inFile), istreambuf_iterator<char>(), '\n');
}*/

/**
 * Description:
 *      Loads a file of strings (words, names, whatever) reading them in
 *      with one word per line. So words must be delimited by newlines '\n'
 * Params:
 *      string file_name - file to get the line count
 * 
 * Returns:
 *      int - line count
 */
/*vector<string> LoadAnimals(string file_name) {
    ifstream fin;                            // file to get animal names
    int count = (CountLines(file_name) + 1); // get size of input file
    vector<string> array(count);             // allocate vector of correct size

    fin.open("animal_names.txt"); // open file for reading

    // knowing the size of the file lets us treat
    // it like an array without using .push_back(value)
    for (int i = 0; i < count; i++) {
        fin >> array[i];           // read in animals
        for (auto &c : array[i]) { // c++ 11 style loop
            c = tolower(c);        // lowercase the animal name
        }
    }
    return array;
}*/

/**
 * Description:
 *      Finds partial matches in an array of strings and returns them. It
 *      doesn't matter where in the string the match is.
 * Params:
 *      vector<string>  array       - array to search
 *      string          substring   - substring to search for in each word
 * 
 * Returns:
 *      vector<string> - holding all the matches to substring
 */
/*vector<string> FindAnimals(vector<string> array, string substring) {
    vector<string> matches; // to hold any matches
    size_t found;           // size_t is an integer position of
                            // found item. -1 if its not found.

    for (int i = 0; i < array.size(); i++) { // loop through array
        found = array[i].find(substring);    // check for substr match
        if (found != string::npos) {         // if found >= 0 (its found then)
            matches.push_back(array[i]);     // add to matches
        }
    }

    return matches;
}*/

int main() {
    char k;                 // holder for character being typed
    string word = "";       // var to concatenate letters to
    int loc;                // location of substring to change its color

    ofstream fout("temp.txt");

    Timer T;   // create a timer
    T.Start(); // start it
    Trie dict;
    vector<string> matches;
    vector<string> words;
    string data;
    JsonFacade J("dict_w_defs.json");
    words = J.getKeys(); 

    bool isGood = true;

    for(int i = 0; i < words.size(); i++) {
      isGood = true;
      for(int j=0;j<words[i].size();j++){
        if(int(words[i][j]) < 97 || int(words[i][j]) > 122){
          isGood = false;
        }
      }
      if(isGood){
        dict.insert(words[i]);
      }
      
    }

  
    T.End(); // end the current timer
    
    // print out how long it took to load the animals file
    cout << T.Seconds() << " seconds to read in and print dictionary to list" << endl;
    cout << T.MilliSeconds() << " milli to read in and print dictionary to list" << endl;
    cout << T.NanoSeconds() << " nano to read in and print dictionary to list" << endl;

    cout << "Type keys and watch what happens. Type capital Z to quit." << endl;

    // While capital Z is not typed keep looping
    while ((k = getch()) != 'Z') {
       
        T.Start(); // start it
        // Tests for a backspace and if pressed deletes
        // last letter from "word".
        if ((int)k == 127) {
            if (word.size() > 0) {
                word = word.substr(0, word.size() - 1);
            }
        } else {
            // Make sure a letter was pressed and only letter
            if (!isalpha(k)) {
                cout << "Letters only!" << endl;
                continue;
            }

            // We know its a letter, lets make sure its lowercase.
            // Any letter with ascii value < 97 is capital so we
            // lower it.
            if ((int)k < 97) {
                k += 32;
            }
            word += k; // append char to word
        }

        // Find any animals in the array that partially match
        // our substr word

        matches.clear();
        matches = dict.find_all(word);
        

        /*if(word.size()>2){
          cout<<"matches:\n";
          for(int i=0;i<matches.size();i++){
            cout<<matches[i]<<endl;
          }
          cout<<"++++++++++++++\n";
        }*/


        if ((int)k != 32) { // if k is not a space print it
            T.End();
            cout << termcolor::red << word << termcolor::reset << endl << endl;
            cout << matches.size() << " words found in " << T.NanoSeconds() << " nanoseconds" << endl << endl;
            //cout << "Keypressed: " << termcolor::blue << k << " = " << (int)k << termcolor::reset << endl;
            //cout << "Current Substr: " << termcolor::red << word << termcolor::reset << endl;
            //cout << "Words Found: ";
            cout << termcolor::green;
            // This prints out all found matches
            for (int i = 0; i < matches.size() && i < 10; i++) {

                  for (int j = 0; j < matches[i].size(); j++) {
                      // if we are printing the substring turn it red
                      if (j <= word.size() - 1) {
                          cout << termcolor::red;
                      } else {
                          cout << termcolor::green;
                      }
                      cout << matches[i][j];
                  }
                  cout << termcolor::green;
                
                cout << " ";
            }
            cout << termcolor::reset << endl
                 << endl;
            }
          cout <<endl;
        }
    
    return 0;
}
