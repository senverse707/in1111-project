#ifndef RESOLVED_CASES_H
#define RESOLVED_CASES_H

#include <stdbool.h>

struct ResolvedNode {
    int CaseID;
    int ItemID;
    char ItemName[30];
    char OwnerName[40];
    char ReturnedDate[15];
    char VerifiedBy[40];
    char Remarks[50];
    struct ResolvedNode *next;
    struct ResolvedNode *prev;
};

struct ResolvedList {
    struct ResolvedNode *head;
    struct ResolvedNode *tail;
};

void initialize_list(struct ResolvedList *list);
struct ResolvedNode *create_node(int CaseID, int ItemID, char ItemName[],
                                 char OwnerName[], char ReturnedDate[],
                                 char VerifiedBy[], char Remarks[]);
void traverseforward(struct ResolvedList *list);
void traversebackward(struct ResolvedList *list);
bool isduplicate(struct ResolvedList *list, int CaseID, int ItemID);
void addcase(struct ResolvedList *list, int CaseID, int ItemID,
             char ItemName[], char OwnerName[], char ReturnedDate[],
             char VerifiedBy[], char Remarks[]);
void displaycase(struct ResolvedNode *temp);
struct ResolvedNode *search(struct ResolvedList *list, int CaseID);
void update(struct ResolvedList *list, int CaseID, char NewRemarks[]);
void deletecase(struct ResolvedList *list, int CaseID);
void displayResolvedCasesMenu();

#endif
