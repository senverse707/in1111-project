#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "claims.h"
#include "actions.h"


Claim create_claim()
{
    static int next_id = 1;   // static counter persists across calls
    Claim c;
    c.claim_id = next_id++;

    clearBuffer();

    printf("Enter claimant name: ");
    fgets(c.claimant_name, sizeof(c.claimant_name), stdin);
    c.claimant_name[strcspn(c.claimant_name, "\n")] = '\0';

    printf("Enter item name: ");
    fgets(c.item_name, sizeof(c.item_name), stdin);
    c.item_name[strcspn(c.item_name, "\n")] = '\0';

    printf("Enter claim date (YYYY-MM-DD): ");
    fgets(c.claim_date, sizeof(c.claim_date), stdin);
    c.claim_date[strcspn(c.claim_date, "\n")] = '\0';

    printf("Enter contact number: ");
    fgets(c.contact_number, sizeof(c.contact_number), stdin);
    c.contact_number[strcspn(c.contact_number, "\n")] = '\0';

    c.status = PENDING;       // default

    return c;
}
/////////////////
int enqueue(Claim c, Queue *q)
{
    ClaimNode *newNode = malloc(sizeof(ClaimNode));
    if (!newNode)
    {
        printf("Memory allocation failed\n");
        return 1;
    }

    newNode->data = c;
    newNode->next = NULL;

    if (q->rear == NULL) 
    {
        q->front = q->rear = newNode;
    }
    else
    {
        q->rear->next = newNode;
        q->rear = newNode;
    }

    return 0;
}


Claim dequeue(Queue *q)
{
    Claim emptyClaim = {0};  // returned if queue empty
    if (q->front == NULL)
    {
        printf("Queue is empty, nothing to remove\n");
        return emptyClaim;
    }

    ClaimNode *temp = q->front;
    Claim c = temp->data;

    q->front = q->front->next;
    if (q->front == NULL)
        q->rear = NULL;

    free(temp);
    return c;
}


void peek(Queue *q)
{
    if (q->front == NULL)
    {
        printf("Queue is empty\n");
        return;
    }

    Claim c = q->front->data;

    printf("---- Front Claim ----\n");
    printf("Claim ID: %d\n", c.claim_id);
    printf("Name: %s\n", c.claimant_name);
    printf("Item: %s\n", c.item_name);
    printf("Date: %s\n", c.claim_date);
    printf("Contact: %s\n", c.contact_number);
    printf("Status: %s\n", (c.status == PENDING) ? "Pending" : "Approved");
    printf("--------------------\n");
}

void all(Queue *q)
{
    if (q->front == NULL)
    {
        printf("Queue is empty, nothing to print\n");
        return;
    }

    ClaimNode *temp = q->front;
    printf("---- All Claims ----\n");

    while (temp != NULL)
    {
        Claim c = temp->data;

        printf("Claim ID: %d\n", c.claim_id);
        printf("Name: %s\n", c.claimant_name);
        printf("Item: %s\n", c.item_name);
        printf("Date: %s\n", c.claim_date);
        printf("Contact: %s\n", c.contact_number);
        printf("Status: %s\n", (c.status == PENDING) ? "Pending" : "Approved");
        printf("-------------------\n");

        temp = temp->next;
    }
}

void toggle_status(Queue *q, int id)
{
    ClaimNode *temp = q->front;
    while (temp != NULL)
    {
        if (temp->data.claim_id == id)
        {
            temp->data.status = (temp->data.status == PENDING) ? APPROVED : PENDING;
            printf("Status toggled for Claim ID %d\n", id);
            return;
        }
        temp = temp->next;
    }
    printf("Claim ID %d not found\n", id);
}


void displayClaimMenu(Queue *q){
    int choice;
    do {
        printf("\n===== Claim Management Menu =====\n");
        printf("1. Add New Claim\n");
        printf("2. Show Front Claim\n");
        printf("3. Show All Claims\n");
        printf("4. Remove Front Claim\n");
        printf("5. Toggle Status by ID\n");
        printf("0. Back to Main Menu\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input. Please enter a number.\n");
            clearBuffer();
            choice = -1;
            continue;
        }
        clearBuffer();
        printf("\n");

        switch (choice)
        {
        case 1:
        {
            Claim c = create_claim();
            enqueue(c, q);
            char logMsg[100];
            snprintf(logMsg, sizeof(logMsg), "Claim enqueued: %s for %s (ID:%d)", c.claimant_name, c.item_name, c.claim_id);
            
            pushAction(logMsg, "INSERT");

            printf("Claim added successfully!\n");
            break;
        }

        case 2:
            peek(q);

            break;

        case 3:
            all(q);
            break;

        case 4:
        {
            Claim removed = dequeue(q);
            if (removed.claim_id != 0) {
                char logMsg[100];
                snprintf(logMsg, sizeof(logMsg), "Claim dequeued: %s (ID:%d)", removed.claimant_name, removed.claim_id);
                pushAction(logMsg, "DELETE");
                printf("Removed Claim ID: %d\n", removed.claim_id);
            }
            break;
        }

        case 5:
        {
            int id;
            printf("Enter Claim ID to toggle status: ");
            scanf("%d", &id);
            toggle_status(q, id);
            char logMsg2[100];
            snprintf(logMsg2, sizeof(logMsg2), "Claim status toggled (ID:%d)", id);
            pushAction(logMsg2, "UPDATE");
            break;
        }
        case 0:
            break;
        default:
            printf("Invalid choice! Try again.\n");
        }
    } while (choice != 0);
}