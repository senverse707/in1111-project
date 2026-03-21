#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "found_item.h"

FoundItemNode *foundHead = NULL, *foundTail = NULL;
int foundIdCounter = 1;

// Insert
void insertItem() {
    FoundItemNode *newNode = (FoundItemNode *)malloc(sizeof(FoundItemNode));

    newNode->itemID = foundIdCounter++;

    printf("Item Name: ");
    scanf(" %[^\n]", newNode->itemName);
    printf("Category: ");
    scanf(" %[^\n]", newNode->category);
    printf("Color: ");
    scanf(" %[^\n]", newNode->color);
    printf("Location Found: ");
    scanf(" %[^\n]", newNode->location);
    printf("Date Found: ");
    scanf(" %[^\n]", newNode->date);
    printf("Finder Name: ");
    scanf(" %[^\n]", newNode->finderName);
    printf("Contact: ");
    scanf(" %[^\n]", newNode->contact);

    newNode->next = NULL;
    newNode->prev = foundTail;

    if (foundHead == NULL)
        foundHead = foundTail = newNode;
    else {
        foundTail->next = newNode;
        foundTail = newNode;
    }

    printf("[OK] Item added successfully\n");
}

// Display forward
void displayForward() {
    FoundItemNode *temp = foundHead;
    while (temp != NULL) {
        printf("\nID: %d\nName: %s\nCategory: %s\n",
               temp->itemID, temp->itemName, temp->category);
        temp = temp->next;
    }
}

// Display backward
void displayBackward() {
    FoundItemNode *temp = foundTail;
    while (temp != NULL) {
        printf("\nID: %d\nName: %s\nCategory: %s\n",
               temp->itemID, temp->itemName, temp->category);
        temp = temp->prev;
    }
}

// Search
void searchItem() {
    int id;
    printf("Enter ID: ");
    scanf("%d", &id);

    FoundItemNode *temp = foundHead;
    while (temp != NULL) {
        if (temp->itemID == id) {
            printf("Found: %s\n", temp->itemName);
            return;
        }
        temp = temp->next;
    }
    printf("Not found\n");
}

// Delete
void deleteItem() {
    int id;
    printf("Enter ID to delete: ");
    scanf("%d", &id);

    FoundItemNode *temp = foundHead;

    while (temp != NULL) {
        if (temp->itemID == id) {
            if (temp == foundHead) foundHead = temp->next;
            if (temp == foundTail) foundTail = temp->prev;

            if (temp->prev) temp->prev->next = temp->next;
            if (temp->next) temp->next->prev = temp->prev;

            free(temp);
            printf("Deleted successfully\n");
            return;
        }
        temp = temp->next;
    }
    printf("Item not found\n");
}

// Main
int main() {
    int choice;

    do {
        printf("\n1.Insert\n2.Delete\n3.Search\n4.Display Forward\n5.Display Backward\n0.Exit\nChoice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: insertItem(); break;
            case 2: deleteItem(); break;
            case 3: searchItem(); break;
            case 4: displayForward(); break;
            case 5: displayBackward(); break;
        }
    } while (choice != 0);

    return 0;
}