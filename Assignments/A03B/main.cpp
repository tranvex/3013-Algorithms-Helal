///////////////////////////////////////////////////////////////////////////////
//
// Author:           Yoseph Helal
// Email:            tranvex@gmail.com
// Label:            P01
// Title:            Program 01 - Array Based Stack
// Course:           3013
// Semester:         Spring 2022
//
// Description:
//       Overview of a class implementing an array based stack
//
//
/////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>

using namespace std;

/**
 * ArrayStack
 * 
 * Description:
 *      Array based stack
 * 
 * Public Methods:
 *      - See class below
 * 
 * Usage: 
 *      - See main program
 *      
 */
class ArrayStack {
private:
    int *A;   // pointer to array of int's
    int top;  // top of stack
    //double threshHold = .85;

    // top = number of items in the stack + 1
    // size = array size

    // size = 100
    // (top + 1) / size

public:
  // Default Values
  double growThresh = 0.85;
  double shrinkThresh = 0.15;
  double growMul = 2.0;
  double shrinkMul = 0.5;
  int commands = 0;
  int resizes = 0;
  int maxSize = 0;
  int size; // current max stack size
  
    /**
  * ArrayStack
  * 
  * Description:
  *      Constructor no params
  * 
  * Params:
  *     - None
  * 
  * Returns:
  *     - NULL
  */
    ArrayStack() {
        size = 10;
        A = new int[size];
        top = -1;
    }

    /**
  * ArrayStack
  * 
  * Description:
  *      Constructor size param
  * 
  * Params:
  *     - int size
  * 
  * Returns:
  *     - NULL
  */
    ArrayStack(int s) {
        size = s;
        A = new int[s];
        top = -1;
    }

    /**
  * Public bool: Empty
  * 
  * Description:
  *      Stack empty?
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [bool] true = empty
  */
    bool Empty() {
        return (top <= -1);
    }

    /**
  * Public bool: Full
  * 
  * Description:
  *      Stack full?
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [bool] true = full
  */
    bool Full() {
        return (top >= size - 1);
    }

    /**
  * Public int: Peek
  * 
  * Description:
  *      Returns top value without altering the stack
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [int] top value if any
  */
    int Peek() {
        if (!Empty()) {
            return A[top];
        }

        return -99; // some sentinel value
                    // not a good solution
    }

    /**
  * Public int: Pop
  * 
  * Description:
  *      Returns top value and removes it from stack
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [int] top value if any
  */
    int Pop() {
        if (!Empty()) {
            return A[top--];
            checkResize();
        }

        return -99; // some sentinel value
                    // not a good solution
    }

    /**
  * Public void: Print
  * 
  * Description:
  *      Prints stack to standard out
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      NULL
  */
    void Print() {
        for (int i = 0; i <= top; i++) {
            cout << A[i] << " ";
        }
        cout << endl;
    }

    /**
  * Public bool: Push
  * 
  * Description:
  *      Adds an item to top of stack
  * 
  * Params:
  *      [int] : item to be added
  * 
  * Returns:
  *      [bool] ; success = true
  */
    bool Push(int x) {
        if (Full()) {
            ContainerGrow();
        }
        if (!Full()) {
            A[++top] = x;

            checkResize();
            return true;
        }

        return false;
    }

    /**
  * Public void: Resize
  * 
  * Description:
  *      Resizes the container for the stack by doubling
  *      its capacity
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      NULL
  */
    void ContainerGrow() {
        int newSize = size * growMul;    // double size of original
        maxSize = newSize; // Set new max size because container grows
        int *B = new int[newSize]; // allocate new memory

        for (int i = 0; i < top; i++) { // copy values to new array
            B[i] = A[i];
        }

        delete[] A; // delete old array

        size = newSize; // save new size

        A = B; // reset array pointer
    }

    void ContainerShrink() {
        int newSize = size * shrinkMul;    // halve size of original
        if (newSize >= 10) {
          int *B = new int[newSize]; // allocate new memory

          for (int i = 0; i < top; i++) { // copy values to new array
            B[i] = A[i];
          }

          delete[] A; // delete old array

          size = newSize; // save new size

          A = B; // reset array pointer
        }

    }

    void checkResize() {
        double check = double(top) / size;
        if (check >= growThresh) {
          ContainerGrow();
          resizes++;
        }
        if (size > 10 && check <= shrinkThresh) {
          ContainerShrink();
          resizes++;
        }
    }
};

// MAIN DRIVER
// Simple Array Based Stack Usage:
int main(int argc, char *argv[]) {
    ArrayStack stack;              // stack instance
    ifstream fin;        
    string file = "nums_test.dat"; // Default file name
    int num = 0;                    // value to read in from file

    if (argc == 2){
      file = argv[1];
    }
    else if (argc == 5) {
      stack.growThresh = atof(argv[1]);
      stack.shrinkThresh = atof(argv[2]);
      stack.growMul = atof(argv[3]);
      stack.shrinkMul = atof(argv[4]);
    }
    else if (argc == 6) {
      file = argv[1];
      stack.growThresh = atof(argv[2]);
      stack.shrinkThresh = atof(argv[3]);
      stack.growMul = atof(argv[4]);
      stack.shrinkMul = atof(argv[5]);
      
    }
    
    /*int r = 0;

    for (int i = 0; i < 20; i++) {
        r = rand() % 100;
        r = i + 1;
        if (!stack.Push(r)) {
            cout << "Push failed" << endl;
        }
    }

    for (int i = 0; i < 7; i++) {
        stack.Pop();
    }*/
    
    
    fin.open(file);
    
    while (!fin.eof()) {
      stack.commands++;
      fin >> num;
      if (num %2 == 0) {
        stack.Push(num);
      }
      if (num %2 == 1) {
        stack.Pop();
      }
    }
    
    cout << "######################################################################" << endl;
    cout << "Assignment 4 - Resizing the Stack" << endl;
    cout << "CMPS 3013" << endl;
    cout << "Yoseph Helal" << endl << endl;
    cout << "Config Params:" << endl;
    cout << "Full Threshold: " << stack.growThresh << endl;
    cout << "Shrink Threshold: " << stack.shrinkThresh << endl;
    cout << "Grow Ratio: " << stack.growMul << endl;
    cout << "Shrink Ratio: " << stack.shrinkMul << endl << endl;
    cout << "Processed " << stack.commands << " Commands" << endl << endl;
    cout << "Max Stack Size: " << stack.maxSize << endl;
    cout << "End Stack Size: " << stack.size << endl;
    cout << "Stack Resized: " << stack.resizes << endl;
    cout << "######################################################################" << endl;

    //stack.Print();
    return 0;
}
