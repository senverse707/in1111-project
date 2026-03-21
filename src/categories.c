#include <stdio.h>
#include <string.h>
#include "categories.h"

char categories[MAX_CATEGORIES][MAX_LENGTH];
int categoryCount = 0;

// Add category
void addCategory() {
    if (categoryCount >= MAX_CATEGORIES) {
        printf("Category list is full.\n");
        return;
    }

    printf("Enter category name: ");
    scanf(" %[^\n]", categories[categoryCount]);
    categoryCount++;

    printf("Category added successfully.\n");
}

// Update category
void updateCategory() {
    int index;

    if (categoryCount == 0) {
        printf("No categories available to update.\n");
        return;
    }

    printf("Enter category number to update (1 to %d): ", categoryCount);
    scanf("%d", &index);

    if (index < 1 || index > categoryCount) {
        printf("Invalid category number.\n");
        return;
    }

    printf("Enter new category name: ");
    scanf(" %[^\n]", categories[index - 1]);

    printf("Category updated successfully.\n");
}

// Search category
void searchCategory() {
    char search[MAX_LENGTH];
    int found = 0;

    if (categoryCount == 0) {
        printf("No categories available.\n");
        return;
    }

    printf("Enter category name to search: ");
    scanf(" %[^\n]", search);

    for (int i = 0; i < categoryCount; i++) {
        if (strcmp(categories[i], search) == 0) {
            printf("Category found at position %d.\n", i + 1);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Category not found.\n");
    }
}

// Display categories
void displayCategories() {
    if (categoryCount == 0) {
        printf("No categories to display.\n");
        return;
    }

    printf("\n--- Item Categories ---\n");
    for (int i = 0; i < categoryCount; i++) {
        printf("%d. %s\n", i + 1, categories[i]);
    }
}

void displayCategoryMenu(){
    int choice;

    do {
        printf("\n===== Item Category Management =====\n");
        printf("1. Add Category\n");
        printf("2. Update Category\n");
        printf("3. Search Category\n");
        printf("4. Display Categories\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addCategory();
                break;
            case 2:
                updateCategory();
                break;
            case 3:
                searchCategory();
                break;
            case 4:
                displayCategories();
                break;
            case 0:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }

    } while (choice != 0);
}
