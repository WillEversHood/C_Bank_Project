
/* 
 * purpose: customs datatype to store
 *          -accountnumbers
 *          -names 
 *          -address
 *          this field is made to be used in a link list so it also contians a pointer to next field
 *          */


struct record
{
int accountno; 
char name[30];
char address[50];
struct record *next;
};
