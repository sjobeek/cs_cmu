/* Doubly Linked List implementation */
/* Reference: https://gist.github.com/mycodeschool/7429492 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"


void InitList(Nodeptr* list_handle){
    // Allocate node at head of list, then list itself
    Nodeptr newNode
        = (struct Node*)calloc(1, sizeof(struct Node));
    newNode = NULL; //Indicate empty
    *list_handle = newNode;
}

//Creates a new Node and returns pointer to it. 
Nodeptr GetNewNode(const char* lastname, const char* firstname, int age, const char* birthdate) {
    struct Node* newNode
        = (struct Node*)calloc(1, sizeof(struct Node));
    // Fill data
    strcpy(newNode->lastname, lastname);
    strcpy(newNode->firstname, firstname);
    newNode->age = age;
    strcpy(newNode->birthdate, birthdate);
    // Placeholders for left/right links
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

//Inserts a Node at head of doubly linked list
void InsertAtHead(Nodeptr* list_handle, Nodeptr newNode) {
    if(*list_handle == NULL) {
        // TODO: Free memory of null node
        *list_handle = newNode;
        return;
    }
    (*list_handle)->left = newNode;
    newNode->right = *list_handle; 
    *list_handle = newNode;
}

//Inserts a Node at tail of Doubly linked list
void InsertAtTail(Nodeptr* list_handle, Nodeptr newNode) {
    struct Node* temp = *list_handle;
    if(*list_handle == NULL) {
        *list_handle = newNode;
        return;
    }
    while(temp->right != NULL) temp = temp->right; // Go To last Node
    temp->right = newNode;
    newNode->left = temp;
}

//Prints all the elements in linked list in forward traversal order
void PrintList(Nodeptr* list_handle) {
    struct Node* temp = *list_handle;
    printf("Forward: \n");
    while(temp != NULL) {
        printf("Lastname: %s, ", temp->lastname);
        printf("Firstname: %s, ", temp->firstname);
        printf("Age: %i, ", temp->age);
        printf("Birthdate: %s\n", temp->birthdate);
        temp = temp->right;
    }
    printf("\n");
}

//Prints all elements in linked list in reverse traversal order. 
void ReversePrintList(Nodeptr* list_handle) {
    struct Node* temp = *list_handle;
    if(temp == NULL) return; // empty list, exit
    // Going to last Node
    while(temp->right != NULL) {
        temp = temp->right;
    }
    // Traversing backward using left pointer
    printf("Reverse: \n");
    while(temp != NULL) {
        printf("Lastname: %s, ", temp->lastname);
        printf("Firstname: %s, ", temp->firstname);
        printf("Age: %i, ", temp->age);
        printf("Birthdate: %s\n", temp->birthdate);
        temp = temp->left;
    }
    printf("\n");
}

