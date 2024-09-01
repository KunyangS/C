// READ A FILE: wrote to a file using w and a modes inside the fopen() function
// to read from a file, you can use the r mode
FILE *fptr;
fptr = fopen("filename.txt","r");
char myString[100]; // store the content of the file
fgets(myString,100,fptr);//using the fgets() function to read the content of filename.txt
printf("%s", myString); //print the file content
fclose(fptr);//close the file

// fgets function only reads the first line of the line.
// use a while loop to read every line of the file
FILE *fptr;
fptr = fopen("filename.txt","r");//open a file in read mode
char myString[100];//store the content of the file
while(fgets(myString,100,fptr)){//read the content and print it
    printf("%s",myString);
}
fclose(fptr);//close the file

// if open a file for reading that does not exist, the fopen()function will return NULL.
FILE *fptr;
fptr = fopen("loremipsum.txt","r");//open a file in read mode
if(fptr == NULL){ // print some text if the file does not exist
    printf("Not able to open the file.");
}
fclose(fptr);// close the file

// if the file exist, read the content and print it. if the file does not exist, print a message
FILE *fptr;
fptr = fopen("filename.txt","r");//open a file in read mode
char myString[100];//store the content of the file
if(fptr !=NULL){//if the file exist
    while(fgets(myString,100,fptr)){//read the content and print it
        printf("%s",myString);
    }
} else {//if the file does not exist
    printf("Not able to open the file.");
}
fclose(fptr);//close the file