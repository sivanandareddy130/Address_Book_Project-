#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fptr;
    fptr = fopen("contacts.csv", "w");  // Open file for writing
    if (fptr == NULL)                   
    {
        fprintf(stderr, "can not open the file\n");   // Print error if failed
        return;
    }
    for (int i = 0; i < addressBook->contactCount; i++)  // Loop through all contacts
    {
         // Write each contact's name, phone, and email to the file
        fprintf(fptr, "%s,%s,%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        
    }
    fclose(fptr);  // Close the file
}

// Function to load contacts from a file into the address book
void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fptr;

    fptr = fopen("contacts.csv", "r");   // Open file for reading
    if (fptr == NULL)
    {
        fprintf(stderr, "can not open the file\n");  // Print error if failed
        return;
    }
    int i = 0;
    while (1)
    {
        int ret = 0;
        // Read contact details from file and store into the address book
        ret = fscanf(fptr, "%[^,],%[^,],%[^\n]\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        if (ret != 3)     // If reading fails or doesn't get all 3 fields, break the loop
        {
            break;
        }
        i++;     // Move to the next contact slot
    }
    addressBook->contactCount = i;    // Update the total number of contacts
    fclose(fptr);
}