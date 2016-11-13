/* Doubly Linked List implementation */
/* Reference: https://gist.github.com/mycodeschool/7429492 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "linkedlist.h"


void InitList(Nodeptr* list_handle){
    // Allocate node at head of list, then list itself
    Nodeptr newNode
        = (struct Node*)calloc(1, sizeof(struct Node));
    newNode = NULL; //Indicate empty
    *list_handle = newNode;
}

// Same procedure for binary tree, queue, and stack data types
void InitBT(Nodeptr* list_handle){
    InitList(list_handle);
}

void InitQueue(Nodeptr* list_handle){
    InitList(list_handle);
}

void InitStack(Nodeptr* list_handle){
    InitList(list_handle);
}

// TODO: Implement memory-freeing operations to clear nodes and lists

//Creates a new Node and returns pointer to it. 
Nodeptr GetNewNode(const char* lastname, const char* firstname, int age, const char* birthdate) {
    assert(strlen(lastname) < 60);
    assert(strlen(firstname) < 60);
    assert(strlen(birthdate) < 60);

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
    newNode->bt_left = NULL;
    newNode->bt_right = NULL;
    return newNode;
}

int ListLength(Nodeptr* list_handle){
    if(*list_handle == NULL) {
        return 0;
    }
    struct Node* temp = *list_handle;
    int n = 1;
    while(temp->right != NULL){
        n++;
        temp = temp->right; // Go To last Node  
    } 
    return n;
}

void StackPush(Nodeptr* list_handle, Nodeptr newNode){
    InsertAtHead(list_handle,newNode);
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

void Enqueue(Nodeptr* list_handle, Nodeptr newNode){
    InsertAtTail(list_handle,newNode);
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



Nodeptr StackPop(Nodeptr* list_handle){
    return PopFromHead(list_handle);
}

Nodeptr Dequeue(Nodeptr* list_handle){
    return PopFromHead(list_handle);
}

Nodeptr Peek(Nodeptr* list_handle){
    return *list_handle;
}

Nodeptr PopFromHead(Nodeptr* list_handle){
    assert(*list_handle != NULL && "List was empty!");
    Nodeptr temp = *list_handle;

    // Update new head of list
    *list_handle = (*list_handle)->right;
    if (*list_handle != NULL)
        (*list_handle)->left = NULL;

    // Clear links of node to be returned
    temp->left  = NULL;
    temp->right = NULL;

    return temp;

}

//Prints all the elements in linked list in forward traversal order
void PrintList(Nodeptr* list_handle) {
    struct Node* temp = *list_handle;
    while(temp != NULL) {
        printf("Lastname: %s, ", temp->lastname);
        printf("Firstname: %s, ", temp->firstname);
        printf("Age: %i, ", temp->age);
        printf("Birthdate: %s\n", temp->birthdate);
        temp = temp->right;
    }
    printf("\n");
}


void PrintNode(Nodeptr node_handle) {
    printf("Lastname: %s, ", node_handle->lastname);
    printf("Firstname: %s, ", node_handle->firstname);
    printf("Age: %i, ", node_handle->age);
    printf("Birthdate: %s", node_handle->birthdate);
    printf("\n");
}


// TODO: Move to binary tree file
void PrintBTPre(Nodeptr node_handle){
    if(node_handle == NULL)
        return;
    PrintNode(node_handle);
    PrintBTPre(node_handle->bt_left);
    PrintBTPre(node_handle->bt_right);
}

void PrintBT(Nodeptr node_handle){
    if(node_handle == NULL)
        return;
    PrintBT(node_handle->bt_left);
    PrintNode(node_handle);
    PrintBT(node_handle->bt_right);
}

void PrintBTPost(Nodeptr node_handle){
    if(node_handle == NULL)
        return;
    PrintBTPost(node_handle->bt_left);
    PrintBTPost(node_handle->bt_right);
    PrintNode(node_handle);

}

// Inserts all elements of queue into a balanced binary_tree
void InsertListtoBT(DLList binary_tree, DLList queue){
    
    // Extra queue to track insertion of binary tree elements
    Nodeptr head_node4;
    DLList bt_queue = &head_node4;
    InitQueue(bt_queue);

    // Insert root of binary tree
    Nodeptr bt_root_node = Dequeue(queue);
    Enqueue(bt_queue, bt_root_node);
    *binary_tree = bt_root_node;  // Assign handle to binary tree

    while(Peek(queue) != NULL){
        //Insert rest of binary tree from queue
        //printf("Head:  %s, %s\n", Peek(bt_queue)->lastname, Peek(bt_queue)->firstname);

        if(Peek(bt_queue)->bt_left == NULL){
            //printf("Add To Left:   ");
            Nodeptr tmp_node = Dequeue(queue);
            Enqueue(bt_queue, tmp_node);
            PrintNode(tmp_node);
            Peek(bt_queue)->bt_left = tmp_node;
        } 
        else if(Peek(bt_queue)->bt_right == NULL){
            //printf("Add to Right:  ");
            Nodeptr tmp_node = Dequeue(queue);
            Enqueue(bt_queue, tmp_node);
            PrintNode(tmp_node);
            Peek(bt_queue)->bt_right = tmp_node;
        }else{
            Dequeue(bt_queue);
            printf("Removing Full\n");
        }
    }
    //Empty bt_queue (clears right/left flags of all bt elements)
    while(Peek(bt_queue) != NULL) Dequeue(bt_queue);

}

void InsertBTtoList(Nodeptr bt_node_handle, DLList list_handle){
    if(bt_node_handle == NULL)
        return;
    InsertBTtoList(bt_node_handle->bt_left, list_handle);
    InsertAtTail(list_handle, bt_node_handle);
    InsertBTtoList(bt_node_handle->bt_right, list_handle);
}

/*
Nodeptr QuickSortPartition(DLList list_handle, Nodeptr left_node, Nodeptr right_node, Nodeptr pivot){
    left_node = *list_handle;
    right_node = *list_handle; // TODO: Point to end of list...
    pivot_node = *list_handle; // TODO: point to end - 1
    while(1){
        while(!strcomp(left_node->lastname, pivot_node->lastname)){ // left < right
            left_node = left_node->right;
        } 

        while(right_node != NULL && strcomp(right_node->right->lastname, pivot->lastname)){
            right_node = right_node->left
        }
        if(strcomp(left_node->lastname, pivot_node->lastname) >= 0)
            break;
        else{
            NodePtr tmp_node = right_node;
            right_node = left_node;
            left_node = right_node;
        }
    }
    NodePtr tmp_node = right_node;
    right_node = left_node;
    left_node = right_node;
    return left_node;

}*/