/* Doubly Linked List implementation */
/* from https://gist.github.com/mycodeschool/7429492 */

#include<stdio.h>
#include<stdlib.h>

struct Node  {
    char firstname[30];
    char lastname[30];
    int age;
    char birthdate[30];
    int null_flag; // set to 1 when this is a place-holder null element
    struct Node* right;
    struct Node* left;
};

typedef struct Node* Nodeptr; // Pointer to node
typedef struct Node** DLList; // Typedef for doubly linked list

//Creates a new Node and returns pointer to it. 

void InitList(Nodeptr* list_handle);

Nodeptr GetNewNode(const char* lastname, const char* firstname, int age, const char* birthdate);

//Inserts a Node at head of doubly linked list
void InsertAtHead(DLList list_handle, Nodeptr newNode);
//Inserts a Node at tail of Doubly linked list
void InsertAtTail(DLList list_handle, Nodeptr newNode);

//Prints all the elements in linked list in forward traversal order
void PrintList(DLList list_handle);

//Prints all elements in linked list in reverse traversal order. 
void ReversePrintList(DLList list_handle);
