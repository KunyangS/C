#include <stdlib.h> 
#include <sys/types.h> 
#include <unistd.h> 
// useful link:https://www.geeksforgeeks.org/zombie-and-orphan-processes-in-c/

// ZOMBIE:A process which has finished the execution but still has entry in the process table to report to its parent process is known as a zombie process. A child process always first becomes a zombie before being removed from the process table. The parent process reads the exit status of the child process which reaps off the child process entry from the process table
// A C program to demonstrate Zombie Process.  
// Child becomes Zombie as parent is sleeping 
// when child process exits. 
int main() 
{ 
    // Fork returns process id 
    // in parent process 
    pid_t child_pid = fork(); 
  
    // Parent process  
    if (child_pid > 0) 
        sleep(50); 
  
    // Child process 
    else        
        exit(0); 
  
    return 0; 
} 



// ORPHAN:A process whose parent process no more exists i.e. either finished or terminated without waiting for its child process to terminate is called an orphan process.
// In the following code, parent finishes execution and exits while the child process is still executing and is called an orphan process now.
// However, the orphan process is soon adopted by init process, once its parent process dies.
// A C program to demonstrate Orphan Process.  
// Parent process finishes execution while the 
// child process is running. The child process 
// becomes orphan. 
int main() 
{ 
    // Create a child process       
    int pid = fork(); 
  
    if (pid > 0) 
        printf("in parent process"); 
  
    // Note that pid is 0 in child process 
    // and negative if fork() fails 
    else if (pid == 0) 
    { 
        sleep(30); 
        printf("in child process"); 
    } 
  
    return 0; 
} 