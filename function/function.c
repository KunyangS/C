// FUNCTIONS
// predefined functions
int main(){
    printf("Hello World!");
    return 0;
}

// create a function: void means that the function doesn't have a return value
void myFunction(){ // myFunction() is the name of the function
    //code to be executed
}

// call a function: decleared functions are not executed immediately. they are"saved for later use", and will be executed when they are called.
// to call a function, write the function's name followed by two parentheses() and a semicolon;
// in the following example, myFunction() is used to print a text(the action),when it is called:
void myFunction(){// create a function
    printf("I just got executed!");
}
int main(){
    myFunction();// call the function
    return 0;
}// outputs "I just got executed!"
int main(){
    myFunction();
    myFunction();
    myFunction();// a function can be called multiple times
    return 0;
}
// use functions to call other functions
void myFunction(){// create a function(myFunction)
    printf("Some text in myFunction\n");
    myOtherFunction();// call myOtherFunction
}
void myOtherFunction(){// create another function(myOtherFunction)
    printf("Hey! Some text in myOtherFunction\n");
}
int main(){
    myFunction();// call myFunction
    return 0;
}

// calculate the sum of numbers
void calculateSum(){
    int x=5;
    int y=10;
    int sum = x+y;
    printf("The sum of x+y is: %d", sum);
}
int main(){
    calculateSum();// call the function
    return 0;
}

// FUNCTION PARAMETERS
// parameters and arguments:information can be passed to functions as a parameter. Parameters act as variables inside the function.
int functionName(parameter1, parameter2, parameter3) { // int is a return type
  // code to be executed
  return 0;
}
// example:the function takes a string of characters with name as parameter.
// When the function is called, we pass along a name, which is used inside the function to print "Hello" and the name of each person:
void myFunction(char name[]){
    printf("Hello %s\n",name);
}
int main(){
    myFunction("Liam");
    myFunction("Jenny");
    myFunction("Anja");
    return 0;
}
// multiple parameters
void myFunction(char name[], int age){
    printf("Hello %s. You are %d years old.\n", name, age);
}
int main(){
    myFunction("Liam",3);
    myFunction("Jenny",14);
    myFunction("Anja",30);
    return 0;
}
// calculate the sum of numbers
void calculateSum(int x, int y){
    int sum = x+y;
    printf("The sum of %d + %d is:%d\n", x, y, sum);
}
int main(){
    calculateSum(5, 3);
    calculateSum(8, 2);
    calculateSum(15, 15);
    return 0;
}
// pass arrays as function parameters
void myFunctions(int myNumbers[5]){
    for (int i=0; i<5; i++) {
        printf("%d\n", myNumbers[i]);
    }
}
int main(){
    int myNumbers[5] = {10, 20,30,40,50};
    myFunction(myFunction);
    return 0;
}
// Return Values:The void keyword, used in the previous examples, indicates that the function should not return a value.
// If you want the function to return a value, you can use a data type (such as int or float, etc.) instead of void, and use the return keyword inside the function:
int myFunctionq(int x){
    return 5+x;
}
int main(){
    printf("Result is:%d", myFunctionq(3));
    return 0;
} // outputs 8(5+3)
// returns the sum of a function with two parameters
int myFunctionqq(int x, int y){
    return x + y;
}
int main(){
    printf("Result is: %d", myFunctionqq(5,3));
    return 0;
} // outputs 8(5+3)
// i can also store the result in a variable:
int myFunctionss(int x, int y){
    return x + y;
}
int main (){
    int result = myFunctionss(5,3);
    printf("Result is = %d", result);
    return 0;
}
// "calculate the sum of numbers" example one more time
// use return instead of and store the results in different variable
int calculatesum(int x, int y){
    return x + y;
}
int main(){
    int result1 = calculatesum(5,3);
    int result2 = calculatesum(8,2);
    int result3 = calculatesum(15,15);
    printf("Result1 is: %d", result1);
    printf("Result2 is: %d", result2);
    printf("Result3 is: %d", result3);
    return 0;
}
// use an array to store many "result variables"
int calculatesum1(int x, int y){
    return x + y;
}
int main(){
    int resultArr[6]; // create an array
    // call the function with different arguments and store the results in the array
    resultArr[0] = calculatesum1(5,3);
    resultArr[1] = calculatesum1(8,2);
    resultArr[2] = calculatesum1(15,15);
    resultArr[3] = calculatesum1(9,1);
    resultArr[4] = calculatesum1(7,7);
    resultArr[5] = calculatesum1(1,1);

    for (int i = 0; i < 6; i++){
        printf("Result%d is = %\n", i + 1, resultArr[i]);
    }
    return 0;
}

// real-life example:create a program that converts a value from fahrenheit to celsius
float toCelsius(float fahrenheit){ //function to convert fahrenheit to celsius
    return (5.0 / 9.0) * (fahrenheit - 32.0);
} 
int main(){
    float f_value = 98.8; // set a fahrenheit value
    float result = toCelsius(f_value); // call the function with the fahrenheit value
    printf("Fahrenheit: %.2f\n", f_value); // print the fahrenheit value
    printf("Convert Fahrenheit to Celsius: %.2f\n", result); // print the result
    return 0; 
}


// SCOPE: variables are only accessible inside the region they are created
// variable scope
// local scope: a variable created inside a function belongs to the local scope of that function, and can only be used inside that function
void myscope(){
    int x = 5;// local variable that belongs to myscope
    printf("%d",x);//print the variable x
}
int main(){
    myscope();
    return 0;
}
// global scope
int x = 5; // global variable:a variable created outside of a function that is available from within any scope, global and local
void myglobal(){
    printf("%d",x);// we can use x here
}
int main(){
    myglobal();
    printf("%d",x);// we can also use x here
    return 0;
}
// naming variables: c can operate with the same variable name inside and outside of a function.
// one available in the global scope(outside the function) and one available in the local scope(inside the function).
int x = 5; // global variable x
void mynaming(){
    int x = 22; // local variable with the same name as the global variable(x)
    printf("%d\n",x);// refers to the local variable x
}
int main(){
    mynaming();
    printf("%d\n",x); // refers to the global variable x
    return 0;
}
// change the value of x from mychange:
int x = 5; // global variable
void mychange(){
    printf("%d\n",++x); // increment the value of x by 1 and print it
}
int main(){
    mychange();
    printf("%d\n",x); // print the global variable x
    return 0; // the value of x is now 6 (no longer 5)
}
