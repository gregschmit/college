#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{       
        char myArray[35] = "Something Useful For Testing";
        int secondArray[5]={111, 112, 113, 114, 115};
        int *myPtr;
        myPtr = secondArray; 
        printf("%s\n",myPtr+17);
                // Question 1, what gets printed here?
                // gns: Undefined output due to you are beyond the scope of the 
                //      last array
        printf("%x\n",myPtr);
                // Question 2, what gets printed here?
                // gns: Prints the address of secondArray in Hexadecimal
        printf("%d\n",*(++myPtr));
                // Question 3, what gets printed here?
                // gns: Prints 112
        printf("%x\n",++myPtr);
                // Question 4, what gets printed here?
                // gns: Prints the address of secondArray[2] in Hexadecimal
        printf("new char %c\n",myArray+35);
        char *myCharPtr = (char *)malloc(25);
                // Question 5, what does this code do?
                // gns: The printf statement prints a null character (nothing). 
                //      Then it generates a range of memory 25 bytes long and 
                //      returns the first byte's address and stores it into 
                //      myCharPtr.
        strncpy(myCharPtr,"testing for our in class demo we need a long "
                "string",34);
        printf("%s\n",myCharPtr);
                // Question 6, what gets printed here?
                // gns: "testing for our in class demo we n" (strncpy stops at 
                //      34)
        myCharPtr[24]='\0';
        printf("%s\n",myCharPtr);
                // Question 7, how/why is what gets printed here 
                // different than what gets printed in Question 6?
                // gns: The string will terminate at this null character, and 
                //      printf will not print any further.
        return 0;
}
