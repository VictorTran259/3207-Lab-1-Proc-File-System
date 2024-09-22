void doesSpecifiedProcessExist(char *specifiedPID, int issPresent, int isUPresent, int isSPresent, int isvPresent, int iscPresent);
void findCurrentUserProcesses(int issPresent, int isUPresent, int isSPresent, int isvPresent, int iscPresent);
void displayProcessInfo(char *pid, int issPresent, int isUPresent, int isSPresent, int isvPresent, int iscPresent);
int retrieveUserTime(char *pid);
void retrieveCommandLine(char *pid);
char retrieveSingleCharStateInfo(char *pid);
int retrieveSystemTime(char *pid);
int retrieveVirtualMemory(char *pid);