#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Retrieves the amount of free memory in the system from /proc/meminfo.
int getAmountFreeMem() {
    FILE *file;
    size_t length = 0;
    char *line = NULL;
    int freeMem;

    file = fopen("/proc/meminfo", "r");

    //Throw an error if /proc/meminfo was unable to be opened.
    if(file == NULL) {
        printf("meminfo: failed to open /proc/meminfo.\n");
        exit(1);
    }

    //Scans through the lines of /proc/meminfo.
    //The while loop breaks when the string "MemFree" is encountered
    //as there's only one MemFree line in /proc/meminfo afterwards.
    while(getline(&line, &length, file) != -1) {
        //Retrieves the amount of free memory if the current line contains the string "MemFree"
        //for use in printing later and break the while loop afterwards.
        if(strstr(line, "MemFree") != NULL) {
            sscanf(line, "MemFree:         %d", &freeMem);
            break;
        }
    }
    
    fclose(file);

    return freeMem;
}

//Retrieves the number of memory buffers from /proc/meminfo.
int getNumMemBufs() {
    FILE *file;
    size_t length = 0;
    char *line = NULL;
    int numMemBufs;

    file = fopen("/proc/meminfo", "r");
    
    //Throw an error if /proc/meminfo was unable to be opened.
    if(file == NULL) {
        printf("meminfo: failed to open /proc/meminfo.\n");
        exit(1);
    }

    //Scans through the lines of /proc/meminfo.
    //The while loop breaks when the string "Buffers" is encountered
    //as there's only one Buffers line in /proc/meminfo.
    while(getline(&line, &length, file) != -1) {
        //Retrieves the amount of memory buffers if the current line contains the string "Buffers"
        //for use in printing later and break the while loop afterwards.
        if(strstr(line, "Buffers") != NULL) {
            sscanf(line, "Buffers:            %d", &numMemBufs);
            break;
        }
    }

    fclose(file);

    return numMemBufs;
}