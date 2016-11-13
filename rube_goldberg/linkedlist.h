/* Doubly Linked List implementation */
/* from https://gist.github.com/mycodeschool/7429492 */

#include<stdio.h>
#include<stdlib.h>

struct Node  {
    char firstname[60];
    char lastname[60];
    int age;
    char birthdate[60];
    struct Node* right; // Linked-list links
    struct Node* left;
    struct Node* bt_right; // Binary Tree links (separate to queue BT elements)
    struct Node* bt_left; 
};

typedef struct Node* Nodeptr; // Pointer to node
typedef struct Node** DLList; // Typedef for doubly linked list

//Creates a new Node and returns pointer to it. 

void InitList(Nodeptr* list_handle);
void InitBT(Nodeptr* list_handle);
void InitQueue(Nodeptr* list_handle);
void InitStack(Nodeptr* list_handle);

Nodeptr GetNewNode(const char* lastname, const char* firstname, int age, const char* birthdate);

//Inserts a Node at head of doubly linked list
void InsertAtHead(DLList list_handle, Nodeptr newNode);
//Inserts a Node at tail of Doubly linked list
void InsertAtTail(DLList list_handle, Nodeptr newNode);

// Pops head from doubly-linked list
Nodeptr PopFromHead(Nodeptr* list_handle);

//Prints all the elements in linked list in forward traversal order
void PrintList(DLList list_handle);

// Print a single node
void PrintNode(Nodeptr node_handle);

// Returns length of a list
int ListLength(Nodeptr* list_handle);

//Prints all elements in linked list in reverse traversal order. 
void ReversePrintList(DLList list_handle);

void StackPush(Nodeptr* list_handle, Nodeptr newNode);
void Enqueue(Nodeptr* list_handle, Nodeptr newNode);

Nodeptr StackPop(Nodeptr* list_handle);
Nodeptr Dequeue(Nodeptr* list_handle);

// Returns data element at the front of the queue or stack
Nodeptr Peek(Nodeptr* list_handle);

// Binary Tree related functions
void InsertListtoBT(DLList binary_tree, DLList queue);
void InsertBTtoList(Nodeptr bt_node_handle, DLList list_handle);
void PrintBTPre(Nodeptr node_handle);
void PrintBT(Nodeptr node_handle);
void PrintBTPost(Nodeptr node_handle);