// STRUCTURES: also called structs, are a way to group several related variables into one place.each variable in the structure is known as a member of the structure
// unlike an array, a structure can contain many different data types(int,float, char,etc.)
// CREATE a Structure
struct myStructure { // Structure declaration
    int myNumber; // Member (int variable)
    char myLetter; // Member (char variable)
}; // End the structure with a semicolon

// Use the struct keyword inside the main() method
struct myStructure{
    int myNumber;
    char myLetter;
};
int main(){
    struct myStructure s1;
    return 0;
}

// Access Structure Members: to access members of a structure, use the dot syntax(.)
struct myStructure{ // create a structure called myStructure
    int myNumber;
    char myLetter;
};
int main(){  // Create a structure variable of myStructure called s1
    struct myStructure s1;
    // assign values to members of s1
    s1.myNum = 13;
    s1.myLetter = 'B';
    // print values
    printf("My number:%d\n",s1.myNumber);
    printf("My letter:%c\n",s1.myLetter);
    return 0;
}
// create multiple structure variables with different values, using just one structure
// Create different struct variables
struct myStructure s1;
struct myStructure s2;
// Assign values to different struct variables
s1.myNum = 13;
s1.myLetter = 'B';
s2.myNum = 20;
s2.myLetter = 'C';


// use the strcpy() function and assign the value to s1.myString
struct mystructure{
    int myNum;
    char myLett;
    char myStrin[30];//string
};
int main(){
    struct mystructure s1;
    strcpy(s1.myStrin,"some text");// assign a value to the string using the strcpy function
    printf("my string:%s",s1.myStrin);
    return 0;
}



// SIMPLER SYNTAX:You can also assign values to members of a structure variable at declaration time, in a single line.
// Just insert the values in a comma-separated list inside curly braces {}. Note that you don't have to use the strcpy() function for string values with this technique:
struct mystructure{//create a structure
    int myNum;
    char myLett;
    char myStrin[30];
};
int main(){
    struct mystructure s1 = {12,'B',"some text"};//create a structure variable and assign values to it
    printf("%d %c %s",s1.myNum,s1.myLett,s1.myStrin);
    return 0;
}



// COPY STRUCTURES:you can also assign one structure to another
struct mystructures s1 = {12,'B',"some text"};
struct mystructures s2;
s2 = s1; 


// MODIFY VALUES: if you want to change/modify a value, you can use the dot syntax(.)
// the strcpy() function is useful to modify a string value
struct mystructure{//create a structure
    int myNum;
    char myLett;
    char myStrin[30];
};
int main(){
    struct mystructure s1 = {13,'B',"some text"};//create a structure variable and assign values to it
    // modify values
    s1.myNum = 30;
    s1.myLett = 'C';
    strcpy(s1.myStrin,"something else");
    // print values
    printf("%d %c %s", s1.myNum,s1.myLett,s1.myStrin);
    return 0;
}
// Modifying values are especially useful when you copy structure values
struct myStructure s1 = {13, 'B', "Some text"};// Create a structure variable and assign values to it
struct myStructure s2;// Create another structure variable
s2 = s1;// Copy s1 values to s2
// Change s2 values
s2.myNum = 30;
s2.myLetter = 'C';
strcpy(s2.myString, "Something else");
// Print values
printf("%d %c %s\n", s1.myNum, s1.myLetter, s1.myString);
printf("%d %c %s\n", s2.myNum, s2.myLetter, s2.myString);

// Real-Life Example
struct Car {
  char brand[50];
  char model[50];
  int year;
};
int main() {
  struct Car car1 = {"BMW", "X5", 1999};
  struct Car car2 = {"Ford", "Mustang", 1969};
  struct Car car3 = {"Toyota", "Corolla", 2011};

  printf("%s %s %d\n", car1.brand, car1.model, car1.year);
  printf("%s %s %d\n", car2.brand, car2.model, car2.year);
  printf("%s %s %d\n", car3.brand, car3.model, car3.year);

  return 0;
}