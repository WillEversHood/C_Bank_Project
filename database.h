 #include "record.h"

/*
 * name: addRedcord
 *
 * function: adds record to a database
 *
 * parameters: ** to the custom data type record, int acctnum: account number, char* name: string with name,
 *             char* address, string pointer containing reference to a string containing a string
 *
 * output: void
 *
 */

 void addRecord (struct record **, int, char [], char []);

/*
 * name: printAllRecords
 *
 * function: print the entire database of struct record consecutively in order
 *
 * parameters: struct record*: pointer to datatype record
 *
 * output: void
 *
 */
 void printAllRecords(struct record *);

/* 

class: ics 212

prof: Ravi 

Name: William Evers-Hood 

Function: findrecord

purpose: finds and prints a record from a linked list

parameters: struct record ** start: keeps track of the beginning of the list and is stored on the stack
            int uaccountno: the account number of the record to be added, used to tell where in the database the records is to be stored

return: -1: was not able to find the record for whatever reason
         0: successfully found the record

*/

 int findRecord (struct record *, int);

/* 

class: ics 212

prof: Ravi 

Name: William Evers-Hood 

Function: deleterecord

purpose: deletes record from a linked list data base stored on the heap

parameters: struct record ** start: keeps track of the beginning of the list and is stored on the heap
            int uaccountno: the account number of the record to be added, used to tell where in the database the records is to be stored

return: -1: was not able to delete the record for whatever reason
         0: successfully deleted the record

*/

 int deleteRecord(struct record **, int);


/* 

class: ics 212

prof: Ravi 

Name: William Evers-Hood 

Function: writefile

purpose: takes the contents of the linked list nad puts them into a txt file

parameters: struct record * start: keeps track of the beginning of the list and is stored on the stack
            char contents[]: the name of the file to be written too

return: -1: was not able to open the file
         0: successfully opened and put all of the data into the linked list

*/


 int writefile (struct record *, char []);

 printf("account number %d\n", (*current).accountno);

/* 

class: ics 212

prof: Ravi 

Name: William Evers-Hood 

Function: readfile

purpose: reads a file and takes the information from that file and puts it into a linked list of type struct record

parameters: struct record ** start: keeps track of the beginning of the list on the stack and is stored on the heap
            char contents[], the name of the file to be opened

return: -1: was not able to open the file
         0: successfully opened and read the file

*/

 int readfile (struct record **, char []);


/* 

class: ics 212

prof: Ravi 

Name: William Evers-Hood 

Function: cleanup

purpose: deletes all of the linked list from the heap when the main method closes

parameters: struct record ** start: keeps track of the beginning of the list and is stored on the heap
            

return: void

*/
 void cleanup(struct record **);



