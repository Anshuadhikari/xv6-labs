#include "user.h"  // Ensure "user.h" doesn't redefine printf/fprintf

int main(void) {
    // Print a message to indicate the test is running
    printf("Testing the dosys system call...\n");

    // Call the dosys system call
    int result = dosys();

    // Print the result of the system call
    printf("dosys returned: %d\n", result);

    // Exit the program
    exit(0);
}

