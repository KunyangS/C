// C Program to Swap Two Numbers
// C Program to Swap Two Numbers using Function
#include <stdio.h>

// Function to swap two numbers
void swap(int* a, int* b) {
  
    // Swapping using temporary variable
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
    int a = 5, b = 10;

    // Call the swap function with addresses of a and b
    swap(&a, &b);

    printf("After swapping: a = %d, b = %d\n", a, b);
    return 0;
}
//https://www.geeksforgeeks.org/c-program-swap-two-numbers/
