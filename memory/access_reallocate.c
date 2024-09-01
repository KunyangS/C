#include <stdio.h>
#include <stdlib.h>
// ACCESS DYNAMIC MEMORY:Dynamic memory behaves like an array, with its data type specified by the type of the pointer.
// As with arrays, to access an element in dynamic memory, refer to its index number:
ptr[0] 12;
// You can also dereference the pointer to access the first element:
*ptr = 12;
// example(read from and write to dynamic memory)
int main(){
    //allocate memory
    int *ptr;
    ptr = calloc(4,sizeof(*ptr));

    // write to the memory
    *ptr = 2;
    ptr[1] = 4;
    ptr[2] = 6;

    // read from the memory
    printf("%d\n",*ptr);
    printf("%d %d %d",ptr[1],ptr[2],ptr[3]);

    return 0;
}


// A NOTE ABOUT DATA TYPES: Dynamic memory does not have its own data type, it is just a sequence of bytes. The data in the memory can be interpreted as a type based on the data type of the pointer.
// In this example a pointer to four bytes can be interpreted as one int value (4 bytes) or as an array of 4 char values (1 byte each).
int main(){
    int *ptr1 = malloc(4);
    char *ptr2 = (char*) ptr1;
    ptr1[0] = 1342423515;
    printf("%d is %c %c %c %c", *ptr1, *ptr2[0], *ptr2[1], *ptr2[2], *ptr2[3]);

    return 0;
}