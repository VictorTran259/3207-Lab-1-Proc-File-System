#include "MYps.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char **argv) {
    //0 = FALSE (flag not present in arguments), 1 = TRUE (flag present in arguments)
    int ispPresent = 0;
    int issPresent = 0;
    int isUPresent = 0;
    int isSPresent = 0;
    int isvPresent = 0;
    int iscPresent = 0;

    //Keep track of how many -p flags are found in the arguments for potential error.
    int pCount = 0;

    int argument;

    //If the flag -p is present in the arguments, this variable will hold the PID value the user entered.
    char pid[10];

    //Read through all the arguments and check to see which flags are present. If the flag is present, set its corresponding int to 1.
    while((argument = getopt(argc, argv, "p:sUSvc")) != -1) {
        switch(argument) {
            case 'p':
                //Increment pCount every time -p appears in the arguments. Throw an error if more than 1 -p flag was found in the arguments.
                pCount++;
                if(pCount > 1) {
                    printf("MYps: too many -p flags were entered.\n");
                    exit(1);
                }
                ispPresent = 1;
                strcpy(pid, optarg);
                break;
            case 's':
                issPresent = 1;
                break;
            case 'U':
                isUPresent = 1;
                break;
            case 'S':
                isSPresent = 1;
                break;
            case 'v':
                isvPresent = 1;
                break;
            case 'c':
                iscPresent = 1;
                break;
            default:
                //getopt will throw the specific error. default will just throw a generic error.
                printf("MYps: an error occured.\n");
                exit(1);
        }
    }

    //***UNCOMMENT LINE BELOW TO PRINT OUT WHICH FLAGS ARE PRESENT IN THE ARGUMENTS***
    //printf("p = %d, s = %d, U = %d, S = %d, v = %d, c = %d\n", ispPresent, issPresent, isUPresent, isSPresent, isvPresent, iscPresent);

    //Case 1: If -p is not present, call the function findCurrentUserProcesses which will find all processes owned by the current user
    //and then print out the information for all the processes taking into consideration the other specified flags.
    if(ispPresent == 0) {
        findCurrentUserProcesses(issPresent, isUPresent, isSPresent, isvPresent, iscPresent);
    }
    //Case 2: If -p is present, call the function doesProcessExist to find out if the process (PID) the user specified exists.
    //the other specified flags if the process exists. Otherwise, perform the actions from Case 1 above.
    else if(ispPresent == 1) {
        doesSpecifiedProcessExist(pid, issPresent, isUPresent, isSPresent, isvPresent, iscPresent);
    }
}