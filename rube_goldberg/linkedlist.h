/* Doubly Linked List implementation */
/* from https://gist.github.com/mycodeschool/7429492 */

#include<stdio.h>
#include<stdlib.h>

struct Node  {
    int data;
    char firstname[30];
    char lastname[30];
    int age;
    struct Node* right;
    struct Node* left;
};

typedef struct Node** DLList; // Typedef for doubly linked list

//Creates a new Node and returns pointer to it. 

struct Node** GetNewList();

struct Node* GetNewNode(int x);

//Inserts a Node at head of doubly linked list
void InsertAtHead(DLList list_handle, int x);
//Inserts a Node at tail of Doubly linked list
void InsertAtTail(DLList list_handle, int x);

//Prints all the elements in linked list in forward traversal order
void Print(DLList list_handle);

//Prints all elements in linked list in reverse traversal order. 
void ReversePrint(DLList list_handle);
