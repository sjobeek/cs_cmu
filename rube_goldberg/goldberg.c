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

void ReadFileToList(char* filename, Nodeptr* list_handle){

    FILE* stream = fopen (filename, "rb");
    char line[1024];
    char tmp[1024];
    char tmpname[1024];
    char fullname[1024];
    char lastname[1024];
    char firstname[1024];
    char birthdate[1024];
    int age;


    while (fgets(line, 1024, stream) != NULL)
    {
        // Initialize variables to avoid accidental transfer from previous record
        //line=""; tmp=""; birthdate="";
        //tmpname=""; fullname=""; lastname=""; firstname="";
        //age=0;

        printf("\n");
        printf(line);

        // Extract names
        strcpy(tmp, line);
        strcpy(fullname, getfield(tmp, 1, ","));
        printf("Full Name is %s\n", fullname);
        
        strcpy(tmpname, fullname);
        strcpy(lastname, getfield(tmpname, 99, " ")); 
        printf("Last name is %s\n", lastname); 

        strcpy(tmpname, fullname);
        strcpy(firstname, getfield(tmpname, 1, " "));
        printf("First name is %s\n", firstname);

        // Extract age
        strcpy(tmp, line);
        age = atoi(getfield(tmp, 2, ","));
        printf("Age is %i\n", age);

        // Extract birthdate
        strcpy(tmp, line);
        strcpy(birthdate, getfield(tmp, 3, ","));
        printf("Birthdate is %s\n", birthdate);


        // Create node and clean up
        Nodeptr newNode = GetNewNode(lastname, firstname, age, birthdate);
        
        InsertAtTail(list_handle, newNode);        

    }
    fclose(stream);

}
 
int main()
{
     
    //Initialize linked list
    //Nodeptr null_node = NULL;
    //DLList list_handle = &null_node;

    Nodeptr head_node;
    InitList(&head_node);

    ReadFileToList("InputFile.dat", &head_node);


    PrintList(&head_node);
    ReversePrintList(&head_node);
}