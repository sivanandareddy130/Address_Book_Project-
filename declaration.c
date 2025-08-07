#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include "contact.h"
int isvalidname(char str[]) {
    for (int i = 0; str[i]; i++) 
    {
        if (!isalpha(str[i]) && str[i] != ' ')   // Check for non-alphabetic and non-space characters
            return 0;
    }
    return 1;  // valid name
}

// Function to validate if a phone number is 10 digits long and all digits
int isvalidphone(char str[],int len) {
    if (strlen(str) != 10) return 0;   // Check length of phone number
    for (int i = 0; i < 10; i++) 
    {
        if (!isdigit(str[i]))   // Check if each character is a digit
         return 0;
    }
    
    return 1;   // Valid phone number

}

// Function to validate if an email is in proper format
int isvalidmail(char str[])
{
if (strchr(str, '@') == NULL) 
{
    printf("Error: Missing '@' in email\n");
    return 0;
}

int len = strlen(str);
if (len < 5 || str[len-4]!='.'||str[len-3]!='c'||str[len-2]!='o'||str[len-1]!='m') 
{
    printf("Error: Email must end with '.com'\n");
    return 0;
}

return 1;
}

int uniqphone(AddressBook *addressBook, char *phone) {
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].phone, phone) == 0)  // compare phone numbers
            return 0;   //phone number is not unique
    }
    return 1;  //phone number is unique
}

// Function to check if an email is unique in the address book
int uniqmail(AddressBook *addressBook, char *email) {
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].email, email) == 0) //compare emails
            return 0;   // not unique
    }
    return 1;    //unique
}