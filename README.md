# CIS 3207 Lab 1 - /PROC File System
## Project files

### Warmup
      cpuinfo.c
      cpuinfo.h
      meminfo.c
      meminfo.h
      cpumeminfo.c

### MYps
      MYps.c
      MYps.h
      processhandling.c
      displayprocessinfo.c
      parsers.c
      makefile


## FUNCTIONS

### Warm-up

    int getNumCPUs();
        Reads through the contents of /proc/cpuinfo using getline(), looks for the string "processor" on each line of /proc/cpuinfo using strstr(), and increments an integer
        every time the string "processor" was found to calculate the number of CPUs which is then returned by the function.

    void getAmountOfCacheInCPUs();
        Reads through the contents of /proc/cpuinfo using getline(), looks for the string "cache size" on each line of /proc/cpuinfo using strstr(), and print out the amount
        of available cache in each CPU using sscanf() to extract that information associated with lines containing the string "cache size".

    int getAmountFreeMem();
        Reads through the contents of /proc/meminfo using getline(), looks for the string "MemFree" on each line of /proc/meminfo using strstr(), and sets an integer to be
        returned to the value associated with "MemFree" with the help of sscanf() to extract that information.

    int getNumMemBufs();
        Reads through the contents of /proc/meminfo using getline(), looks for the string "Buffers" on each line of /proc/meminfo using strstr(), and sets an integer to be
        returned to the value associated with "Buffers" with the help of sscanf() to extract that information.

### MYps

#### In processhandling.c:
    void doesSpecifiedProcessExist(char *specifiedPID, int issPresent, int isUPresent, int isSPresent, int isvPresent, int iscPresent);
        For the case where the flag -p was entered, builds a path (the process) using strcat() and then checks to see if that process exists using stat. If that process
        exists, calls the function displayProcessInfo to print out that process's information taking into account the other flags the user entered. If that process 
        doesn't exist, calls the function findCurrentUserProcesses to find out which processes are owned by the current user and prints out the informatios of those
        processes taking into account the other flags the user entered. The function takes in all the values of the ints used to keep track of which flags are present
        for use later on in displaying the process information and also the pid specified by the user for the purpose of checking if the process exists.

    void findCurrentUserProcesses(int issPresent, int isUPresent, int isSPresent, int isvPresent, int iscPresent);
        For the case where the flag -p wasn't entered or the process (PID) the user entered for the flag -p doesn't exist, find out which processes are owned by the current
        user by reading through the contents of /proc using readdir(), building a path using strcat() for each process, and then using stat to find the uid of that process.
        If the uid of the process matches the current user's uid that was retrieved using getuid(), call the function displayProcessInfo to display the information of that
        process taking into account the other flags the user entered. Repeats this process until every process's PID within /proc has been analyzed. The function takes in all
        the values of the ints used to keep track of which flags are present for use later on in displaying the process information.

#### In displayprocessinfo.c:
    void displayProcessInfo(char *pid, int issPresent, int isUPresent, int isSPresent, int isvPresent, int iscPresent);
        Prints out the information of a process with the help of all the functions listed below this one, taking into account the other flags the user entered. The default
        process information that's printed out by this function is the process's PID, the amount of user time the process has consumed, and the command line that started
        the process. If the flags -U and/or -c are present in the arguments the user entered, the amount of user time the process has consumed and/or the command line that
        started the process are not displayed respectively. If the flags -s, and/or -S, and/or -v are present in the arguments the user entered, the single-character state
        information about the process, and/or the amount of system time consumed so far by this process, and/or the amount of virtual memory currently used (in pages) by
        this program are displayed. The function takes in all the values of the ints used to keep track of which flags are present for use in printing out the information.
        and also the process PID for the purpose of passing it to parser functions.

