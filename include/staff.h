#ifndef STAFF_H
#define STAFF_H

typedef struct
{
    int id;
    char name[50];
    char shift[20];
    char contactNumber[15];
    int dutyOrder;
} StaffMember;

typedef struct StaffNode
{
    StaffMember data;
    struct StaffNode *next;
} StaffNode;

typedef struct
{
    StaffNode *head;
} CSLL;

int generateStaffId();
void initialize(CSLL *list);
StaffNode *createStaffNode(StaffMember staffMember);
int countStaff(CSLL *list);
void addStaff(CSLL *list);
void removeStaff(CSLL *list);
void rotateToNext(CSLL *list);
void displayCurrentDuty(CSLL *list);
void displayAllStaff(CSLL *list);
void freeCircularList(CSLL *list);
void displayStaffMenu(CSLL *list);

#endif
