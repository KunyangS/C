// a function consist of two parts: declaration and definition
// declaration: the function's name,return type, and parameters(if any)
// definition: the body of the function(code to be executed)
void myFunction(){ // declaration
    // the body of the function (definition)
}
// c programs that hav function declaration above main(), and function below main()
void myFunction(); // function declaration
int main(){ // the main method
    myFunction();// call the function
    return 0;
}
void myFunction(){ // function definition
    printf("i just got executedd!");
}

// WHAT ABOUT PARAMETERS
int myFunctions(int x, int y) {
    return x + y;
}
int main() {
    int result = myFunctions(5, 3);
    printf("Result is = %d", result);
    return 0;
} // outputs 8(5+3)
// it is considered goood practive to write it like this instead:
int myFunctionn(int x, int y); // function declaration
int main(){ // the main method
    int result = myFunctionn(5, 3); // call the function
    printf("Result is = %d", result);
    return 0;
}
int myFunction(int x, int y){ // function definition
    return x + y;
}