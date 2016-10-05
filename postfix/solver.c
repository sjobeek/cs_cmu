#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#define STACK_SIZE 1000

char equation_str[BUFSIZ]; // To contain single line of input

struct FloatStack1k {
    float items[STACK_SIZE]; // Contents of stack
    int num;                 // Number of items on stack
};

float popf(struct FloatStack1k* stack){
    assert(stack->num > 0 && "Nothing on stack to pop!"); // Ensure there's always something to pop
    stack->num -= 1; 
    return stack->items[stack->num + 1]; // Don't forget +1 here...
}

void pushf(struct FloatStack1k* stack, float item){
    assert(stack->num < STACK_SIZE && "No room left on stack!"); // Ensure there's always room to push
    stack->num += 1;
    stack->items[stack->num] = item;
}

float peekf(struct FloatStack1k* stack){
    assert(stack->num > 0 && "Nothing on stack to peek at!"); // Empty stack! 
    return stack->items[stack->num];
}

void init_stack(struct FloatStack1k* stack){
    stack->num = 0;
}


int main() {
    struct FloatStack1k fstack;
    init_stack(&fstack); // Initializxation
    const char* seps = " \t\n\r"; // Separator tokens
    char* token; // Pointer to matched token string
    char* end; // Pointer to end of matched token (if equal to token, error!)
    float tokenval, final_value;
    float arg1, arg2; // Arguments to each operation

    printf("Enter an equation in RPN:\n");
    fgets(equation_str, sizeof(equation_str), stdin); // Not completely safe, but sufficient for small inputs on homework...
    
    // Get rid of annoying newline that shows up (sometimes?!)
    char* dumb_newline_ptr;
    if ((dumb_newline_ptr = strchr(equation_str, '\n')) != NULL)
      *dumb_newline_ptr = '\0';

    printf("Entered equation:\n");
    printf("%s\n", equation_str);

    // Loop through every token in string
    for(token = strtok(equation_str, seps); token ;token = strtok(0, seps)) {
        printf( " %s\n", token );
        tokenval = strtof(token, &end);
        if (end != token)  // This was not a valid number!
            pushf(&fstack, tokenval);
        else if(fstack.num < 2){
            printf("Not enough values to apply ( %s ) operator! \n", token);
            printf("Ignoring it. Double check your equation...\n");
        }
        else if(*token == '+'){
            arg2 = popf(&fstack);
            arg1 = popf(&fstack);
            pushf(&fstack, arg1 + arg2);
            printf("( %f )\n", peekf(&fstack));
        }
        else if(*token == '-'){
            arg2 = popf(&fstack);
            arg1 = popf(&fstack);
            pushf(&fstack, arg1 - arg2);
            printf("( %f )\n", peekf(&fstack));
        }
        else if(*token == '/'){
            arg2 = popf(&fstack);
            arg1 = popf(&fstack);
            pushf(&fstack, arg1 / arg2);
            printf("( %f )\n", peekf(&fstack));
        }
        else if(*token == '*'){
            arg2 = popf(&fstack);
            arg1 = popf(&fstack);
            pushf(&fstack, arg1 * arg2);
            printf("( %f )\n", peekf(&fstack));
        }
        else
            printf("Ignoring Unrecognized Characters: %s\n", token);
    }

    if (fstack.num != 1)
        printf("Malformed equation! Leftover terms.\n");
    else{
        final_value = popf(&fstack);
        printf("Solution: %f\n", final_value);
    }
    getch(); //Hold the screen so output can be seen... 
    return final_value;
}