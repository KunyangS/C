#include <stdio.h>

int main(){
    printf("Hello World!");
    return 0;
}

int main1() {
    printf("hihihihi~");
    printf("i'm coming :)");
    return 0;
}

//add a new line
int main2() {
    printf("hihihi~\n");
    printf("this is a new line because i'm coming and honk honk hahaha :)");
    return 0;
}

int main3() {
    printf("saturday\n\nyapyapyap:33");
    return 0;
}

//somethings more about escape sequence
//creates a horizontal tab: \t 
//inserts a backslash character: \ 
//inserts a double quote character: \" 


//create a variable and use the variable function
//create a variable
int getValue() {
    int apple = 15;
    return apple;
}
//use the variable function
int useValue() {
    int value = getValue;
    printf("%d", value); // %c for char and %f for float
    return 0;
}

// Format specifiers examples
int creatnfl(){
    //create variable
    int myNumber = 15; // integer(whole number)
    float myFloatNumber = 5.99; // floating point number
    char myLetter = 'D'; // character
    // print variables
    printf("%d\n", myNumber);
    printf("%f\n", myFloatNumber);
    printf("%c\n", myLetter);
    return 0;
}
// combine both text and variable
int comtextvariable(){
    int myNum = 15;
    char myLetter = 'X';
    printf("My favorite number is: %d, my letter is: %c", myNum, myLetter);
    return 0;
}

// change variable values
int changevariable(){
    int myNum = 15; // myNum is 15
    myNum = 10; // Now myNum is 10
    printf ("%d", myNum);
    return 0;
}
// other method to change variable values
void changev(){
    int myNum = 15;
    int myOtherNum;
    myOtherNum = myNum;
    printf("%d", myOtherNum);
}


// cc -o oder order.c
// order.c
// time order.c
// r

// arrays
// strings are 1-dimensional arrays of charactars
// spristf and printf
