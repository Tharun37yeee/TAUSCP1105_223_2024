#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "phonebook1.txt"

typedef struct 
{
    char name[50];
    char phone[15];
    char email[50];
    char address[50];
} Contact;

void addContact() 
{
    FILE *fp = fopen("phonebook1.txt", "a");
    if (fp == NULL) 
    {
        printf("Error opening file!\n");
        return;
    }

    Contact c;
    printf("Enter name: ");
    scanf(" %[^\n]", c.name);
    printf("Enter phone number: ");
    scanf(" %[^\n]", c.phone);
    printf("Enter email : ");
    scanf(" %[^\n]", c.email);
    printf("Enter address : ");
    scanf(" %[^\n]", c.address);

    fwrite(&c, sizeof(Contact), 1, fp);
    fclose(fp);
    printf("Contact saved successfully.\n");
}

void displayContacts() 
{
    FILE *fp = fopen("phonebook1.txt", "r");
    if (fp == NULL) 
    {
        printf("No contacts found.\n");
        return;
    }

    Contact c;
    printf("\n--- Contact List ---\n");
    while (fread(&c, sizeof(Contact), 1, fp)) 
    {
        printf("Name: %s\nPhone: %s\nEmail: %s\nAddress: %s\n\n", c.name, c.phone, c.email, c.address);
    }
    fclose(fp);
}

void modifyContact()
{
    FILE *fp = fopen("phonebook1.txt","rb+");
    if(fp == NULL)
    {
        printf("No contacts found :(");
        return;
    }
    int pos, found;
    Contact c;
    char name[50];
    printf("Enter the name of the contact that you want to modify : ");
    scanf(" %[^\n]", name);
    while(fread(&c, sizeof(Contact), 1, fp))
    {
       if (strcmp(c.name, name) == 0) 
       {
            found = 1;
            pos = ftell(fp) - sizeof(Contact); 

            int choice;
            printf("Which field do you want to modify?\n");
            printf("1. Name\n2. Phone\n3. Email\n4. Address\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) 
            {
                case 1:
                    printf("Enter new name: ");
                    scanf(" %[^\n]", c.name);
                    break;
                case 2:
                    printf("Enter new phone: ");
                    scanf(" %[^\n]", c.phone);
                    break;
                case 3:
                    printf("Enter new email: ");
                    scanf(" %[^\n]", c.email);
                    break;
                case 4 : 
                    printf("Enter neew address : ");
                    scanf(" %[^\n]", c.address);
                    break;
                default:
                    printf("Invalid choice.\n");
                    fclose(fp);
                    return;
            }

            fseek(fp, pos, SEEK_SET);
            fwrite(&c, sizeof(Contact), 1, fp);
            printf("Contact updated.\n");
            break;
        }
    }
    if(!found)
        printf("Contact not found :(");
    fclose(fp);
}


void searchContact() 
{
    char searchName[50];
    int found = 0;
    Contact c;

    printf("Enter name to search: ");
    scanf(" %[^\n]", searchName);

    FILE *fp = fopen("phonebook1.txt", "r");
    if (fp == NULL) 
    {
        printf("No contacts found.\n");
        return;
    }

    while (fread(&c, sizeof(Contact), 1, fp)) 
    {
        if (strcmp(c.name, searchName) == 0) 
        {
            printf("\nContact found :)\n\nName: %s\nPhone: %s\nEmail: %s\nAddress: %s\n\n", c.name, c.phone, c.email, c.address);
            found = 1;
            break;
        }
    }
    if (!found) 
    {
        printf("Contact not found.\n");
    }

    fclose(fp);
}

void deleteContact() 
{
    char nameToDelete[50];
    int found = 0;

    printf("Enter the name of the contact to delete: ");
    scanf(" %[^\n]", nameToDelete);

    FILE *fp = fopen("phonebook1.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) 
    {
        printf("File error.\n");
        return;
    }

    Contact c;
    while (fread(&c, sizeof(Contact), 1, fp)) 
    {
        if (strcmp(c.name, nameToDelete) != 0) 
        {
            fwrite(&c, sizeof(Contact), 1, temp);
        } 
        else 
            found = 1;
        
    }

    fclose(fp);
    fclose(temp);

    remove("phonebook1.txt");
    rename("temp.txt", "phonebook1.txt");

    if (found)
        printf("Contact deleted successfully.\n");
    else
        printf("Contact not found.\n");
}

void main() {
    int choice;

    while (1) 
    {
        printf("\n---  :: Phonebook Menu ::  ---\n");
        printf("1. Add Contact\n");
        printf("2. Display Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Delete Contact\n");
        printf("5. Modify Contact\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1: addContact(); 
                    break;
            case 2: displayContacts(); 
                    break;
            case 3: searchContact(); 
                    break;
            case 4: deleteContact(); 
                    break;
            case 5: modifyContact();
                    break;
            case 6: exit(0);
            default: printf("Invalid choice. Try again.\n");
        }
    }

    //getch();
}
