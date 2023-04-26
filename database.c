#include <stdio.h>
#include <string.h> 
#include "record.h"
#include <stdlib.h>
#include "globals.h"
/* 

class: ics 212

prof: Ravi 

Name: William Evers-Hood 

Function: deleterecord

purpose: deletes record from a linked list data base stored on the heap

parameters: struct record ** start: keeps track of the beginning of the list and is stored on the stack
            int uaccountno: the account number of the record to be added, used to tell where in the database the records is to be stored

return: -1: was not able to delete the record for whatever reason
         0: successfully deleted the record

*/


int deleteRecord(struct record **start, int uaccountno)
{
    int trig, none, startdel, counter;
    struct record *current, *coming, *remove;
    trig = -1;
    counter = 0;
    if((*start) == NULL)
    {
        return trig;
    }
    current = *start;
    coming = (**start).next;
    trig = 1;
    do
    {	
        startdel = 0;
        none = 1;
        while (uaccountno == (*current).accountno)
        {
            counter++;
            trig = 0;
            (*start) = (*current).next;
            free(current);
            current = *start;
            if((current == NULL))
            {
                return trig;
            }
            coming = (*current).next;
            none = 0;
            startdel = 1;
        } 
        if(coming != NULL)
        {
            if(uaccountno == (*coming).accountno && startdel == 0)
            {
                counter++;
                remove = (*current).next; 
                coming = (*remove).next; 
                (*current).next = coming;
                free(remove);
                trig = 0;
                none = 0;
            }
        }
        if (none == 1)
        {
            current = (*current).next;
            coming = (*coming).next; 
        }
    } while (coming != NULL);
    if (debugmode == 1)
    {
    printf("delete method debug: # of file deleted %d\n", counter);
    }
    return trig;
}






/*

class: ics 212

prof: Ravi 

Name: William Evers-Hood 

Function: addrecord

purpose: adds record to a linked list data base stored on the heap

parameters: struct record ** start: keeps track of the beginning of the list and is stored on the stack
            int uaccountno: the account number of the record to be added, used to tell where in the database the records is to be stored
            char unamme[]: character array contianing the name of the account holder
            char uaddress[]: character array containing the address of the account holder 

return: -1: was not able to add the record for whatever reason
         0: successfully added the record

*/


void addRecord(struct record ** start, int uaccountno, char uname[], char uaddress[])
{
    struct record *current, *coming, *addition;
    if (*start == NULL)
    {
        *start = malloc(sizeof(struct record));
        (**start).accountno = uaccountno; 
        strcpy((**start).name, uname);
        strcpy((**start).address, uaddress);
        (**start).next = NULL;
        return;
    }
    addition = malloc(sizeof(struct record));
    (*addition).accountno = uaccountno;
    strcpy((*addition).name, uname);
    strcpy((*addition).address, uaddress);
    (*addition).next = NULL;
    if(uaccountno < (**start).accountno)
    {
        current = (*start); 
        (*start) = addition;
        (**start).next = current;
        return;
    }
    current = (*start);
    coming = (*current).next;
    if(coming == NULL)
    {
        (**start).next = addition;
        return;
    }
    if (uaccountno < (*coming).accountno)
    {
        (*current).next = addition;
        (*addition).next = coming;
	return;
    }
    while(coming != NULL)
    {
        current = coming; 
        coming = (*current).next;
        if(coming == NULL)
        {
            (*current).next = addition;
            return; 
        }  
        if(uaccountno < (*coming).accountno)
        {
            (*current).next = addition;
            (*addition).next = coming;
            return;
        }                             
    }
}                                                   

/*

class: ics 212

prof: Ravi 

Name: William Evers-Hood 

Function: addrecord

purpose: prints all records in the heap to the command line 

parameters: struct record * start: keeps track of the beginning of the list and is stored on the stack
            
return: -1: void
*/
void printAllRecords (struct record *start)

{
    int counter;
    struct record *current;
    counter = 0; 
    current = start;
    if (start == NULL)
    {
        printf("empty list \n");
        return;
    }
    do
    {
        counter++;
        printf("account number: %d\n", (*current).accountno);
        printf("name: %s\n", (*current).name);
        printf("address: %s\n", (*current).address);
        current = (*current).next;
    } while (current != NULL);
    if(debugmode == 1)
    {
        printf("printall debug mode: # of record printed %d\n", counter);
    } 
}



/*

class: ics 212

prof: Ravi 

Name: William Evers-Hood 

Function: findrecord

purpose: prints all records in the heap to the command line 

parameters: struct record ** start: keeps track of the beginning of the list and is stored on the stack
            
return: -1: was not able to find the record for whatever reason
         0: successfully found the records
*/



