#ifndef FOUND_ITEM_H
#define FOUND_ITEM_H

typedef struct FoundItemNode {
    int itemID;
    char itemName[50];
    char category[30];
    char color[20];
    char location[50];
    char date[20];
    char finderName[50];
    char contact[20];
    struct FoundItemNode *prev;
    struct FoundItemNode *next;
} FoundItemNode;

extern FoundItemNode *foundHead;
extern FoundItemNode *foundTail;
extern int foundIdCounter;

void insertItem(void);
void displayForward(void);
void displayBackward(void);
void searchItem(void);
void deleteItem(void);

#endif
