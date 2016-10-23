#include<stdio.h>
#include<stdlib.h>
#include "linkedlist.h"

int main() {

    // Retrieve new handle to a Doubly Linked List
    DLList list_handle = GetNewList();
    // Calling an Insert and printing list both in forward as well as reverse direction. 
    InsertAtTail(list_handle, 2); Print(list_handle); ReversePrint(list_handle);
    InsertAtTail(list_handle, 4); Print(list_handle); ReversePrint(list_handle);
    InsertAtHead(list_handle, 6); Print(list_handle); ReversePrint(list_handle);
    InsertAtTail(list_handle, 8); Print(list_handle); ReversePrint(list_handle);
    
}