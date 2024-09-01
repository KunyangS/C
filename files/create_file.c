// FILE HANDLING: you can create,open,read,and write to files by declaring a pointer of type FILE, and use the fopen() function
FILE *fpter;
fpter = fopen(filename,mode); // fopen() is used to open a file
// FILE: a basically a date type, and we need to create a pointer variable to work the it(fptr)
// filename: the name of the actual file you want to open(or create), like filename.txt
// mode: a single character,which represents what you want to do with the file(read, write or append)
// mode: w - writes to a file. a - appends new data to a file. r - reads from a file.

// CREATE A FILE: ust the w mode inside the fopen() function
// the w mode is used to write to a file. however, if the file does not exit, it will create one for you.
FILE *fptr;
fptr = fopen("filename.txt","w");// create a file
fclose(fptr);// close the file
// create the file in a specific folder,just provide an absolute path
fptr = fopen("C:\directoryname\filename.txt","w");
