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

//Display the process information of a specified pid.
//Takes in the process PID for the purpose of passing it to parser functions and the ints that
//show which flags the user entered to determine what information to print.
void displayProcessInfo(char *pid, int issPresent, int isUPresent, int isSPresent, int isvPresent, int iscPresent) {
    //Always print the PID.
    printf("PID: %s     ", pid);

    //Will only print utime if -U is not present in the arguments.
    if(isUPresent != 1) {
        printf("User time (utime) consumed: %d     ", retrieveUserTime(pid));
    }

    //Will only print single-character state if -s is present in the arguments.
    if(issPresent == 1) {
        printf("Single-character state info: %c     ", retrieveSingleCharStateInfo(pid));
    }

    //Will only print stime if -S is present in the arguments.
    if(isSPresent == 1) {
        printf("System time (stime) consumed: %d     ", retrieveSystemTime(pid));
    }

    //Will only print virtual memory if -v is present in the arguments.
    if(isvPresent == 1) {
        printf("Virtual memory in use: %d     ", retrieveVirtualMemory(pid));
    }

    //Will only print command line if -c is not present in the arguments.
    if(iscPresent != 1) {
        printf("Command line: ");
        retrieveCommandLine(pid);
    }

    printf("\n\n");
}