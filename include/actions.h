#ifndef ACTIONS_H
#define ACTIONS_H

typedef struct ActionNode
{
    int actionID;
    char actionDescription[100];
    char actionType[20];
    char timestamp[20];
    struct ActionNode *next;
} ActionNode;

extern ActionNode *stackTop;
extern int stackSize;
extern int actionCounter;

void clearBuffer(void);
void printLine(int n);
void getCurrentTime(char *buf);
void pushAction(const char *desc, const char *type);
void popAction(void);
void peekAction(void);
void displayActionHistory(void);
void countActionsByType(void);
void pushManual(void);
void loadSampleData(void);
void displayActionsMenu();

#endif
