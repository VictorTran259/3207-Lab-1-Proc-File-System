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

//***ALL OF THESE FUNCTIONS BELOW ARE FOR RETRIEVING THE DESIRED INFORMATION FROM A CERTAIN /PROC/<PID>/<FILENAME> FILE***
//Retrieve the amount of user time consumed so far by this process from /proc/<pid>/stat (default).
//Function takes in the pid of the process for the purpose of building a path to the process's stat file to extract the information.
int retrieveUserTime(char *pid) {
    //Build a path to the process's stat file.
    char fileName[4096] = { 0 };
    strcat(fileName, "/proc/");
    strcat(fileName, pid);
    strcat(fileName, "/stat");

    FILE* fp;
    char buffer[4096];
    size_t bytes_read;

    //***Copied this code from Advanced Linux Programming Chapter 7 p.149 Listing 7.1***
    //Read the entire contents of /proc/<pid>/stat into the buffer.
    fp = fopen (fileName, "r");
    bytes_read = fread (buffer, 1, sizeof (buffer), fp);
    fclose (fp);
    //Throw an error if read failed or if buffer isn’t big enough.
    if (bytes_read == 0 || bytes_read == sizeof (buffer)) {
        return 0;
    }
    //NUL-terminate the text.
    buffer[bytes_read] = '\0';

    //First strtok.
    char *argument = strtok(buffer, " ");

    //strtok 13 more times for a total of 14 times to reach utime which is the 14th argument of /proc/<pid>/stat.
    for(int i = 0; i < 13; i++) {
        argument = strtok(NULL, " ()");
    }

    int userTime = atoi(argument);

    return userTime;
}

//Retrieve the command-line that started this program from /proc/<pid>/cmdline.
//Function takes in the pid of the process for the purpose of building a path to the process's cmdline file to extract the information.
void retrieveCommandLine(char *pid) {
    //Build a path to the process's stat file.
    char fileName[4096] = { 0 };
    strcat(fileName, "/proc/");
    strcat(fileName, pid);
    strcat(fileName, "/cmdline");

    //***Copied this code from Advanced Linux Programming Chapter 7 p.153 Listing 7.3***
    char arg_list[4096];
    size_t length;
    char* next_arg;

    //Read the contents of the file.
    int fd = open(fileName, O_RDONLY);
    length = read (fd, arg_list, sizeof (arg_list));
    close (fd);

    //read does not NUL-terminate the buffer, so do it here.
    arg_list[length] = '\0';
    
    printf("[");

    //Loop over arguments. Arguments are separated by NULs. */
    next_arg = arg_list;
    while (next_arg < arg_list + length) {
        // Print the argument. Each is NUL-terminated, so just treat it like an ordinary string.
        printf ("%s", next_arg);

        //Advance to the next argument. Since each argument is NUL-terminated,
        //strlen counts the length of the next argument, not the entire argument list.
        next_arg += strlen (next_arg) + 1;

        if(strcmp(next_arg, "\0") != 0) {
            printf(" ");
        }
    }
    printf("]");
}

//Retrieve the single-character state information of a process from /proc/<pid>/stat (-s).
//Function takes in the pid of the process for the purpose of building a path to the process's stat file to extract the information.
char retrieveSingleCharStateInfo(char *pid) {
    //Build a path to the process's stat file.
    char fileName[4096] = { 0 };
    strcat(fileName, "/proc/");
    strcat(fileName, pid);
    strcat(fileName, "/stat");

    FILE* fp;
    char buffer[4096];
    size_t bytes_read;

    //***Copied this code from Advanced Linux Programming Chapter 7 p.149 Listing 7.1***
    //Read the entire contents of /proc/<pid>/stat into the buffer.
    fp = fopen (fileName, "r");
    bytes_read = fread (buffer, 1, sizeof (buffer), fp);
    fclose (fp);
    //Throw an error if read failed or if buffer isn’t big enough.
    if (bytes_read == 0 || bytes_read == sizeof (buffer)) {
        return 0;
    }
    //NUL-terminate the text.
    buffer[bytes_read] = '\0';

    //First strtok.
    char *argument = strtok(buffer, " ");

    //strtok 2 more times for a total of 3 times to reach state which is the 3rd argument of /proc/<pid>/stat.
    for(int i = 0; i < 2; i++) {
        argument = strtok(NULL, " ()");
    }

    char singleCharStateInfo = *argument;

    return singleCharStateInfo;
}

//Retrieve the amount of system time consumed so far by this process from /proc/<pid>/stat (-S).
//Function takes in the pid of the process for the purpose of building a path to the process's stat file to extract the information.
int retrieveSystemTime(char *pid) {
    //Build a path to the process's stat file.
    char fileName[4096] = { 0 };
    strcat(fileName, "/proc/");
    strcat(fileName, pid);
    strcat(fileName, "/stat");

    FILE* fp;
    char buffer[4096];
    size_t bytes_read;

    //***Copied this code from Advanced Linux Programming Chapter 7 p.149 Listing 7.1***
    //Read the entire contents of /proc/<pid>/stat into the buffer.
    fp = fopen (fileName, "r");
    bytes_read = fread (buffer, 1, sizeof (buffer), fp);
    fclose (fp);
    //Throw an error if read failed or if buffer isn’t big enough.
    if (bytes_read == 0 || bytes_read == sizeof (buffer)) {
        return 0;
    }
    //NUL-terminate the text.
    buffer[bytes_read] = '\0';

    //First strtok.
    char *argument = strtok(buffer, " ");

    //strtok 14 more times for a total of 15 times to reach stime which is the 15th argument of /proc/<pid>/stat.
    for(int i = 0; i < 14; i++) {
        argument = strtok(NULL, " ()");
    }

    int systemTime = atoi(argument);

    return systemTime;
}

//Retrieve the amount of virtual memory currently used (in pages) by this program from /proc/<pid>/statm (-v).
//Function takes in the pid of the process for the purpose of building a path to the process's statm file to extract the information.
int retrieveVirtualMemory(char *pid) {
    //Build a path to the process's stat file.
    char fileName[4096] = { 0 };
    strcat(fileName, "/proc/");
    strcat(fileName, pid);
    strcat(fileName, "/statm");

    FILE* fp;
    char buffer[4096];
    size_t bytes_read;

    //***Copied this code from Advanced Linux Programming Chapter 7 p.149 Listing 7.1***
    //Read the entire contents of /proc/<pid>/statm into the buffer.
    fp = fopen (fileName, "r");
    bytes_read = fread (buffer, 1, sizeof (buffer), fp);
    fclose (fp);
    //Throw an error if read failed or if buffer isn’t big enough.
    if (bytes_read == 0 || bytes_read == sizeof (buffer)) {
        return 0;
    }
    //NUL-terminate the text.
    buffer[bytes_read] = '\0';

    //Retrieve the first argument (size) which is the virtual memory value.
    char *argument1 = strtok(buffer, " ");

    int virtualMemory = atoi(argument1);

    return virtualMemory;
}