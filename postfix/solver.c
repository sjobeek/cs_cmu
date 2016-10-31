#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#define STACK_SIZE 1000

char equation_str[BUFSIZ]; // To contain single line of input


/** Implementation of Stack ADT Below **/

// Stack comprised of floats in an array for simplicity
struct FloatStack {
    float items[STACK_SIZE]; // Contents of stack
    int num;                 // Number of items on stack - intialization required
};
typedef struct FloatStack FloatStack; // Define a type to hide the struct-based implementation

float popf(FloatStack* stack){
    assert(stack->num > 0 && "Nothing on stack to pop!"); // Ensure there's always something to pop
    stack->num -= 1; 
    return stack->items[stack->num + 1]; // Don't forget +1 here...
}

void pushf(FloatStack* stack, float item){
    assert(stack->num < STACK_SIZE && "No room left on stack!"); // Ensure there's always room to push
    stack->num += 1;
    stack->items[stack->num] = item;
}

float peekf(FloatStack* stack){
    assert(stack->num > 0 && "Nothing on stack to peek at!"); // Empty stack! 
    return stack->items[stack->num];
}

// Initializxation of stack is required before use
void init_stack(FloatStack* stack){
    stack->num = 0;
}
/** End implementation of Stack ADT**/


// Computes RPN calculation on string using specified stack.  Result is last remaining float on stack.
void computeRPN(char* equation_str, FloatStack* stack_ptr){

    const char* seps = " \t\n\r"; // Equation argument separator tokens
    char* token; // Pointer to matched token string
    char* end; // Pointer to end of matched token (if equal to token, error!)
    float tokenval; // Floating-point value of token, if applicable 
    float arg1, arg2; // Arguments to each operation

    // Loop through every token in string (only one pass is required for RPN calculator algorithm)
    for(token = strtok(equation_str, seps); token ;token = strtok(0, seps)) {
        printf( " %s\n", token ); 
        tokenval = strtof(token, &end); // tokenval will contain the floating-point value if a number, 0 otherwise

        if (end != token)  // This was a valid number (needed to disambiguate 0 result of strtof() on error from actual 0.0 value)
            pushf(stack_ptr, tokenval);
        // Otherwise, not a number...  test for operators and handle errors for unknown tokens etc.
        else if(stack_ptr->num < 2){ // All operators require two numbers as arguments. 
            printf("Not enough values to apply ( %s ) operator! \n", token);
            printf("Ignoring it. Double check your equation...\n");
        }
        else if(*token == '+'){
            arg2 = popf(stack_ptr);
            arg1 = popf(stack_ptr);
            pushf(stack_ptr, arg1 + arg2);
            printf("( %f )\n", peekf(stack_ptr));
        }
        else if(*token == '-'){
            arg2 = popf(stack_ptr);
            arg1 = popf(stack_ptr);
            pushf(stack_ptr, arg1 - arg2);
            printf("( %f )\n", peekf(stack_ptr));
        }
        else if(*token == '/'){
            arg2 = popf(stack_ptr);
            arg1 = popf(stack_ptr);
            pushf(stack_ptr, arg1 / arg2);
            printf("( %f )\n", peekf(stack_ptr));
        }
        else if(*token == '*'){
            arg2 = popf(stack_ptr);
            arg1 = popf(stack_ptr);
            pushf(stack_ptr, arg1 * arg2);
            printf("( %f )\n", peekf(stack_ptr));
        }
        else
            printf("Ignoring Unrecognized Characters: %s\n", token);
    }
}


/** Implementation of main calculator program **
  * 1) Acquire one-line equation from user in RPN format
  * 2) Perform RPN computation on stack
  * 3) Handle error cases and display the result
  */
int main() {
    FloatStack fstack;
    init_stack(&fstack); // Initializxation of stack is required
    int return_val = -1; // 0 for success, -1 for failure

    while(1){ // Loop until exit condition met

        // ### 1) Acquire one-line equation from user ###

        printf("Enter an equation in RPN:\n");
        fgets(equation_str, sizeof(equation_str), stdin); // Not completely safe, but sufficient for small inputs on homework...
        
        // Get rid of annoying newline character that can show up at end of string as a result of fgets behavior
        char* dumb_newline_ptr = strchr(equation_str, '\n');
        if (dumb_newline_ptr != NULL)
          *dumb_newline_ptr = '\0';

        if (!strcmp(equation_str,"exit") || 
            !strcmp(equation_str,"Exit") || 
            !strcmp(equation_str,"EXIT")) { // Allow for exiting the program
            printf("\nExiting program. Thank you.\n");
            return return_val;
        }


        // ### 2) Perform calculation using RPN algorithm: Result remains on stack ###

        computeRPN(equation_str, &fstack);
        

        // ### 3) Calculation complete:  Handle failure cases and display solution (last value on stack) ###
        
        if (fstack.num == 1){ // Correctly formatted RPN equation will leave one value on the stack
            printf("Solution: %f\n", popf(&fstack));
            return_val = 0; //Success
        }
        else if (fstack.num > 1){ // Should always be one number left on the stack after valid equation.
            printf("Malformed equation! Leftover terms.\n");
            printf("Solution below may be incorrect.\n"); // Might still be correct, so give a chance to display
            printf("Potential Solution: %f\n", popf(&fstack));
            return_val = -1; //Error
        } 
        else { // Empty stack = no result: Return failure
            return_val = -1; //Error
        }

        //printf("\nPress any key to exit. Thank you.\n");
        //getch(); //Hold the screen so output can be seen... 
        //return return_val;
    }
}