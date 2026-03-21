#ifndef LOST_ITEM_H
#define LOST_ITEM_H

struct LostItem
{
    int id;
    char name[50];
    char category[50];
    char color[30];
    char location[50];
    char date[20];
    char owner[50];
    char contact[20];

    struct LostItem *next;
};

extern struct LostItem *lostHead;

void insertLostItem(void);
void displayLostItems(void);
void searchLostItem(void);
void deleteLostItem(void);
void updateLostItem(void);
void sortLostItems(void);

#endif
