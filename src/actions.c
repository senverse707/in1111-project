#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "actions.h"


ActionNode *stackTop = NULL;
int stackSize = 0;
int actionCounter = 1;

/* helpers  */
void clearBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void printLine(int n)
{
    for (int i = 0; i < n; i++)
        putchar('-');
    putchar('\n');
}

void getCurrentTime(char *buf)
{
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    strftime(buf, 20, "%Y-%m-%d %H:%M", tm);
}

/* stack operations */

void pushAction(const char *desc, const char *type)
{
    ActionNode *n = (ActionNode *)malloc(sizeof(ActionNode));
    if (!n)
    {
        printf("  [Error] Memory allocation failed.\n");
        return;
    }
    n->actionID = actionCounter++;
    strncpy(n->actionDescription, desc, 99);
    n->actionDescription[99] = '\0';
    strncpy(n->actionType, type, 19);
    n->actionType[19] = '\0';
    getCurrentTime(n->timestamp);
    n->next = stackTop;
    stackTop = n;
    stackSize++;
    printf("  [OK] Action pushed. Stack size: %d\n", stackSize);
}

void popAction(void)
{
    if (!stackTop)
    {
        printf("  [Stack] No actions to undo.\n");
        return;
    }
    printf("\n  [UNDO] Action removed:\n");
    printf("  ID    : %d\n", stackTop->actionID);
    printf("  Type  : %s\n", stackTop->actionType);
    printf("  Desc  : %s\n", stackTop->actionDescription);
    printf("  Time  : %s\n", stackTop->timestamp);
    ActionNode *tmp = stackTop;
    stackTop = stackTop->next;
    free(tmp);
    stackSize--;
    printf("  Stack size now: %d\n", stackSize);
}

void peekAction(void)
{
    if (!stackTop)
    {
        printf("  [Stack] Stack is empty.\n");
        return;
    }
    printf("\n  [Most Recent Action]\n");
    printf("  ID    : %d\n", stackTop->actionID);
    printf("  Type  : %s\n", stackTop->actionType);
    printf("  Desc  : %s\n", stackTop->actionDescription);
    printf("  Time  : %s\n", stackTop->timestamp);
}

void displayActionHistory(void)
{
    if (!stackTop)
    {
        printf("  [Stack] No action history.\n");
        return;
    }
    printf("\n  %-4s  %-10s  %-22s  %s\n", "ID", "Type", "Timestamp", "Description");
    printLine(75);
    ActionNode *cur = stackTop;
    while (cur)
    {
        printf("  %-4d  %-10s  %-22s  %s\n",
               cur->actionID,
               cur->actionType,
               cur->timestamp,
               cur->actionDescription);
        cur = cur->next;
    }
    printf("\n  Total actions in stack: %d\n", stackSize);
}

void countActionsByType(void)
{
    int ins = 0, del = 0, upd = 0, other = 0;
    ActionNode *cur = stackTop;
    while (cur)
    {
        if (strcmp(cur->actionType, "INSERT") == 0)
            ins++;
        else if (strcmp(cur->actionType, "DELETE") == 0)
            del++;
        else if (strcmp(cur->actionType, "UPDATE") == 0)
            upd++;
        else
            other++;
        cur = cur->next;
    }
    printf("\n  Action Type Summary:\n");
    printf("  INSERT : %d\n", ins);
    printf("  DELETE : %d\n", del);
    printf("  UPDATE : %d\n", upd);
    if (other)
        printf("  OTHER  : %d\n", other);
    printf("  TOTAL  : %d\n", ins + del + upd + other);
}

/* manually push input */
void pushManual(void)
{
    char desc[100], type[20];
    printf("  Action Description : ");
    fgets(desc, 100, stdin);
    desc[strcspn(desc, "\n")] = '\0';
    printf("  Action Type (INSERT / DELETE / UPDATE) : ");
    fgets(type, 20, stdin);
    type[strcspn(type, "\n")] = '\0';
    pushAction(desc, type);
}

/*  sample data for stack loading  */
void loadSampleData(void)
{
    pushAction("Lost item added: iPhone 13 (ID:1)", "INSERT");
    pushAction("Found item added: Blue Wallet (ID:1)", "INSERT");
    pushAction("Lost item deleted: Keys (ID:3)", "DELETE");
    pushAction("Category updated: Electronics (ID:2)", "UPDATE");
    pushAction("Claim enqueued: Laptop by Amal (ID:1)", "INSERT");
    printf("  [OK] 5 sample actions loaded.\n");
}

void displayActionsMenu(){
    int ch;
    do
    {
        printf("\n");
        printLine(50);
        printf("  1. Push Action\n");
        printf("  2. Pop Action  (Undo)\n");
        printf("  3. Peek        (View top)\n");
        printf("  4. Display Full History\n");
        printf("  5. Count by Type\n");
        printf("  0. Exit\n");
        printLine(50);
        printf("  Choice: ");
        scanf("%d", &ch);
        clearBuffer();
        printf("\n");
        switch (ch)
        {
        case 1:
            pushManual();
            break;
        case 2:
            popAction();
            break;
        case 3:
            peekAction();
            break;
        case 4:
            displayActionHistory();
            break;
        case 5:
            countActionsByType();
            break;
        case 0:
            printf("  Goodbye!\n\n");
            break;
        default:
            printf("  [Error] Invalid option.\n");
        }
    } while (ch != 0);
}

