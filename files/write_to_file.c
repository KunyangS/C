// WRITE TO A FILE: use the w mode to write something the file we just created
// the w mode means that the file is opened for writing. to insert content to it, we can use the fprintf() funciton and add the pointer variable(fptr in our example) and some text
FILE *fptr;
fptr = fopen("filename.txt","w"); // open a file in writing mode
fprintf(fptr,"some text"); // write some text to the file
fclose(fptr); // close the file
// if i write to a file that already exists, the old content is deleted, and the new contect is inserted. this is important to know, as you might accidentally erase existing content.
fprintf(fptr,"Hello World!"); // as a result, when we open the file on our computer, it says "Hello World!" instead of "Some text"

// APPEND CONTECT TO A FILE: add content to a file without deleting the old contect
// the a mode appends contect at the end of the file
FILE *fptr;
fptr = fopen("filename.txt","a"); // open a file in append mode
fprintf(fptr,"\nHi everybody!"); // Append some text to the file
fclose(fptr); // close the file