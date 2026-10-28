#include <stdio.h>
#include <string.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fp = fopen("contact.csv", "w");

    if(fp == NULL)
    {
        printf("Unable to open file\n");
        return;
    }

    // Save all contacts
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fp, "%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fp);

    printf("Contacts saved successfully\n");
}

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fp = fopen("contact.csv", "r");

    if(fp == NULL)
        return;

    Contact temp;

    while(fscanf(fp, "%49[^,],%19[^,],%49[^\n]\n",temp.name,temp.phone,temp.email) == 3)
    {
        int duplicate = 0;

        // Check if contact already exists
        for(int i = 0; i < addressBook->contactCount; i++)
        {
            if(strcmp(temp.phone, addressBook->contacts[i].phone) == 0)
            {
                duplicate = 1;
                break;
            }
        }
        // Add only if not duplicate
        if(!duplicate && addressBook->contactCount < MAX_CONTACTS)
        {
            addressBook->contacts[addressBook->contactCount] = temp;
            addressBook->contactCount++;
        }
    }

    fclose(fp);
}