// definition: a special type represents a group of constants(unchangeable values)
// create an enum: use the enum keyword, followed by the name of the enum, and separate the enum items with a comma
enum Level {
    LOW,
    MEDIUM,
    HIGH
};
// to access the enum, you must create a variable of it
// inside the main() method, specify the enum keyword, followed by the name of the enum(level)and then the name of the enum variable(myVar in this example):
enum Level myVar; // now you have created an enum variable(myVar)
// to assign a value to myVar: the assigned value must be one of the items inside the enum(LOW, MEDIUM or HIGH):
enum Level myVar = MEDIUM;
// by default, the first item(LOW) has the value 0, the second(MEDIUM) has the value 1, etc.
// if you now try to print myVar, it will output 1,which represents MEDIUM:
int main(){
    enum Level myVar = MEDIUM; // create an enum variable and assign a value to it
    printf("%d", myVar);// print the enum variable
    return 0;
}


// CHANGE VALUES
enum Level {
    LOW = 25,
    MEDIUM = 50,
    HIGH = 75
};
int main(){
    enum Level myVar = MEDIUM;
    printf("%d", myVar);
    return 0;
}
printf("%d", myVar); // now outputs 50
// Note that if you assign a value to one specific item, the next items will update their numbers accordingly:
enum Level{
    LOW = 5,
    MEDIUM,//now 6
    HIGH//now 7
};
int main(){
    enum Level myVar = MEDIUM;
    printf("%d", myVar);
    return 0;
}


// ENUM IN A SWITCH STATEMENT: Enums are often used in switch statements to check for corresponding values:
enum Level{
    LOW = 5,
    MEDIUM,//now 6
    HIGH//now 7
};
int main() {
  enum Level myVar = MEDIUM;
  
  switch (myVar) {
    case 5:
      printf("Low Level");
      break;
    case 6:
      printf("Medium level");
      break;
    case 7:
      printf("High level");
      break;
    default:
        printf("out of valid range");
        break;
  }
   
  return 0;
}