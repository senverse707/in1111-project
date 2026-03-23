#include <stdio.h>
#include <stdlib.h>
#include "actions.h"

#include "categories.h"
#include "claims.h"
#include "found_item.h"
#include "lost_item.h"
#include "resolved_cases.h"
#include "staff.h"

int main() {
    int choice;
    CSLL staffList;
    initialize(&staffList);

    Queue claimQueue = {NULL, NULL};

    struct ResolvedList resolvedList;
    initialize_list(&resolvedList);

    do {
        printf("\n=========================================\n");
        printf("  Lost and Found Management System\n");
        printf("=========================================\n");
        printf("  1. Actions\n");
        printf("  2. Categories\n");
        printf("  3. Claims\n");
        printf("  4. Found Items\n");
        printf("  5. Lost Items\n");
        printf("  6. Resolved Cases\n");
        printf("  7. Staff\n");
        printf("  0. Exit\n");
        printf("=========================================\n");
        printf("  Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("\n  Invalid input. Please enter a number.\n");
            clearBuffer();
            choice = -1;
            continue;
        }
        clearBuffer();

        switch (choice) {
            case 1: displayActionsMenu(); break;
            case 2: displayCategoryMenu(); break;
            case 3: displayClaimMenu(&claimQueue); break;
            case 4: displayFoundItemMenu(); break;
            case 5: displayLostItemMenu(); break;
            case 6: displayResolvedCasesMenu(&resolvedList); break;
            case 7: displayStaffMenu(&staffList); break;
            case 0: printf("\nGoodbye!\n"); break;
            default: printf("\nInvalid choice. Try again.\n"); break;
        }
    } while (choice != 0);

    freeCircularList(&staffList);

    /* Free lost items linked list */
    {
        struct LostItem *cur = lostHead;
        while (cur) {
            struct LostItem *tmp = cur;
            cur = cur->next;
            free(tmp);
        }
        lostHead = NULL;
    }

    /* Free found items linked list */
    {
        FoundItemNode *cur = foundHead;
        while (cur) {
            FoundItemNode *tmp = cur;
            cur = cur->next;
            free(tmp);
        }
        foundHead = foundTail = NULL;
    }

    /* Free claim queue */
    {
        ClaimNode *cur = claimQueue.front;
        while (cur) {
            ClaimNode *tmp = cur;
            cur = cur->next;
            free(tmp);
        }
    }

    /* Free resolved cases circular doubly linked list */
    if (resolvedList.head != NULL) {
        struct ResolvedNode *cur = resolvedList.head->next;
        while (cur != resolvedList.head) {
            struct ResolvedNode *tmp = cur;
            cur = cur->next;
            free(tmp);
        }
        free(resolvedList.head);
    }

    /* Free action stack */
    while (stackTop) {
        ActionNode *tmp = stackTop;
        stackTop = stackTop->next;
        free(tmp);
    }

    return 0;
}
