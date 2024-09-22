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

//Displays the information for an existing specified PID with the help of the displayProcessInfo (-p) . 
//If it doesn't display the information of processes owned by the current user instead.
//Function takes in the pid specified by the user for the purpose of checking if the process exists
//and also the the ints that show which flags the user entered for the purpose of passing it down to the displayProcessInfo
//either directly or through the function findCurrentUserProcesses.
void doesSpecifiedProcessExist(char *specifiedPID, int issPresent, int isUPresent, int isSPresent, int isvPresent, int iscPresent) {
    //Build the file path.
    char fileName[4096] = { 0 };
    strcat(fileName, "/proc/");
    strcat(fileName, specifiedPID);

    //Test to see if the process exists within the /proc directory.
    struct stat sb;
    int doesFileExist = stat(fileName, &sb);

    //Case 1: Process doesn't exist. Call findCurrentUserProcesses to display the information of processes owned by the current user.
    if(doesFileExist != 0) {
        printf("MYps: Process does not exist. Displaying information for processes owned by user instead...\n");
        findCurrentUserProcesses(issPresent, isUPresent, isSPresent, isvPresent, iscPresent);
    }
    //Case 2: Process exists. Call displayProcessInfo to display its information.
    else {
        displayProcessInfo(specifiedPID, issPresent, isUPresent, isSPresent, isvPresent, iscPresent);
    }
}

//Find all processes owned by the current user within the /proc directory and then call displayProcessInfo
//to print out the process information in accordance to the flags the user entered.
//Function takes in the ints that show which flags the user entered for the purpose of passing it to the displayProcessInfo function.
void findCurrentUserProcesses(int issPresent, int isUPresent, int isSPresent, int isvPresent, int iscPresent) {
    //Retrieve the current user's UID.
    int uid = getuid();

    DIR *d = opendir("/proc");

    //Throw an error if the /proc directory couldn't be opened.
    if(d == NULL) {
        printf("MYps: could not open /proc\n");
        exit(1);
    }

    struct dirent *dir;

    //Read through the contents of the /proc directory.
    while((dir = readdir(d)) != NULL) {
        //Check to see if the current process is a pid (it's an int).
        if(isdigit(*dir->d_name)) {
            //Build a path to the process's stat file.
            char fileName[4096] = { 0 };
            strcat(fileName, "/proc/");
            strcat(fileName, dir->d_name);
            strcat(fileName, "/stat");

            //Retrieve the process's uid.
            struct stat sb;
            stat(fileName, &sb);

            int file_uid = sb.st_uid;

            //Check to see if the process is owned by the current user
            //(the process's uid matches the user's uid).
            //If it is, call d_ProcessInfo to display the process's info.
            if(file_uid == uid) {
                displayProcessInfo(dir->d_name, issPresent, isUPresent, isSPresent, isvPresent, iscPresent);
            }
        }
    }

    closedir(d);
}