int findRecord(struct record *start, int uaccountno)
{
    int trig, none, counter;
    struct record *current;
    trig = -1;
    if((start) == NULL)
    {
        return trig;
    }
    current = start;
    trig = 1;
    
    do
    {
        none = 1;
        if (uaccountno == (*current).accountno)
        {
            counter++;
            trig = 0;
            printf("account number %d\n", (*current).accountno);
            printf("address  %s\n", (*current).address);
            printf("name %s\n", (*current).name);
            current = (*current).next;
            none = 0;
        }
        if (none == 1)
        {
            current = (*current).next;
        }
    } while (current != NULL);
    if(debugmode == 1)
    {
        printf("debug mode for find record: # of record printed %d\n", counter);
    }
    return trig;
}

/*****************************************************************
//
//  Function name: writefile
//
//  DESCRIPTION:   writes to a file with the contents of an array
//
//  Parameters:    struct record *start: keeps track of the beginning of the list on the stack
//                 char contents[]: keeps the name of the file to be opened
//
//  Return values:  0 : file was opened and contents were added sucessfully
//                 -1 : file was not opened
//
****************************************************************/



int writefile (struct record *start, char contents[])
{
    struct record *current;
    FILE * filep;

    char addressPrime[50];
    int trig;
    trig = -1;
    current = start;
    if(start == NULL)
    {
        return trig;
    }  
    filep = fopen(contents, "w");
    if(filep == NULL)
    {
        return trig;
    }    
    do
    {
        if (debugmode == 1)
        {
            printf("debug mode accountno: %d\n", (*current).accountno);
            printf("debug mode name: %s\n", (*current).name);
            printf("debug mode address: %s\n", (*current).address);
            printf("debug done\n");
        }
        fprintf(filep, "%d\n", (*current).accountno);
        fprintf(filep, "%s\n", (*current).name);
        strcpy(addressPrime, (*current).address);
        strcat(addressPrime, "///");
        strcpy((*current).address, addressPrime);
        fprintf(filep, "%s\n", addressPrime);
        current = (*current).next;
        
    } while (current != NULL);
    fprintf(filep, "*\n");
    fclose(filep); 
    return trig;
}






/*****************************************************************
//
//  Function name: readfile
//
//  DESCRIPTION: read file reads information from a txt file and puts it back into
//               the heap to be manipulated by a user
//
//  Parameters:  struct record ** start: keeps track of the start of the list
//               char contents[]: holds the name of the file to be opened
//
//  Return values:  0 : file was opened and contents were read
//                 -1 : file was not able to be opened 
//
****************************************************************/


int readfile( struct record ** start, char contents[])
{
    FILE * filep;
    int trig, accountnoPrime, counter, flip, val, size;
    long i;
    int * intp;
    char namePrime[30];
    char addressPrime[50];
    counter = 0;
    val = 0;
    trig = 0;
    flip = -1; 
    i = 0;
    filep = fopen(contents, "r");
    if (filep == NULL)
    {
        return flip;
    }
    do
    {
        if (i % 3 == 0 && i != 0)
        {	    
            if (debugmode == 1)
            {
                printf("debug mode accountno: %d\n", accountnoPrime);
                printf("debug mode name: %s\n", namePrime);
                printf("debug mode address: %s\n", addressPrime);
            }
            addRecord(start, accountnoPrime, namePrime, addressPrime);
        }
        if(i % 3 == 0)
        {
            intp = &accountnoPrime;
            flip = fscanf(filep, "%d", intp );
            if (accountnoPrime == 42)
            {
                return 0;
            }
        }
        if (i % 3 == 1)
        {
            fscanf(filep, "%s", namePrime);
            size = strlen(namePrime);
            namePrime[size] = '\0';
        }
        if (i % 3 == 2)
        {
            trig = 0;
            counter = 0;
            val = 0;
            while(counter < 50 && trig < 3)
            {             
                addressPrime[counter] = fgetc(filep);
                if (addressPrime[counter] == 47)
                {
                    trig++;
                }
                if(val >= 1)
                {
                    counter++;
                }
                val++;
            }
            addressPrime[counter - 3] = '\0';
        }
        i++;
    } while(flip == 1);
    fclose(filep);
    return flip;
}



/*

class: ics 212

prof: Ravi 

Name: William Evers-Hood 

Function: cleanup

purpose: deallocates all heap space when main exits 

parameters: struct record ** start: keeps track of the beginning of the list and is stored on the stack
            
return: void
*/
void cleanup(struct record** start)
{
    struct record *current, *coming; 
    int counter;
    current = *start;
    counter = 0;
    if((*start) == NULL)
    {
        return;
    }	
    do 
    {
        counter++;
        coming = (*current).next;
        free(current);
        current = (coming);
    } while (current != NULL);
    if(debugmode == 1)
    {
        printf("cleanup debug mode: %d records deallocatted from heap \n", counter);
    }
    *start = NULL;
    
}

