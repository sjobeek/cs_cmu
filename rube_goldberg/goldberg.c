#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "linkedlist.h"

 
/* Ref: http://ideone.com/l23He */
const char* getfield(char* line, int num, char* sep)
{
    const char* tok;
    char* last_token = strdup(line); // Initialize to entire line

    for (tok = strtok(line, sep);
            tok && *tok;
            tok = strtok(NULL, sep))
    {
        // Get rid of annoying newline character that can show up at end of string as a result of fgets behavior
        char* dumb_newline_ptr = strchr(tok, '\n');
        if (dumb_newline_ptr != NULL)
            *dumb_newline_ptr = '\0';
        if(tok[0] == ' ') // Skip leading space if it exists
            tok++; 

        strcpy(last_token, tok);
        if (!--num){
            free(last_token);
            return tok;
        }

    }
    //TODO Ensure last_token is always free'd (possible memory leak)
    return last_token; // Always return last token instead of null
}

// Reads in a single line of text, and parses it into a pointer to a node
Nodeptr LineToNodeptr(char* text_line){
    char tmp[1024];
    char tmpname[1024];
    char fullname[1024];
    char lastname[1024];
    char firstname[1024];
    char birthdate[1024];
    int age=0;

    // Extract names
    strcpy(tmp, text_line);
    strcpy(fullname, getfield(tmp, 1, ","));
    //printf("Full Name is %s\n", fullname);
    
    strcpy(tmpname, fullname);
    strcpy(lastname, getfield(tmpname, 99, " ")); 
    //printf("Last name is %s\n", lastname); 

    strcpy(tmpname, fullname);
    strcpy(firstname, getfield(tmpname, 1, " "));
    //printf("First name is %s\n", firstname);

    // Extract age
    strcpy(tmp, text_line);
    age = atoi(getfield(tmp, 2, ","));
    //printf("Age is %i\n", age);

    // Extract birthdate
    strcpy(tmp, text_line);
    strcpy(birthdate, getfield(tmp, 3, ","));
    //printf("Birthdate is %s\n", birthdate);

    // Create node and clean up
    Nodeptr newNode = GetNewNode(lastname, firstname, age, birthdate);
    return newNode;
}

void ReadFileToList(char* filename, Nodeptr* list_handle){

    FILE* stream = fopen (filename, "rb");
    char line[1024];


    while (fgets(line, 1024, stream) != NULL)
    {
        Nodeptr newNode = LineToNodeptr(line);
        InsertAtTail(list_handle, newNode);        

    }
    fclose(stream);
}

void DequePrintReque(DLList queue){
    // deques, prints then re-queue items, waiting for input. 
    int len_q = ListLength(queue);
    for(int n=0; n<len_q; n++){
        Nodeptr popped_node = Dequeue(queue);
        PrintNode(popped_node);
        Enqueue(queue, popped_node); 
    }
    //printf("End\n");
    //PrintList(queue);
    return;
}

void PressAnyKey(){
    printf("\nPress any key to continue...\n");
    getch(); //Hold the screen so output can be seen... 
}



char* GetUserInput(){
    char input_str[1024];
    strcpy(input_str, "");
    while(strlen(input_str) < 4){
        printf("Enter new user data in following format:  Full Name, Age, Birthday\n");
        fgets(input_str, sizeof(input_str), stdin); // Not completely safe, but sufficient for small inputs on homework...
        
        // Get rid of annoying newline character that can show up at end of string as a result of fgets behavior
        char* dumb_newline_ptr = strchr(input_str, '\n');
        if (dumb_newline_ptr != NULL)
          *dumb_newline_ptr = '\0';
    }
    return strdup(input_str); // Ensure this allocated memory is free'd!
}


int main()
{
     

    Nodeptr head_node;
    DLList queue = &head_node;
    InitQueue(queue);


    // Read in file to queue (double-linked list) 
    ReadFileToList("InputFile.dat", queue);

    // Display contents of the queue
    printf("\nQueue Data in List Order: \n");
    DequePrintReque(queue);
    PressAnyKey();

    // Stack to be used to reverse queue. 
    Nodeptr head_node2;
    DLList stack = &head_node2;
    InitStack(stack);

    // Insert all items into stack
    int len_q = ListLength(queue);
    for(int n=0; n<len_q; n++){
        Nodeptr tmp_node = Dequeue(queue);
        StackPush(stack, tmp_node); 
    }

    // Re-insert all items into queue in reverse order
    for(int n=0; n<len_q; n++){
        Nodeptr tmp_node = StackPop(stack);
        Enqueue(queue, tmp_node); 
    }

    // Display contents of the queue
    printf("\nQueue Data in Reversed Order: \n");
    DequePrintReque(queue);
    PressAnyKey();

    
    // Inserts all elements of queue into a balanced binary_tree
    Nodeptr head_node3;
    DLList binary_tree = &head_node3;
    InitBT(binary_tree);
    
    InsertListtoBT(binary_tree, queue);

    // Recursively print binary tree in pre-order, starting from head node
    printf("\nBinary Tree in Pre-Order: \n");
    PrintBTPre(*binary_tree);
    PressAnyKey();

    // Insert binary_tree into list
    Nodeptr head_node4;
    DLList linked_list = &head_node4;
    InitList(linked_list);

    InsertBTtoList(*binary_tree, linked_list);
    printf("\nLinked List In Binary-Tree Order: \n");
    PrintList(linked_list);
    PressAnyKey();


    //TODO:  Quicksort ascending + print
    //QuickSortPartition(linked_list)

    // Get input from user
    char* input_str = GetUserInput();
    Nodeptr new_node =  LineToNodeptr(input_str);
    free(input_str);

    InsertAtTail(linked_list, new_node);
    PrintList(linked_list);
    PressAnyKey();

    

}