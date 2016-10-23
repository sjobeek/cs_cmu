#include <stdio.h>
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
    return last_token; // Always return last token instead of null
}

 
int main()
{
     
    //Initialize linked list
    Nodeptr null_node = NULL;
    DLList list_handle = &null_node;

    

    FILE* stream = fopen ("InputFile.dat", "rb");
    char line[1024];
    while (fgets(line, 1024, stream) != NULL)
    {
       
        printf("\n");
        printf(line);

        // Extract names
        char* tmp = strdup(line);
        char* fullname = strdup(getfield(tmp, 1, ","));
        printf("Full Name is %s\n", fullname);
        free(tmp);
        
        char* tmpname = strdup(fullname);
        char* lastname = strdup(getfield(tmpname, 99, " ")); 
        printf("Last name is %s\n", lastname); 
        free(tmpname);

        tmpname = strdup(fullname);
        char* firstname = strdup(getfield(tmpname, 1, " "));
        printf("First name is %s\n", firstname);
        free(tmpname);
        free(fullname);

        // Extract age
        tmp = strdup(line);
        int age = atoi(getfield(tmp, 2, ","));
        printf("Age is %i\n", age);
        free(tmp);

        // Extract birthdate
        tmp = strdup(line);
        char* birthdate = strdup(getfield(tmp, 3, ","));
        printf("Birthdate is %s\n", birthdate);
        free(tmp);

        // Create node and clean up
        Nodeptr newNode = GetNewNode(lastname, firstname, age, birthdate);
        free(firstname); free(lastname); free(birthdate);

        
        InsertAtTail(list_handle, newNode);        

    }

    PrintList(list_handle);
    ReversePrintList(list_handle);
}