#### In parsers.c:
    int retrieveUserTime(char *pid);
        Builds a path to a process's stat file and reads the information it contains into a buffer. strtok() is called 14 times to reach the 14th argument of the process's
        stat folder which is the utime value. An int that will be returned is set to the value of the 14th argument of the process's stat file which is converted into an int
        from a string using atoi(). The function takes in the pid of the process for the purpose of building a path to the process's stat file to extract the information.

    void retrieveCommandLine(char *pid);
        Builds a path to a process's cmdline file and reads the information it contains into a buffer. Reads through the buffer and prints out the arguments in the process's
        cmdline file. Since each argument is terminated with a null character, increment the pointer set to the buffer by 1 every time a null character is reached until all the
        arguments are printed out (two null characters in a row have been encountered). The function takes in the pid of the process for the purpose of building a path to the
        process's cmdline file to extract the information.

    char retrieveSingleCharStateInfo(char *pid);
        Builds a path to a process's stat file and reads the information it contains into a buffer. strtok() is called 3 times to reach the 3rd argument of the process's
        stat folder which is the single-character state. A char that will be returned is set to the value of that single-character state. The function takes in the pid of
        the process for the purpose of building a path to the process's stat file to extract the information.

    int retrieveSystemTime(char *pid);
        Builds a path to a process's stat file and reads the information it contains into a buffer. strtok() is called 15 times to reach the 15th argument of the process's
        stat folder which is the stime value. An int that will be returned is set to the value of the 15th argument of the process's stat file which is converted into an int
        from a string using atoi(). Function takes in the pid of the process for the purpose of building a path to the process's stat file to extract the information.
        The function takes in the pid of the process for the purpose of building a path to the process's stat file to extract the information.

    int retrieveVirtualMemory(char *pid);
        Builds a path to a process's statm file and reads the information it contains into a buffer. strtok() is called 1 time to reach the 1st argument of the process's
        statm folder which is the size (virtual memory) value. An int that will be returned is set to the value of the 1st argument of the process's stat file which is
        converted into an int from a string using atoi(). The function takes in the pid of the process for the purpose of building a path to the process's stat file to
        extract the information.


cpumeminfo.c contains the main function for the warmup and it just prints out the number of CPUs, amount of cache in each CPU, the amount of free memory, and the number of
memory buffers using the functions present in the warmup listed above.


MYps.c contains the main function for MYps and it contains a argument parser that uses getopt() and a switch statement which sets a bunch of ints that represent each
possible flag and are initialized to 0, meaning the flag isn't present in the arguments, to 1, meaning the flag is present in the arguments, if getopts() finds that the flag
is present in the argument. The ints representing each possible flag and their value are needed by the displayProcessInfo function in order to decide what information to
print out. The main function will call the function findCurrentUserProcesses if the -p flag wasn't present in the arguments or the function displayProcessInfo if the -p
flag is present in the function to start the process of printing out process information. An error will be thrown if more than 1 -p <pid> flag is entered by the user.


The header files all contain function declarations of the functions in the warmup program and MYps.


I have created and included a makefile that compiles MYps for quality of life purposes.


There are many comments included all over cpuinfo.c, meminfo.c, cpumeminfo.c MYps.c, processhandling.c, displayprocessinfo.c, and parsers.c that go into detail about
the purpose of a certain line of lines of code.


## POSSIBLE FLAGS

    -p <pid>  Display process information only for the process whose number is pid. It does not matter if the specified process is owned by the current user. If this option is not
              present, then display information for all processes of the current user (and only of the current user). Process UID found in /proc/<pid>/stat
              
    -s        Display the single-character state information about the process. Found in /proc/<pid>/stat.
    
    -U        DO NOT Display the amount of user time consumed by this process. Found in /proc/<pid>/stat.
    
    -S        Display the amount of system time consumed so far by this process. Found in /proc/<pid>/stat.
    
    -v        Display the amount of virtual memory currently used (in pages) by this program. Found in /proc/<pid>/statm.
    
    -c        DO NOT Display the command-line that started this program. Found in /proc/<pid>/cmdline.


## TESTING

One way to test this program is using the sleepy.c program. If MYps works correctly, when a user runs sleepy, the program should pick it up as a process owned by the user.
All of the information that the sleepy.c process contains should be able to be printed out such as the command line the user used to run the sleepy program. Error catching
for if a file wasn't able to be opened or if a read to a buffer failed was included just in case something went wrong during the execution of MYps. Another way of testing 
this program is to simply use cat /proc/'pid'/'filename' in the terminal and compare the arguments retrieved from it with the values printed out by the MYps program.
