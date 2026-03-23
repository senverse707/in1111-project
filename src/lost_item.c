
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lost_item.h"
#include "actions.h"

struct LostItem *lostHead = NULL;

void insertLostItem()
{
    struct LostItem *newNode = (struct LostItem*)malloc(sizeof(struct LostItem));

    printf("Enter Lost Item ID: ");
    scanf("%d", &newNode->id);
    clearBuffer();

    printf("Enter Item Name: ");
    fgets(newNode->name, sizeof(newNode->name), stdin);
    newNode->name[strcspn(newNode->name, "\n")] = '\0';

    printf("Enter Category: ");
    fgets(newNode->category, sizeof(newNode->category), stdin);
    newNode->category[strcspn(newNode->category, "\n")] = '\0';

    printf("Enter Color: ");
    fgets(newNode->color, sizeof(newNode->color), stdin);
    newNode->color[strcspn(newNode->color, "\n")] = '\0';

    printf("Enter Location Lost: ");
    fgets(newNode->location, sizeof(newNode->location), stdin);
    newNode->location[strcspn(newNode->location, "\n")] = '\0';

    printf("Enter Date Lost: ");
    fgets(newNode->date, sizeof(newNode->date), stdin);
    newNode->date[strcspn(newNode->date, "\n")] = '\0';

    printf("Enter Owner Name: ");
    fgets(newNode->owner, sizeof(newNode->owner), stdin);
    newNode->owner[strcspn(newNode->owner, "\n")] = '\0';

    printf("Enter Contact Number: ");
    fgets(newNode->contact, sizeof(newNode->contact), stdin);
    newNode->contact[strcspn(newNode->contact, "\n")] = '\0';

    newNode->next = NULL;

    if(lostHead == NULL)
    {
        lostHead = newNode;
    }
    else
    {
        struct LostItem *temp = lostHead;
        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    char logMsg[100];
    snprintf(logMsg, sizeof(logMsg), "Lost item added: %s (ID:%d)", newNode->name, newNode->id);
    pushAction(logMsg, "INSERT");
    printf("Lost item added successfully!\n");
}

void displayLostItems()
{
    struct LostItem *temp = lostHead;

    if(temp == NULL)
    {
        printf("No lost items found.\n");
        return;
    }

    while(temp != NULL)
    {
        printf("\nID: %d", temp->id);
        printf("\nItem Name: %s", temp->name);
        printf("\nCategory: %s", temp->category);
        printf("\nColor: %s", temp->color);
        printf("\nLocation Lost: %s", temp->location);
        printf("\nDate Lost: %s", temp->date);
        printf("\nOwner: %s", temp->owner);
        printf("\nContact: %s\n", temp->contact);

        temp = temp->next;
    }
}

void searchLostItem()
{
    int id;
    printf("Enter Lost Item ID to search: ");
    scanf("%d", &id);
    clearBuffer();

    struct LostItem *temp = lostHead;

    while(temp != NULL)
    {
        if(temp->id == id)
        {
            printf("Item Found!\n");
            printf("Item Name: %s\n", temp->name);
            printf("Owner: %s\n", temp->owner);
            return;
        }
        temp = temp->next;
    }

    printf("Item not found.\n");
}

void deleteLostItem()
{
    int id;
    printf("Enter ID to delete: ");
    scanf("%d", &id);
    clearBuffer();

    struct LostItem *temp = lostHead;
    struct LostItem *prev = NULL;

    if(temp != NULL && temp->id == id)
    {
        char logMsg[100];
        snprintf(logMsg, sizeof(logMsg), "Lost item deleted: %s (ID:%d)", temp->name, temp->id);
        lostHead = temp->next;
        free(temp);
        pushAction(logMsg, "DELETE");
        printf("Item deleted.\n");
        return;
    }

    while(temp != NULL && temp->id != id)
    {
        prev = temp;
        temp = temp->next;
    }

    if(temp == NULL)
    {
        printf("Item not found.\n");
        return;
    }

    char logMsg[100];
    snprintf(logMsg, sizeof(logMsg), "Lost item deleted: %s (ID:%d)", temp->name, temp->id);
    prev->next = temp->next;
    free(temp);

    pushAction(logMsg, "DELETE");
    printf("Item deleted successfully.\n");
}

void updateLostItem()
{
    int id;
    printf("Enter ID to update: ");
    scanf("%d", &id);
    clearBuffer();

    struct LostItem *temp = lostHead;

    while(temp != NULL)
    {
        if(temp->id == id)
        {
            printf("Enter New Item Name: ");
            fgets(temp->name, sizeof(temp->name), stdin);
            temp->name[strcspn(temp->name, "\n")] = '\0';

            printf("Enter New Category: ");
            fgets(temp->category, sizeof(temp->category), stdin);
            temp->category[strcspn(temp->category, "\n")] = '\0';

            printf("Enter New Color: ");
            fgets(temp->color, sizeof(temp->color), stdin);
            temp->color[strcspn(temp->color, "\n")] = '\0';

            char logMsg[100];
            snprintf(logMsg, sizeof(logMsg), "Lost item updated (ID:%d)", temp->id);
            pushAction(logMsg, "UPDATE");
            printf("Update successful!\n");
            return;
        }

        temp = temp->next;
    }

    printf("Item not found.\n");
}


 void sortLostItems()
{
    struct LostItem *sorted = NULL;
    struct LostItem *current = lostHead;

    while (current != NULL)
    {
        struct LostItem *next = current->next;

        if (sorted == NULL || current->id < sorted->id)
        {
            current->next = sorted;
            sorted = current;
        }
        else
        {
            struct LostItem *temp = sorted;

            while (temp->next != NULL && temp->next->id < current->id)
            {
                temp = temp->next;
            }

            current->next = temp->next;
            temp->next = current;
        }

        current = next;
    }

    lostHead = sorted;

    pushAction("Lost items sorted by ID", "UPDATE");
    printf("Lost items sorted by ID successfully!\n");
}

void displayLostItemMenu(){
    int choice;
    do {
        printf("\n===== Lost Item Management Menu =====\n");
        printf("1. Insert Lost Item\n");
        printf("2. Display Lost Items\n");
        printf("3. Search Lost Item\n");
        printf("4. Delete Lost Item\n");
        printf("5. Update Lost Item\n");
        printf("6. Sort Lost Items (by ID)\n");
        printf("0. Back to Main Menu\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearBuffer();
            choice = -1;
            continue;
        }
        clearBuffer();
        switch (choice) {
            case 1: insertLostItem(); break;
            case 2: displayLostItems(); break;
            case 3: searchLostItem(); break;
            case 4: deleteLostItem(); break;
            case 5: updateLostItem(); break;
            case 6: sortLostItems(); break;
            case 0: break;
            default: printf("Invalid choice\n");
        }
    } while (choice != 0);
}