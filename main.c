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
        scanf("%d", &choice);

        switch (choice) {
            case 1: 
                displayAtionsMenu();
                break;
            case 2: 
                displayCategoryMenu(); 
                break;
            case 3: 
                displayClaimMenu(); 
                break;
            case 4: 
                displayFoundItemMenu();
                break;
            case 5:
                displayLostItemMenu();
                break;
            case 6:
                displayResolvedCasesMenu(); 
                break;
            case 7:
                displayStaffMenu(&staffList);
                break;
            case 0: 
                printf("\nGoodbye!\n");
                break;
            default:
                printf("\nInvalid choice. Try again.\n"); 
                break;
        }
    } while (choice != 0);

    freeCircularList(&staffList);
    return 0;
}
