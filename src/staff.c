#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "staff.h"
#include "actions.h"

int nextId = 1;
int generateStaffId()
{
    return nextId++;
}

void initialize(CSLL *list)
{
    list->head = NULL;
}

StaffNode *createStaffNode(StaffMember staffMember)
{
    StaffNode *newNode = (StaffNode *)malloc(sizeof(StaffNode));
    if (newNode == NULL)
    {
        printf("  [ERROR] Memory allocation failed.\n");
        return NULL;
    }
    newNode->data = staffMember;
    newNode->next = NULL;
    return newNode;
}

int countStaff(CSLL *list)
{
    if (list->head == NULL)
        return 0;

    int count = 0;
    StaffNode *temp = list->head;
    do
    {
        count++;
        temp = temp->next;
    } while (temp != list->head);
    return count;
}

void addStaff(CSLL *list)
{
    StaffMember staffMember;
    staffMember.id = generateStaffId();
    staffMember.dutyOrder = staffMember.id;

    printf("\n  --- Add Staff Member ---\n");

    printf("  Enter name: ");
    fgets(staffMember.name, sizeof(staffMember.name), stdin);
    staffMember.name[strcspn(staffMember.name, "\n")] = '\0';

    printf("  Enter shift (Morning/Afternoon/Night): ");
    fgets(staffMember.shift, sizeof(staffMember.shift), stdin);
    staffMember.shift[strcspn(staffMember.shift, "\n")] = '\0';

    printf("  Enter contact number: ");
    fgets(staffMember.contactNumber, sizeof(staffMember.contactNumber), stdin);
    staffMember.contactNumber[strcspn(staffMember.contactNumber, "\n")] = '\0';

    StaffNode *newNode = createStaffNode(staffMember);
    if (newNode == NULL)
        return;

    if (list->head == NULL)
    {
        list->head = newNode;
        newNode->next = newNode;
    }
    else
    {
        StaffNode *temp = list->head;
        while (temp->next != list->head)
        {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = list->head;
    }

    char logMsg[100];
    snprintf(logMsg, sizeof(logMsg), "Staff added: %s (ID:%d)", newNode->data.name, newNode->data.id);
    pushAction(logMsg, "INSERT");
    printf("\n  [SUCCESS] Staff '%s' added (ID: %d).\n", newNode->data.name, newNode->data.id);
}

void removeStaff(CSLL *list)
{
    if (list->head == NULL)
    {
        printf("  [INFO] No staff members to remove.\n");
        return;
    }

    int id;
    printf("\n  Enter Staff ID to remove: ");
    if (scanf("%d", &id) != 1)
    {
        printf("  [ERROR] Invalid input.\n");
        clearBuffer();
        return;
    }
    clearBuffer();

    StaffNode *curr = list->head;
    StaffNode *prev = NULL;
    int found = 0;

    prev = list->head;
    while (prev->next != list->head)
    {
        prev = prev->next;
    }

    curr = list->head;
    do
    {
        if (curr->data.id == id)
        {
            found = 1;
            break;
        }
        prev = curr;
        curr = curr->next;
    } while (curr != list->head);

    if (!found)
    {
        printf("  [ERROR] Staff with ID %d not found.\n", id);
        return;
    }

    printf("  Found: %s (Shift: %s)\n", curr->data.name, curr->data.shift);
    printf("  Confirm removal? (y/n): ");
    char confirm;
    scanf("%c", &confirm);
    clearBuffer();

    if (confirm != 'y' && confirm != 'Y')
    {
        printf("  Removal cancelled.\n");
        return;
    }

    if (curr->next == curr)
    {
        list->head = NULL;
    }
    else
    {
        prev->next = curr->next;
        if (curr == list->head)
        {
            list->head = curr->next;
        }
    }

    char logMsg[100];
    snprintf(logMsg, sizeof(logMsg), "Staff removed: %s (ID:%d)", curr->data.name, curr->data.id);
    free(curr);
    pushAction(logMsg, "DELETE");
    printf("  [SUCCESS] Staff removed.\n");
}

void rotateToNext(CSLL *list)
{
    if (list->head == NULL)
    {
        printf("  [INFO] No staff members to rotate.\n");
        return;
    }

    list->head = list->head->next;
    char logMsg[100];

    snprintf(logMsg, sizeof(logMsg), "Duty rotated to: %s (ID:%d)", list->head->data.name, list->head->data.id);
    
    pushAction(logMsg, "UPDATE");
    
    printf("  [INFO] Rotated. Current on duty: %s (ID: %d, Shift: %s)\n", list->head->data.name, list->head->data.id, list->head->data.shift);
}

void displayCurrentDuty(CSLL *list)
{
    if (list->head == NULL)
    {
        printf("  [INFO] No staff members.\n");
        return;
    }

    StaffNode *onDuty = list->head;
    printf("\n  --- Current Staff on Duty ---\n");
    printf("    ID:      %d\n", onDuty->data.id);
    printf("    Name:    %s\n", onDuty->data.name);
    printf("    Shift:   %s\n", onDuty->data.shift);
    printf("    Contact: %s\n", onDuty->data.contactNumber);
}

void displayAllStaff(CSLL *list)
{
    if (list->head == NULL)
    {
        printf("  [INFO] No staff members.\n");
        return;
    }

    int count = countStaff(list);
    printf("\n  [INFO] Displaying %d staff member(s) in rotation order:\n\n", count);
    printf("  %-6s %-20s %-15s %-15s %-10s\n", "ID", "Name", "Shift", "Contact", "Status");
    printf("  ------------------------------------------------------------------\n");

    StaffNode *temp = list->head;
    int first = 1;
    do
    {
        printf("  %-6d %-20s %-15s %-15s %-10s\n",
               temp->data.id, temp->data.name, temp->data.shift,
               temp->data.contactNumber,
               first ? "<- ON DUTY" : "");
        first = 0;
        temp = temp->next;
    } while (temp != list->head);

}

void freeCircularList(CSLL *list)

{
    if (list->head == NULL)
        return;

    StaffNode *curr = list->head->next;
    while (curr != list->head)
    {
        StaffNode *temp = curr;
        curr = curr->next;
        free(temp);
    }
    free(list->head);
    list->head = NULL;
}

void displayStaffMenu(CSLL *list)
{
    int choice;

    do
    {
        printf("\n");
        printf("  ========================================\n");

        printf("    STAFF DUTY ROTATION\n");

        printf("  ========================================\n");

        printf("    1. Add Staff Member\n");
        printf("    2. Remove Staff Member\n");
        printf("    3. Rotate to Next (Move Duty)\n");
        printf("    4. View Current On Duty\n");
        printf("    5. Display All Staff\n");
        printf("    0. Back to Main Menu\n");

        printf("  ========================================\n");

        printf("    Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("\n  [Warning] Invalid input! Please enter a number.\n");
            clearBuffer();
            choice = -1;
            continue;
        }

        clearBuffer();

        switch (choice)
        {
        case 1:
            addStaff(list);
            break;
        case 2:
            removeStaff(list);
            break;
        case 3:
            rotateToNext(list);
            break;
        case 4:
            displayCurrentDuty(list);
            break;
        case 5:
            displayAllStaff(list);
            break;
        case 0:
            break;
        default:
            printf("    Invalid choice.\n");
        }
    } while (choice != 0);
}

