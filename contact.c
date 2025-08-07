#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook, int sortCriteria) {
    int n = addressBook->contactCount;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            int cmp = 0;
            switch (sortCriteria) {
                case 1:       // Name
                    cmp = strcmp(addressBook->contacts[j].name, addressBook->contacts[j + 1].name);
                    break;
                case 2:        // Phone
                    cmp = strcmp(addressBook->contacts[j].phone, addressBook->contacts[j + 1].phone);
                    break;
                case 3:        // Email
                    cmp = strcmp(addressBook->contacts[j].email, addressBook->contacts[j + 1].email);
                    break;
                default:      //invalid sort criteria
                    printf("Invalid sort criteria.\n");
                    return;
            }

              // Swap if current contact is greater than next based on comparison
            if (cmp > 0) {
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = temp;
            }
        }
    }
      
     // Print the sorted list of contacts
    for (int i = 0; i < n; i++) {
        printf("%s\t%s\t%s\n", addressBook->contacts[i].name,
               addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
}
void initialize(AddressBook *addressBook)
 {
    addressBook->contactCount = 0;
    populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) 
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

void createContact(AddressBook *addressBook) {
    char name[50], phone[15], email[50];

     // Step 1: Name
    while (1) {
        printf("Enter Name: ");
        scanf("%s", name);
        if (isvalidname(name))   //checking the name is valid or not
        {
            break;
        }
         else 
        {
            printf("Invalid name. Please enter only alphabets.\n");
        }
       
    }

    // Step 2: Mobile
    while (1) {
        printf("Enter Mobile Number: ");
        scanf("%s", phone);
        if (isvalidphone (phone,strlen(phone)))    //checking phone and length of phone is valid or not
        {
            if (uniqphone(addressBook, phone))    //checking if phone aleady exist or not
             {
                break;
            } else 
            {
                printf("Duplicate mobile number. Try again.\n");
            }
        }
         else 
        {
            printf("Mobile number must be 10 digits.\n");
        }
    }

    // Step 3: Email
    while (1) {
        printf("Enter Email ID: ");
        scanf("%s", email);
        if (isvalidmail(email))                   //checking valid mail or not
        {
            if (uniqmail(addressBook, email))      //checking if phone aleady exist or not
            {
                break;
            } 
            else 
            {
                printf("Duplicate email. Try again.\n");
            }
        } 
        else
         {
            printf("Invalid email format. Try again.\n");
        }
       
    }

    // Store the contact
    int count = addressBook->contactCount++;
        strcpy(addressBook->contacts[count].name,name);
        strcpy(addressBook->contacts[count].phone,phone);
        strcpy(addressBook->contacts[count].email,email);
        
        printf("Contact added successfully!\n");
}

void searchContact(AddressBook *addressBook) 
{
    int option;
    char input[50];
    int found = 0;

    if (addressBook->contactCount == 0)   // Check if there are any contacts
     {
        printf("No contacts available to search.\n");
        return;
    }
      
     // Display search menu
    printf("\nSearch by:\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("Enter your choice: ");
    scanf("%d", &option);     // Read user choice
      
    // Switch based on user’s search option
    switch (option) 
    {
        case 1:   // Search by name
        {
            printf("Enter the name to search: ");
            scanf(" %[^\n]", input);
            for (int i = 0; i < addressBook->contactCount; i++) 
            {
                if (strcmp(addressBook->contacts[i].name, input) == 0)   // Compare names
                {
                    printf("\nContact Found:\n");
                    printf("Name : %s\n", addressBook->contacts[i].name);
                    printf("Phone: %s\n", addressBook->contacts[i].phone);
                    printf("Email: %s\n", addressBook->contacts[i].email);
                    found = 1;    // Mark name as found

                }
            }
            break;

            }

        case 2:   // Search by phone number
        {
            printf("Enter the phone number to search: ");
            scanf(" %s", input);
            for (int i = 0; i < addressBook->contactCount; i++)
             {
                if (strcmp(addressBook->contacts[i].phone, input) == 0)   // Compare phone
                {
                    printf("\nContact Found:\n");
                    printf("Name : %s\n", addressBook->contacts[i].name);
                    printf("Phone: %s\n", addressBook->contacts[i].phone);
                    printf("Email: %s\n", addressBook->contacts[i].email);
                    found = 1;   // Mark contact as found
                  
                }
            }
            break;
        }

        case 3:     // Search by email
        {
            printf("Enter the email to search: ");
            scanf(" %s", input);
            for (int i = 0; i < addressBook->contactCount; i++)
             {
                if (strcasecmp(addressBook->contacts[i].email, input) == 0)
                 {
                    printf("\nContact Found:\n");
                    printf("Name : %s\n", addressBook->contacts[i].name);
                    printf("Phone: %s\n", addressBook->contacts[i].phone);
                    printf("Email: %s\n", addressBook->contacts[i].email);
                    found = 1;  //// Mark email as found
               
                }
            }
            break;
        }

        default:    // Invalid search option

        {
            printf("Invalid search option.\n");
            break;
        }
    }

    if (!found)    // input not found 
    {
        printf("No contact found matching the given input.\n");
        return;
    }
   
}

void editContact(AddressBook *addressBook)
{
    char name[20];         // Buffer to store the name input
    int found = 0;         // Flag to check if contact is found

    if (addressBook->contactCount == 0)  // Check if there are any contacts
    {
        printf("No contacts to edit.\n");
        return;
    }

    printf("Enter the name of the contact to edit: ");
    scanf(" %[^\n]", name);  // Read the full line input for name

    // Loop through all contacts to find the matching name
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strcmp(addressBook->contacts[i].name, name) == 0)  // Compare contact names
        {
            found = 1;  // Mark that contact is found

            // Display contact details
            printf("\nContact Found:\n");
            printf("1. Name : %s\n", addressBook->contacts[i].name);
            printf("2. Phone: %s\n", addressBook->contacts[i].phone);
            printf("3. Email: %s\n", addressBook->contacts[i].email);

            int choice;
            // Ask user what they want to edit
            printf("\nWhat would you like to edit?\n");
            printf("1. Name\n");
            printf("2. Phone\n");
            printf("3. Email\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            // Handle user choice
            switch (choice) 
            {
                case 1: // Edit name
                {
                    char newName[50];
                    printf("Enter new name: ");
                    scanf(" %[^\n]", newName);  // Read new name input
                    if (!isvalidname(newName))  // Validate name
                    {
                        printf("Error: Invalid name.\n");
                        return;
                    }
                    strcpy(addressBook->contacts[i].name, newName);  // Update name
                    break;
                }
                case 2: // Edit phone
                {
                    char newPhone[20];
                    printf("Enter new phone: ");
                    scanf(" %s", newPhone);  // Read new phone number
                    if (!isvalidphone(newPhone, strlen(newPhone)))  // Validate phone
                    {
                        printf("Error: Invalid phone number.\n");
                        return;
                    }
                    if (!uniqphone(addressBook, newPhone))  // Check uniqueness
                    {
                        printf("Error: Phone number already exists.\n");
                        return;
                    }
                    strcpy(addressBook->contacts[i].phone, newPhone);  // Update phone
                    break;
                }
                case 3: // Edit email
                {
                    char newEmail[50];
                    printf("Enter new email: ");
                    scanf(" %s", newEmail);  // Read new email
                    if (!isvalidmail(newEmail))  // Validate email format
                    {
                        printf("Error: Invalid email.\n");
                        return;
                    }
                    if (!uniqmail(addressBook, newEmail))  // Check email uniqueness
                    {
                        printf("Error: Email already exists.\n");
                        return;
                    }
                    strcpy(addressBook->contacts[i].email, newEmail);  // Update email
                    break;
                }
                default:  // Invalid choice handling
                    printf("Invalid choice.\n");
                    return;
            }

            // Confirm successful update
            printf("Contact updated successfully.\n");
        }
    }

    // If contact with specified name was not found
    if (!found)
    {
        printf("Error: Contact with phone number %s not found.\n", name);
    }
}

void deleteContact(AddressBook *addressBook)
{
    char contact[20];      // Buffer to hold the name of the contact to delete
    int found = 0;         // Flag to indicate whether the contact was found
    int option;

    // Prompt user to enter the contact name
    printf("ENTER THE CONTACT:\n");
    scanf(" %[^\n]", contact);

    // Prompt for search option (though not used here)
    printf("SELECT YOUR SEARCH OPTION:\n");

    // Loop through the contact list
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        // Check if the current contact name matches the input
        if (strcmp(addressBook->contacts[i].name, contact) == 0)
        {
            char ch;       // Variable to store user confirmation
            found = 1;     // Set flag to indicate contact is found

            // Display contact details
            printf("%s\t %s\t %s\n", addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);

            // Ask for deletion confirmation
            printf("DO YOU WANT DELETE THIS CONTACT(y & n):\n");
            scanf(" %c", &ch);

            if (ch == 'y')  // If user confirms deletion
            {
                // Shift remaining contacts one position left
                for (int j = i; j < addressBook->contactCount - 1; j++)
                {
                    addressBook->contacts[j] = addressBook->contacts[j + 1];
                }

                addressBook->contactCount--;  // Decrease contact count
                printf("CONTACT DELETE SUCCESSFULLY.\n");
            }
            else if (ch == 'n')  // If user cancels deletion
            {
                printf("CONTACT NOT DELETE.\n");
            }
            else  // Invalid input
            {
                printf("error:invalid input\n");
            }
        }
    }

    // If no matching contact is found
    if (!found)
    {
        printf("contact not found:\n");
    }
}