
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lost_item.h"

struct LostItem *lostHead = NULL;

void insertLostItem()
{
    struct LostItem *newNode = (struct LostItem*)malloc(sizeof(struct LostItem));

    printf("Enter Lost Item ID: ");
    scanf("%d", &newNode->id);

    printf("Enter Item Name: ");
    scanf("%s", newNode->name);

    printf("Enter Category: ");
    scanf("%s", newNode->category);

    printf("Enter Color: ");
    scanf("%s", newNode->color);

    printf("Enter Location Lost: ");
    scanf("%s", newNode->location);

    printf("Enter Date Lost: ");
    scanf("%s", newNode->date);

    printf("Enter Owner Name: ");
    scanf("%s", newNode->owner);

    printf("Enter Contact Number: ");
    scanf("%s", newNode->contact);

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

    struct LostItem *temp = lostHead;
    struct LostItem *prev = NULL;

    if(temp != NULL && temp->id == id)
    {
        lostHead = temp->next;
        free(temp);
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

    prev->next = temp->next;
    free(temp);

    printf("Item deleted successfully.\n");
}

void updateLostItem()
{
    int id;
    printf("Enter ID to update: ");
    scanf("%d", &id);

    struct LostItem *temp = lostHead;

    while(temp != NULL)
    {
        if(temp->id == id)
        {
            printf("Enter New Item Name: ");
            scanf("%s", temp->name);

            printf("Enter New Category: ");
            scanf("%s", temp->category);

            printf("Enter New Color: ");
            scanf("%s", temp->color);

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
        scanf("%d", &choice);
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