/* Doubly Linked List implementation */
/* Reference: https://gist.github.com/mycodeschool/7429492 */

#include<stdio.h>
#include<stdlib.h>
#include "linkedlist.h"

struct Node** GetNewList(){
    struct Node* listhead = NULL;
    struct Node** list_handle = &listhead; // empty list. set head as NULL. 
    return list_handle;
}

//Creates a new Node and returns pointer to it. 
struct Node* GetNewNode(int x) {
    struct Node* newNode
        = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = x;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

//Inserts a Node at head of doubly linked list
void InsertAtHead(struct Node** list_handle, int x) {
    struct Node* newNode = GetNewNode(x);
    if(*list_handle == NULL) {
        *list_handle = newNode;
        return;
    }
    (*list_handle)->left = newNode;
    newNode->right = *list_handle; 
    *list_handle = newNode;
}

//Inserts a Node at tail of Doubly linked list
void InsertAtTail(struct Node** list_handle, int x) {
    struct Node* temp = *list_handle;
    struct Node* newNode = GetNewNode(x);
    if(*list_handle == NULL) {
        *list_handle = newNode;
        return;
    }
    while(temp->right != NULL) temp = temp->right; // Go To last Node
    temp->right = newNode;
    newNode->left = temp;
}

//Prints all the elements in linked list in forward traversal order
void Print(struct Node** list_handle) {
    struct Node* temp = *list_handle;
    printf("Forward: ");
    while(temp != NULL) {
        printf("%d ",temp->data);
        temp = temp->right;
    }
    printf("\n");
}

//Prints all elements in linked list in reverse traversal order. 
void ReversePrint(struct Node** list_handle) {
    struct Node* temp = *list_handle;
    if(temp == NULL) return; // empty list, exit
    // Going to last Node
    while(temp->right != NULL) {
        temp = temp->right;
    }
    // Traversing backward using left pointer
    printf("Reverse: ");
    while(temp != NULL) {
        printf("%d ",temp->data);
        temp = temp->left;
    }
    printf("\n");
}

