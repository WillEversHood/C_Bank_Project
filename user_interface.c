/*****************************************************************
//
//  NAME:        Ravi Narayan
//
//  HOMEWORK:    1
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        September 3, 2112
//
//  FILE:        template.c
//
//  DESCRIPTION:
//   Describe the file
//
****************************************************************/


#include<stdio.h>
#include<string.h>
#include "database.c"

 void getAddress(char [], int);
 void getName();
 int getFileNum();
/*****************************************************************
//
//  Function name: main
//
//  DESCRIPTION:   Don't forget to describe what your main
//                 function does.
//
//  Parameters:    argc (int) : The number of elements in argv
//                 argv (char*[]) : An array of arguments passed
//                                  to the program.
//
//  Return values:  0 : some meaning
//                 -1 : some meaning
// notes for tm put fgets at end of functions so that buffers clear
// fix the broken loop in the get address function 
// comments 
****************************************************************/
int debugmode;


int main(int argc, char* argv[])
{
    int  size, i, acctNum, addressSize, nameSize, quitter, task, validInput;
    char address[50]; 
    char name[30];
    char options[10];
    char contents[] = "bankstorage.txt";
    char add[] = "add";
    char printall[] = "printall";
    char find[] = "find";
    char delete[] = "delete";
    char quit[] = "quit";
    char debug[] = "debug";
    struct record * start = NULL;
    addressSize = 100;
    nameSize = 30; 
    quitter = 1;
    validInput = 1;
    printf("Welcome to the bank user interface\n");
    printf("Options include 'add' to add a record\n");
    printf("'printall' to print all records\n");
    printf("'find' to find a record\n");
    printf("'delete' to delete a record\n");
    printf("'quit' to quit the program\n");
    printf("type and enter the name of an option to proceed\n");
    if (argc != 1)
    {
        if (argc > 2)
        {
            quitter = 0;
            printf("invalid command line input\n");
        }
        else if(strcmp(argv[1], debug) != 0)
        {
           quitter = 0;
           printf("invalid command line input\n");
        }
        else
        { 
            debugmode = 1;
            printf("in debug mode\n");
        }
    }
    readfile(&start, contents); 
    while (quitter == 1)
    {
        task = 1;
        validInput = 1;
        fscanf(stdin, "%s", options);
        size = strlen(options);
        switch(options[0])
        {
            case 'a':
                for(i = 0; i < size; i++)
                {
                    if(strncmp(add, options, size) != 0)
                    {
                        validInput = 0;
                    }
                }
                if (validInput == 1)
                {
                    /*  link and print */
                    acctNum = getFileNum();
                    getAddress(address, addressSize);
                    getName(name, nameSize);
                    /*interface with database*/
                    addRecord (&start, acctNum, name, address);
                    printf("record addition complete\n");
                }
                else 
                {
                    printf("please enter valid input\n");
                }     
                break;   
                case 'p':
                for(i = 0; i < size; i++)
                {
                    if(strncmp(printall, options, size) != 0)
                    {
                        validInput = 0;
                    }
                }
                if (validInput == 1)
                {
                    /*  link and print */
                    printf("printing all records\n");
                    printAllRecords(start);
                    printf("done\n");
                }
                else 
                {
                    printf("please enter valid input\n");
                }             
                break; 
                case 'f':
                for(i = 0; i < size; i++)
                {
                    if(strncmp(find, options, size) != 0)
                    {
                        validInput = 0;
                    }
                }
                if(validInput == 1)
                {
                    while (task != 0)
                    {
                        /*  link and print */
                        printf("finding account info\n");
                        acctNum = getFileNum();
                        task = findRecord(start, acctNum);
                        printf("account found\n");
                        if (task != 0)
                        {
                            printf("please enter valid account info\n");
                        }
                    } 
                } 
                else
                {
                    printf("please enter valid input\n"); 
                }      
                break; 
                case 'd':
                for(i = 0; i < size; i++)
                {
                    if(strncmp(delete, options, size) != 0)
                    {
                    validInput = 0; 
                    }
                }
                    if(validInput == 1)
                    {
                        while (task != 0)
                        {    
                            /*  link and print */
                            printf("deleting account info\n");
                            task = deleteRecord(&start, getFileNum()); 
                            printf("account deleted\n");
                            if (task != 0)
                            {
                                printf("please enter valid account info\n");
                            }
                        }
 
                    } 
                    else 
                    {
                        printf("please enter valid input\n");
                    }
                break; 
                case 'q':
                printf("size %d\n", size);
                for(i = 0; i < size; i++)
                {
                    if(strncmp(quit, options, size) != 0)
                    {
                       
                        /*  link and print */
                        validInput = 0;        
                    } 
                }
                if(validInput == 1) 
                {
                    printf("program exiting\n");
                    quitter = 0;
                }
                else 
                {
                    printf("please enter valid input\n");
                }
            break; 
            default:
               {
                   printf("plese insert acceptable input\n");
               }  
           break;
           }   
    }
    writefile(start, contents); 
    cleanup(&start);
    return 0;
}

