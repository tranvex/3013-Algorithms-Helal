/*****************************************************************************
*                    
*  Author:           Yoseph Helal
*  Email:            tranvex@gmail.com
*  Label:            A03B
*  Title:            Linked List Class
*  Course:           CMPS 3013
*  Semester:         Spring 2022
* 
*  Description:
*        This program implements a class that allows a linked list to be used just like 
*        an array. It overloads the "[]" (square brackets) to simulate accessing seperate 
*        array elements, but really it traverses the list to find the specified node using
*        an index value. It also overloads the "+" and "-" signs allowing a user to "add"
*        or "push" items onto the end of the list, as well as "pop" items off the end of our 
*        array. This class is not meant to replace the STL vector library, its simply a project
*        to introduce the beginnings of creating complex / abstract data types. 
*        
*  Usage: 
*       - $ ./main filename
*       - This will read in a file containing whatever values to be read into our list/array. 
*       
*  Files:            
*       main.cpp    : driver program 
*****************************************************************************/

#include <iostream>

using namespace std;

int A[100];

/**
 * Node
 * 
 * Description:
 *      Struct simply representing a node for our linked list. Each node
 *      holds a next pointer and an integer value.
 * 
 * Public Methods:
 *                          Node()                               
 *                          Node(int)
 * 
 * Private Methods:
 *      N/A
 * 
 * Usage: 
 * 
 *      Node H(int):                        // Create Instance of Node
 *      Node Y():                           // Create instance of Node
 *      
 */
struct Node {
    int x;
    Node *next;
    
    /**
     * Public : Node
     * 
     * Description:
     *      Node constructor
     * 
     * Params:
     *      N/A
     * 
     * Returns:
     *      A constructed node
     */
    Node() {
        x = -1;
        next = NULL;
    }
    
    /**
     * Public : Node
     * 
     * Description:
     *      Node constructor
     * 
     * Params:
     *      int n
     * 
     * Returns:
     *      A constructed node with passed in integer
     */
    Node(int n) {
        x = n;
        next = NULL;
    }
};


/**
 * List
 * 
 * Description:
 *      This class implements a linked list with a head and tail pointer
 *      and a size variable to keep track of the list size. The list has
 *      push, pop, insert, print, print tail capabilities. It also
 *      overloads the +, [] operators and ostream (cout).
 * 
 * Public Methods:
 *                          List()                               
 *      void                push(int val)
 *      void                insert(int val)
 *      void                PrintTail()
 *      string              Print()
 *      int                 Pop()
 * 
 * Private Methods:
 *      N/A
 * 
 * Usage: 
 * 
 *      List H;                                     // Create Instance of List 
 *      H.push(5);                                  // push 5 to list
 *      H.insert(6);                                // Insert 6 in order to list
 *      H.PrintTail();                              // Prints value of tail in list
 *      H.Print();                                  // Returns values of list as string, ready for printing
 *      H.Pop();                                    // Returns popped value from list
 *      
 */
class List {
private:
    Node *Head;
    Node *Tail;
    int Size;

public:
    /**
     * Public : List
     * 
     * Description:
     *      Constructs List class object
     * 
     * Params:
     *      N/A
     * 
     * Returns:
     *      Constructed List Class object
     */
    List() {
        Head = Tail = NULL;
        Size = 0;
    }

    /**
     * Public : Push
     * 
     * Description:
     *      Pushes integer value to linked list
     * 
     * Params:
     *      [int]     :  Value pushed
     * 
     * Returns:
     *      [type] Void
     */
    void Push(int val) {
        // allocate new memory and init node
        Node *Temp = new Node(val);

        if (!Head && !Tail) {
            Head = Tail = Temp;
        } else {
            Tail->next = Temp;
            Tail = Temp;
        }
        Size++;
    }

    /**
     * Public : Insert
     * 
     * Description:
     *      Inserts integer value in order to linked list
     * 
     * Params:
     *      [int]     :  Value inserted
     * 
     * Returns:
     *      [type] Void
     */
    void Insert(int val) {
        // allocate new memory and init node
        Node *Temp = new Node(val);

        // figure out where it goes in the list

        Temp->next = Head;
        Head = Temp;
        if (!Tail) {
            Tail = Head;
        }
        Size++;
    }

    /**
     * Public : PrintTail
     * 
     * Description:
     *      Prints value in the tail of the list
     * 
     * Params:
     *      N/A
     * 
     * Returns:
     *      [type] Void
     */
    void PrintTail() {
        cout << Tail->x << endl;
    }

    /**
     * Public : Print
     * 
     * Description:
     *      Returns string of values in list ready to be printed
     * 
     * Params:
     *      N/A
     * 
     * Returns:
     *      [String]     :  Values ready to be printed in this string
     */
    string Print() {
        Node *Temp = Head;
        string list;

        while (Temp != NULL) {
            list += to_string(Temp->x) + "->";
            Temp = Temp->next;
        }

        return list;
    }

    /**
     * Public : Pop
     * 
     * Description:
     *      Pops integer value from linked list
     * 
     * Params:
     *      N/A
     * 
     * Returns:
     *      [int]     :  Value popped from list
     */
    // not implemented
    int Pop() {
        Size--;
        return 0; //
    }

    /**
     * Public : Operator Overloading +
     * 
     * Description:
     *      Overloads the addition operator to seamlessly add two lists by
     *      creating new list with values added.
     * 
     * Params:
     *      [type]  RHS List   :  Right Hand Side list
     * 
     * Returns:
     *      [type]  List     :  Newly created list with added values
     */
    List operator+(const List &Rhs) {
        // Create a new list that will contain both when done
        List NewList;

        // Get a reference to beginning of local list
        Node *Temp = Head;

        // Loop through local list and Push values onto new list
        while (Temp != NULL) {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        // Get a reference to head of Rhs
        Temp = Rhs.Head;

        // Same as above, loop and push
        while (Temp != NULL) {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        // Return new concatenated version of lists
        return NewList;
    }

    /**
     * Public : Operator Overloading []
     * 
     * Description:
     *      Overloads [] to give list array-like random-access capabilities.
     * 
     * Params:
     *      [int]  Index number   :  Number of index needing to be accessed
     * 
     * Returns:
     *      [int]      : Value at index requested
     */
    // Implementation of [] operator.  This function returns an
    // int value as if the list were an array.
    int operator[](int index) {
        Node *Temp = Head;

        if (index >= Size) {
            cout << "Index out of bounds, exiting";
            exit(0);
        } else {

            for (int i = 0; i < index; i++) {
                Temp = Temp->next;
            }
            return Temp->x;
        }
    }

    /**
     * Public : Operator Overloading ostream (cout)
     * 
     * Description:
     *      Allows user to cout a list directly since ostream is
     *      overloaded
     * 
     * Params:
     *      [type]  ostream os   :  ostream object for printing
     *      [type]  List   :  List going to be printed
     * 
     * Returns:
     *      [type]  ostream os     :  ostream object with values printed
     */
    friend ostream &operator<<(ostream &os, List L) {
        os << L.Print();
        return os;
    }
};

int main(int argc, char **argv) {
    List L1;
    List L2;

    for (int i = 0; i < 25; i++) {
        L1.Push(i);
    }

    for (int i = 50; i < 100; i++) {
        L2.Push(i);
    }

    //cout << L1 << endl;
    L1.PrintTail();
    L2.PrintTail();

    List L3 = L1 + L2;
    cout << L3 << endl;

    cout << L3[5] << endl;
    return 0;
}
