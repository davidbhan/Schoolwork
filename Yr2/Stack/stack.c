#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Stack structure
struct Stack {
    int elements; // Num elements currently in the stack
    unsigned capacity; // Maximum size of the stack
    int* array; // Array address of the stack
};

// Creates a stack of given capacity
struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack)); // Allocates space for a stack
    stack->capacity = capacity; // Sets the max size of the stack
    stack->elements = 0; // Initializes size of stack to 0;
    stack->array = (int*) malloc(stack->capacity * sizeof(int)); // Creates a pointer to an array memory space of our capacity
    return stack;
}

// Checks if stack is full by comparing number of elements to capacity
int isFull(struct Stack* stack) {
    return stack->elements == stack->capacity;
}

// Check if stack is empty by bhecking if number of elements is zero
int isEmpty(struct Stack* stack) {
    return stack->elements == 0;
}

// Adds an item to stack, increases number of elements by 1
void push(struct Stack* stack, int item) {
    if (isFull(stack)) {
        return;
    }
    stack->array[stack->elements] = item; // Add element to array
    stack->elements++; // Increase element counter
    //printf("%d pushed to stack\n", item);
}

// Returns the top value of the stack, and decreases the element counter
void pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("empty stack\n");
        return;
    }
    int top = stack->array[stack->elements-1];
    stack->elements--;
    printf("%d\n", top);
}


// MAIN
int main()
{
    struct Stack* stack = createStack(100);
    char command[10];
    char pushstr[] = "push";
    char popstr[] = "pop";
    int item;

    scanf("%s", command);
    if(strcmp(pushstr, command) == 0) {
        scanf("%d", &item);
        push(stack, item);
    } else if(strcmp(popstr, command) == 0) {
        pop(stack);
    } else {
        printf("crap\n");
    }

    while(scanf("%s", command) != EOF) {
        if(strcmp(pushstr, command) == 0) {
            scanf("%d", &item);
            push(stack, item);
        } else if(strcmp(popstr, command) == 0) {
            pop(stack);
        } else {
            printf("crap\n");
            break;
        }
    }

/*
    for(int i = 0 ; i < 25; i++) {
        scanf("%s", command);
        if(strcmp(pushstr, command) == 0) {
            scanf("%d", &item);
            push(stack, item);
        } else if(strcmp(popstr, command) == 0) {
            pop(stack);
        } else {
            break;
        }
    }
*/    
    /*
    pop(stack);
    push(stack, 10);
    push(stack, 20);
    push(stack, 30);
    pop(stack);
    pop(stack);
    pop(stack);
    pop(stack);
    pop(stack);
    push(stack, 15);
    pop(stack);
    */
    return 0;
}