/*****************************************************************
//
//  Function name: getFileNum()
//
//  DESCRIPTION:   This function uses a while loop to get a single positve int value
//                 to take as a file num
//
//           
//  Parameters:     none
//
//  Return values: int a file number
//
****************************************************************/

int getFileNum()
{
    int account, trigger;
    char trash[50];
    trigger = 1;
    printf("please enter valid account number\n");
    while (trigger == 1)
    {
        fgets(trash, 50, stdin);
        if(fscanf(stdin, "%d", &account) == 1 && account > 0)
        {
            trigger = 0;
        }
        else 
        {
            printf("invalid accountnumber try again\n");
        }
    }
    if(debugmode == 1)
    {
         printf("\nDebug info\n");
         printf("getFileNum output %d\n", account);
    } 
    return account;
}


/*****************************************************************
//
//  Function name: getAddress
//
//  DESCRIPTION:   This function uses a loop and fgets in combination
//                 with an exit sequence to get a multi line address 
//                 with multiple newlines //
//  Parameters:    char * pointer to array addressPrime[] storing, int Size: the size of the //                 char array 
//
//  Return values: none 
//
****************************************************************/



void getAddress(char addressPrime[], int size)
{
    int trig, counter, sizePrime;
    char trash[50];
    counter = 0;
    trig = 1;
    fgets(trash, 50, stdin);
    printf("please enter your address\n Enter /// when complete\n");
    while(counter < size && trig < 3)
    {
        addressPrime[counter] = fgetc(stdin);
        if (addressPrime[counter] == 47)
        {
            /*fgets(trash, 100, stdin);*/
            trig++;
        }
        counter++;
    }
    addressPrime[counter - 2] = '\0';
    if (debugmode == 1)
    {
         printf("\nDebug info\n");
         printf("Address: %s\n", addressPrime);
         sizePrime = strlen(addressPrime);
         printf("Address Length: %d\n", sizePrime);
    }
    return;
}

/*****************************************************************
//
//  Function name: getName
//
//  DESCRIPTION:   function that gets a string name value that is ended
//                 when the user enter newline
//
//  Parameters:    char* namePrime[]: this is the array that the name will be stored in
//                 int size: size lets the functio nknow how big the array is
//
//  Return values: none
//
****************************************************************/


void getName(char namePrime[], int size)
{
    int trig, counter, nameLen;
    char trash[50];
    counter = 0;
    trig = 1;
    fgets(trash, 50, stdin);
    printf("please enter your name\n");
    while (counter < size && trig == 1)
    {
        namePrime[counter] = fgetc(stdin);
        if (namePrime[counter] == 10)
        {
           /* fgets(trash, 100, stdin);*/                               
            trig = 0;
            namePrime[counter] = '\0';
        }
        counter++;
    }
    if (debugmode == 1)
    {
        printf("Name: %s\n", namePrime);
        nameLen = strlen(namePrime); 
        printf("name length %d\n", nameLen);
    }
    return;
}
 
