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

void main() {
  // Create a myNum variable and assign the value 15 to it
  int myNum = 15;
  
  // Declare a myOtherNum variable without assigning it a value
  char *myLetter = "Caleb is soooo hot";

  // myOtherNum now has 15 as a value
  printf("this is number %d and this is letter %s", myNum, 	myLetter);
}



// BACIS DATA TYPES
// int(size:2 or 4 bytes; description: store whole numbers, without decimals)
// float(size:4 bytes; stores fractional numbers, containing one or more decimals. sufficient for storing 6-7 decimal digits)
// double(size:8 bytes; stores frational numbers, containing one or more decimals. sufficient for storing 15 decimal digits)
// char(size:1 byte; stores a single character/letter/number, or ASCII values)

// Basic Format Specifiers
// %d or %i : int
// %f or %F : float
// %lf : double
// %c : char
// %s
// %lu

// cc -o oder order.c
// order.c
// time order.c
// r

// IF Statement
void main () {
    if (20>18) {
        printf ("20 is greater than 18");
    }
}
// ELSE Statement
void main() {
    int time = 20;
    if (time < 18) {
        printf("Good day.");
    } else {
        printf("Good evening.");
}}
// ELSE IF Statement
void main(){
    int time = 22;
    if (time < 10) {
        printf("Good morning.");
    } else if (time < 20) {
        printf("Good day.");
    } else {
        printf("Good evening.");
}}
// arrays   

// String Functions
// String Length
int main() {
  char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  printf("%d", strlen(alphabet));
  return 0;
}
// Concatenate Strings
int main() {
  char str1[10] = "Hello ";
  char str2[] = "World!";
 
  // Concatenate str2 to str1 (the result is stored in str1)
  strcat(str1, str2);
  
  // Print str1
  printf("%s", str1);
 
  return 0;
}
// Copy Strings
int main() {
  char str1[20] = "Hello World!";
  char str2[20];

  // Copy str1 to str2
  strcpy(str2, str1);

  // Print str2
  printf("%s", str2);
  
  return 0;
}
// Compare Strings
int main() {
  char str1[] = "Hello";
  char str2[] = "Hello";
  char str3[] = "Hi";

  // Compare str1 and str2, and print the result
  printf("%d\n", strcmp(str1, str2));
  
  // Compare str1 and str3, and print the result
  printf("%d\n", strcmp(str1, str3));
  
  return 0;
}

// User Input
int main() {
  // Create an integer variable that will store the number we get from the user
  int myNum;

  // Ask the user to type a number
  printf("Type a number and press enter: \n"); 

  // Get and save the number the user types
  scanf("%d", &myNum);

  // Print the number the user typed
  printf("Your number is: %d", myNum);

  return 0;
}
// multiple inputs
int main() {
  // Create an int and a char variable
  int myNum;
  char myChar;

  // Ask the user to type a number AND a character
  printf("Type a number AND a character and press enter: \n");

  // Get and save the number AND character the user types
  scanf("%d %c", &myNum, &myChar);

  // Print the number
  printf("Your number is: %d\n", myNum);

  // Print the character
  printf("Your character is: %c\n", myChar);
  
  return 0;
}
// Take String input
int main() {
  // Create a string
  char firstName[30];

  // Ask the user to input some text (name)
  printf("Enter your first name and press enter: \n");

  // Get and save the text
  scanf("%s", firstName);

  // Output the text
  printf("Hello %s", firstName);
  
  return 0;
}
// when working with strings, we often use the fgets() function to read a line of text. Note that you must include the following arguments: the name of the string variable, sizeof(string_name), and stdin
int main() {
  // Create a string
  char fullName[30] = malloc(sizeof char * 30);

  // Ask the user to input some text (full name)
  printf("Type your full name and press enter: \n");

  // Get the text
  fgets(fullName, sizeof(fullName), stdin);

  // Output the text
  printf("Hello %s", fullName);
  
  return 0;
}

// Memory Address：reference operator (&)
int main() {
  int myAge = 43;
  printf("%p", &myAge);
  return 0;
}

// Pointers

// strings are 1-dimensional arrays of charactars
// spristf and printf
// q: stdlib.h and double and struct
// 学会如何加需要的文件在最开头，每一个文件对应什么东西，并且如何在struct里面加东西，比如加bool，同时也要学会如何在bool里面加东西，比如加if。
// 是否和r一样，c语言也可以在function里面运用别的funciton。
// 理解library如何运用的，是不是可以把所有的function全部都放在里面
// 

// int bytes size binary
// int float char bytes
