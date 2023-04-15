//user header file so we need to use ""
#include "dd2.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void hexdump (char * buf, int len);

int main (int argc, char * argv[]){
    // creating a pointer to point at the personalInfo struct in assignment2.h
    // allocating a space the same size as the personaInfo
    personalInfo * pointer;
    pointer = malloc (sizeof (personalInfo));
    // using printf to check if malloc failed.
    // exit if malloc failed.
    if(pointer == NULL){
        printf("ERROR: malloc failed");
        return (-1);
    }
    // Assingning values to personalInfo
    pointer->firstName = argv[1];
    pointer->lastName = argv[2];
    pointer->level = SENIOR;
    // bitwise add to languages
    pointer->languages = KNOWLEDGE_OF_JAVA | KNOWLEDGE_OF_JAVASCRIPT | KNOWLEDGE_OF_CPLUSPLUS | KNOWLEDGE_OF_C;
    // knowing the length of the message.
    // source : https://www.geeksforgeeks.org/strlen-function-in-c/
    int lenfthOfMessage = strlen(argv[3]);

    /*printf("\tlength of message: %d \n", lenfthOfMessage);*/

    // if the size of the message is larger than 100, change it to 100
    if (lenfthOfMessage > sizeof(pointer -> message)){
        lenfthOfMessage = sizeof(pointer -> message);
    }

    /*printf("\tlength of message after fixing: %d \n", lenfthOfMessage);*/

    // copies n (lenfthOfMessage) characters from argv[3] to message
    //source: https://www.tutorialspoint.com/c_standard_library/c_function_memcpy.htm
    memcpy(pointer->message, argv[3],lenfthOfMessage);

    // Step five, write the personal information.
    int pWrite = writePersonalInfo (pointer);
    // return 0 if success, so anything else mean error
    if(pWrite !=0){
        printf("ERROR: in writing PersonalInfo:\n");
    }
    //printing the personal info to catch any error
    printf("\n************************************************************\n");
    printf("Name: %s %s \n", pointer->firstName, pointer->lastName);
    printf("Level: %d\n",pointer->level);
    printf("Languages: %d \n", pointer->languages);
    printf("Message: %s\n", pointer->message);
    // free the pointer because we do not need it any more
    // point at NULL for safety for future use
    free(pointer);
    pointer=NULL;

    // allocate the buffer dynamicly with the size of 256 (BLOCK_SIZE)
    char*buffer = malloc(BLOCK_SIZE);
    // we need a char pointer to get a new line
    const char *newLine;
    //getting a new line to buffer write
    newLine= getNext();

    // to keep track of our location in the buffer
    int position = 0;
    // to keep track of the size of the new line
    int lengthOfLine;

    // to track the number of commit
    int commitNumber = 0;
    // Iterate untill the new line is NULL
    while(newLine !=NULL){
        // getting the size of the new line
        //source: https://www.geeksforgeeks.org/strlen-function-in-c/
        lengthOfLine= strlen(newLine);
        // if the size of the new line is smaller or equal to the 265 - our position in the buffer
        // coppy the newLine to the buffer (from our our position to the end)
        // keeping track of our position for the next new line
        if(lengthOfLine <= (BLOCK_SIZE - position)){
            memcpy (buffer + position, newLine, lengthOfLine);
            position = position + lengthOfLine;
            newLine = getNext();
        }
        // if the new line is bigger than the space in the buffer
        // copy the line to the buffer just the size of remaining space
        // commit the buffer.
        // getting the rest of the line that we did not copy to the buffer.
        // we did the commit so we can change the position to zero (start over).
        else{
            memcpy(buffer + position, newLine, BLOCK_SIZE - position);
            /* hexdump (buffer, BLOCK_SIZE);*/
            commitNumber++;
            commitBlock(buffer);
            newLine = newLine+(BLOCK_SIZE - position);
            position = 0;
        }
    }
    // commit again if there is any small line in the buffer
    if(position>0){
    commitNumber++;
    commitBlock(buffer);
    }
    // frre the buffer and point at NULL for safety
    free(buffer);
    buffer=NULL;
    printf("\nNumber of the commit is: %X \n", commitNumber);

    // Step seven
    int checkRetuen = checkIt();
    return checkRetuen;
}
