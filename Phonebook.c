#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct list {
    char name[15];
    char number[15];
    char address[50];
    struct list* next;
};

typedef struct list list;

list* CreateContact(char name[], char number[], char address[]) {
    list* newcontact = (list*)malloc(sizeof(list));
    strcpy(newcontact->name, name);
    strcpy(newcontact->number, number);
    strcpy(newcontact->address, address);
    newcontact->next = NULL;
    return newcontact;
}

void InsertContact(list** phonebook, char name[], char number[], char address[]) {
    list* contact = CreateContact(name, number, address);

    char firstChar = toupper(name[0]);
    int index = firstChar - 'A';
    list* temp = phonebook[index];

    if (temp == NULL) {
        phonebook[index] = contact;
    }
    else {
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = contact;
    }
}

void DeleteContact(list** phonebook, char name[]) {
    char firstChar = toupper(name[0]);
    int index = firstChar - 'A';
    list* temp = phonebook[index];
    list* previous = NULL;

    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {  //string compare
            if (previous == NULL) { 
                phonebook[index] = temp->next;
            }
            else {
                previous->next = temp->next;
            }
            free(temp);
            printf("Contact deleted successfully.\n");
            return;
        }
        previous = temp;
        temp = temp->next;
    }

    printf("Contact not found.\n");
}

void ModifyContact(list** phonebook, char name[], char number[], char address[]) {
    char firstChar = toupper(name[0]);
    int index = firstChar - 'A';
    list* temp = phonebook[index];

    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            strcpy(temp->number, number);
            strcpy(temp->address, address);
            printf("Contact modified successfully!\n");
            return;
        }
        temp = temp->next;
    }

    printf("Contact not found!\n");
}

void SearchContact(list** phonebook, char name[]) {
    char firstChar = toupper(name[0]);
    int index = firstChar - 'A';
    list* temp = phonebook[index];
    int found = 0;

    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            printf("Contact found:\n");
            printf("Name: %s\n", temp->name);
            printf("Number: %s\n", temp->number);
            printf("Address: %s\n", temp->address);
            found = 1;
        }
        temp = temp->next;
    }

    if (found==0) {
        printf("Contact not found!\n");
    }
}

int CountContacts(list** phonebook) {
    int count = 0;
    for (int i = 0; i < 26; i++) {
        list* temp = phonebook[i];
        while (temp != NULL) {
            count++;
            temp = temp->next;
        }
    }
    return count;
}

void ClearPhonebook(list** phonebook) {
    for (int i = 0; i < 26; i++) {
        list* temp = phonebook[i];
        while (temp != NULL) {
            list* next = temp->next;
            free(temp);
            temp = next;
        }
        phonebook[i] = NULL;
    }
}

void DisplayPhonebook(list** phonebook) {
    printf("PhoneBook:\n");
    for (int i = 0; i < 26; i++) {
        char currentChar = 'A' + i;
        list* temp = phonebook[i];
        if (temp != NULL) {
            printf("%c:\n", currentChar);
            while (temp != NULL) {
                printf("Name: %s\n", temp->name);
                printf("Number: %s\n", temp->number);
                printf("Address: %s\n", temp->address);
                printf("\n");
                temp = temp->next;
            }
        }
    }
}

int main() {
    list* phonebook[26];
    for (int i = 0; i < 26; i++) {
        phonebook[i] = NULL;
    }

    int choice;
    char name[15], number[15], address[50];

    while (1) {
        printf("PhoneBook Menu\n");
        printf("1. Insert Contact\n");
        printf("2. Delete Contact\n");
        printf("3. Search Contact\n");
        printf("4. Display PhoneBook\n");
        printf("5. Clear PhoneBook\n");
        printf("6. Count Contacts\n");
        printf("7. Modify Contact\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice) {
            case 1:
                printf("Enter the Contact Details:\n");
                printf("Name: ");
                scanf(" %[^\n]s", name);
                printf("Number: ");
                scanf(" %[^\n]s", number);
                printf("Address: ");
                scanf(" %[^\n]s", address);
                InsertContact(phonebook, name, number, address);
                printf("Contact inserted successfully!\n");
                break;
            case 2:
                printf("Enter the Name of the Contact: ");
                scanf(" %[^\n]s", name);
                DeleteContact(phonebook, name);
                break;
            case 3:
                printf("Enter the Name of the Contact: ");
                scanf(" %[^\n]s", name);
                SearchContact(phonebook, name);
                break;
            case 4:
                DisplayPhonebook(phonebook);
                break;
            case 5:
                ClearPhonebook(phonebook);
                printf("PhoneBook cleared successfully!\n");
                break;
            case 6:
                printf("Total contacts: %d\n", CountContacts(phonebook));
                break;
            case 7:
                printf("Enter the name of the Contact to Modify: ");
                scanf(" %[^\n]s", name);
                printf("Number: ");
                scanf(" %[^\n]s", number);
                printf("Address: ");
                scanf(" %[^\n]s", address);
                ModifyContact(phonebook,name,number,address);
                break;
            case 0:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice! Please try again.\n");
                break;
        }
        printf("\n");
    }

    return 0;
}
