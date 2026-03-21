#ifndef CLAIMS_H
#define CLAIMS_H

typedef enum {
    PENDING,
    APPROVED
} Status;

typedef struct Claim {
    int claim_id;
    char claimant_name[50];
    char item_name[50];
    char claim_date[20];
    char contact_number[15];
    Status status;
} Claim;

typedef struct ClaimNode {
    Claim data;
    struct ClaimNode *next;
} ClaimNode;

typedef struct Queue {
    ClaimNode *front;
    ClaimNode *rear;
} Queue;

Claim create_claim(void);
int enqueue(Claim c, Queue *q);
Claim dequeue(Queue *q);
void peek(Queue *q);
void all(Queue *q);
void toggle_status(Queue *q, int id);

#endif
